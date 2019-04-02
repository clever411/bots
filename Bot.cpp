#include "Bot.hpp"

#include <iostream>

#include "BotField.hpp"
#include "Cell.hpp"
#include "Plant.hpp"
#include "Body.hpp"
#include "Mineral.hpp"


using namespace clever;
using namespace std;





// core
Bot::Bot()
{
	random_fill_brain();
}

void Bot::update(field_type &f)
{
	++age;
	++worldage;

	auto &cell = f.at(x, y);
	double delta = stepprice() + age * agesteptax();

		// death
	if( !( energy - delta > deathedge() ) )
	{
		cell.bot = nullptr;
		cell.body = new Body { energy, 0 };
		delete this;
		return;
	}

		// all right
	energy -= delta;
	cell.energy += delta;
	

	
	// bud
	if(
		energy > budreq() &&
		sqrt(
			(energy - budreq()) /
			(maxenergy() - budreq())
		) > realdis(dre)
	)
	{
		auto to = getto();
		if(valid(to, f))
		{
			f.correct(to);
			auto &toc = f.at(to);
			if(!toc.bot && !toc.body)
			{
				toc.bot = bud();
				toc.bot->x = to.x;
				toc.bot->y = to.y;
				return;
			}
		}
	}
	
	

	// on brain
	int count = 0;
	neuron_type action, jmp;
	while(count < REPEAT_COMMAND_COUNT)
	{
		action = brain[p] & ACTION_MASK;
		jmp = brain[p] >> 4;

		switch(action)
		{
		case NUL:
		{
			int i = 0;
			for(; brain[p] & JUMP_MASK == NUL && i != BRAIN_SIZE; ++i)
				incp();
			if(i == BRAIN_SIZE)
				return;
			break;
		}

		case MOVE:
			move(f);
			jump(jmp);
			return;

		case EAT:
			eat(f);
			jump(jmp);
			return;

		case TURN: case TURN+1: case TURN+2:
			turn(action-TURN);
			jump(jmp);
			break;

		case CHECK: case CHECK+1:
		case CHECK+2: case CHECK+3:
			check(f, action-CHECK, jmp);
			break;

		default:
			throw 1;

		}

		++count;
	}



	return;
}

void Bot::random_fill_brain()
{
	for(auto *b = brain, *e = brain+BRAIN_SIZE; b != e; ++b)
		*b = random_neuron();
	return;
}



// actions
Bot *Bot::bud()
{
	static uniform_int_distribution<int>
		mutdis(0, CHARACTERS_COUNT-1),
		braindis(0, BRAIN_SIZE-1);

	// burn
	Bot *child = new Bot(*this);
	child->age = 0;
	++child->generation;
	double const delta = budprice();
	energy -= delta;
	child->energy = delta;



	// mutation
	float *characts[ CHARACTERS_COUNT ] = {
		&child->steppricek, &child->agesteptaxk,
		&child->maxenergyk,
		&child->budreqk, &child->budpricek
	};

	int from, to;
	do
	{
		from = mutdis(dre);
	}
	while(
		*characts[from] - MUTATION_POWER <= 1.0 - MAX_MUTATION 
	);

	do
	{
		to = mutdis(dre);
	}
	while(
		to == from ||
		*characts[to] + MUTATION_POWER >= 1.0 + MAX_MUTATION 
	);

	*characts[from] -= MUTATION_POWER;
	*characts[to] += MUTATION_POWER;

	child->brain[ braindis(dre) ] = random_neuron();



	return child;
}

void Bot::move(field_type &f)
{
	auto to = getto();
	if( !valid(to, f) )
		return;

	f.correct(to);
	auto &toc = f.at(to);
	if(toc.bot || toc.body)
		return;

	f.at(x, y).bot = nullptr;
	x = to.x;
	y = to.y;
	toc.bot = this;

	return;
}

void Bot::eat(field_type &f)
{
	auto &toc = f.neart(x, y, dir);
	if(!toc.plant)
		return;

	auto &plant = *toc.plant;
	if( !( plant.energy > maxenergy() - energy ) )
	{
		energy += plant.energy;
		delete toc.plant;
		toc.plant = nullptr;
	}
	else
	{
		double const delta = maxenergy() - energy;
		plant.energy -= delta;
		energy += delta;
	}

	return;
}

void Bot::turn(neuron_type arg)
{
	static uniform_int_distribution<int> turndis(0, 1);

	switch(arg)
	{
	case 0:
		dir = tape( dir - 1, field_type::OFFSET_COUNT );
		break;
	case 1:
		dir = (dir + 1) % field_type::OFFSET_COUNT;
		break;
	case 2:
		dir = tape(
			dir + ( turndis(dre) == 0 ? -1 : 1 ),
			field_type::OFFSET_COUNT
		);
		break;
	default:
		throw 1;
	}

	return;
}

void Bot::check(field_type const &f, neuron_type action, neuron_type jmp)
{
	auto to = getto();
	auto const &toc = f.att(to);

	bool is = false;
	switch(action)
	{
	case 0:
		is = !toc.bot && !toc.body;
		break;
	case 1:
		is = toc.plant;
		break;
	case 2:
		is = toc.bot;
		break;
	case 3:
		is = toc.body;
		break;
	default:
		throw 1;
	}

	if(is)
		jump(jmp);
	else
		jump(jmp >> 6);
	
	return;
}

void Bot::jump(neuron_type jmp)
{
	p = jmp & JUMP_MASK;
	return;
}



// private help
inline Bot::neuron_type Bot::random_neuron()
{
	static constexpr neuron_type NEURONS[] = {
		NUL, EAT, MOVE,
		TURN, TURN+1, TURN+2,
		CHECK, CHECK+1, CHECK+2, CHECK+3
	};
	static constexpr int const
		NEURONS_SIZE = sizeof(NEURONS) / sizeof(neuron_type);
	static std::uniform_int_distribution<int>
		neurondis(0, NEURONS_SIZE-1),
		jumpdis(0, BRAIN_SIZE-1);

	return NEURONS[ neurondis(dre) ] + (jumpdis(dre) << 6) + (jumpdis(dre) << 12);
}

inline void Bot::incp()
{
	p = (p + 1) % BRAIN_SIZE;
	return;
}

inline PointI Bot::getto() const
{
	return {
		x + field_type::OFFSET[dir][0],
		y + field_type::OFFSET[dir][1]
	};
}

inline bool Bot::valid(
	PointI const &to,
	field_type const &f
) const
{
	return to.y >= 0 && to.y < f.h;
}





// end
