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
	return;
}

void Bot::update(field_type &f)
{
	++age;
	++worldage;


	auto &cell = f.at(x, y);
	double const delta = stepprice() + age * agesteptax();

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
	for(int count = 0; count < REPEAT_COMMAND_COUNT; ++count);
	{
		switch(getaction(brain[p]))
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
			jump( getjumpf( brain[p] ) );
			return;

		case EAT:
			eat(f, getarg(brain[p]) );
			jump( getjumpf( brain[p] ) );
			return;

		case TURN:
			turn( getarg( brain[p] ) );
			jump( getjumpf( brain[p] ) );
			break;

		case CHECK:
			if( check(f, getarg(brain[p])) )
				jump( getjumpf( brain[p] ) );
			else
				jump( getjumps( brain[p] ) );
			break;

		default:
			throw 1;

		}
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

void Bot::eat(field_type &f, neuron_type arg)
{
	auto &toc = f.neart(x, y, dir);
	switch(arg)
	{
	case 0:
		if(toc.plant)
		{
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
		}
		break;

	case 1:
		if(toc.body)
		{
			static int COUNT_EAT_BODY = 0;
			++COUNT_EAT_BODY;
			if(COUNT_EAT_BODY % 100 == 0)
				cout << "Body: " << COUNT_EAT_BODY/100 << " * 100" << endl;
			auto &body = *toc.body;
			if( !( body.energy > maxenergy() - energy ) )
			{
				energy += body.energy;
				delete toc.body;
				toc.body = nullptr;
			}
			else
			{
				double const delta = maxenergy() - energy;
				body.energy -= delta;
				energy += delta;
			}
		}
		break;

	case 2:
		if(toc.mineral)
		{
			static int COUNT_EAT_MINERAL = 0;
			++COUNT_EAT_MINERAL;
			if(COUNT_EAT_MINERAL % 1000 == 0)
				cout << "Mineral: " << COUNT_EAT_MINERAL/1000 << " * 1000" << endl;
			auto &mineral = *toc.mineral;
			double const delta = min(
				MINERAL_TAKE,
				maxenergy() - energy
			);
			if( !(mineral.energy > delta) )
			{
				energy += mineral.energy;
				delete toc.mineral;
				toc.mineral = nullptr;
			}
			else
			{
				mineral.energy -= delta;
				energy += delta;
			}
		}
		break;

	case 3:
		{
			static int COUNT_EAT_AIR = 0;
			++COUNT_EAT_AIR;
			if(COUNT_EAT_AIR % 10000 == 0)
				cout << "Air: " << COUNT_EAT_AIR/10000 << " * 10000" << endl;
			double const delta = toc.airenergy * AIR_TAKE_FACTOR;
			toc.airenergy -= delta;
			energy += delta;
		}
		break;

	default:
		throw 1;
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

bool Bot::check(field_type const &f, neuron_type arg)
{
	auto const &toc = f.neart(x, y, dir);

	switch(arg)
	{
	case 0:
		return !toc.bot && !toc.body;
	case 1:
		return toc.plant;
	case 2:
		return toc.bot;
	case 3:
		return toc.body;
	case 4:
		return toc.mineral;
	default:
		throw 1;
	}
}

inline void Bot::jump(neuron_type jmp)
{
	p = jmp;
	return;
}



// private help
Bot::neuron_type Bot::random_neuron()
{
	static constexpr neuron_type ACTIONS[] = {
		NUL,
		MOVE,

		EAT,
		EAT | (1 << ARG_OFFSET),
		EAT | (2 << ARG_OFFSET),
		EAT | (3 << ARG_OFFSET),

		TURN,
		TURN | (1 << ARG_OFFSET),
		TURN | (2 << ARG_OFFSET),

		CHECK,
		CHECK | (1 << ARG_OFFSET),
		CHECK | (2 << ARG_OFFSET),
		CHECK | (3 << ARG_OFFSET),
		CHECK | (4 << ARG_OFFSET)
	};

	static constexpr int const
		ACTIONS_SIZE = sizeof(ACTIONS) / sizeof(neuron_type);

	static std::uniform_int_distribution<int>
		actiondis(0, ACTIONS_SIZE-1),
		jumpdis(0, BRAIN_SIZE-1);



	return
		( jumpdis(dre) << JUMPS_OFFSET ) |
		( jumpdis(dre) << JUMPF_OFFSET ) |
		( ACTIONS[ actiondis(dre) ] << ACTION_OFFSET );
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
