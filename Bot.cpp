#include "Bot.hpp"

#include <iostream>

#include "BotField.hpp"
#include "Cell.hpp"
#include "Plant.hpp"
#include "Body.hpp"
#include "Mineral.hpp"


using namespace clever;
using namespace std;





// objects
uniform_int_distribution<int> mutdis(0, Bot::CHARACTERS_COUNT-1);
uniform_int_distribution<int> turndis(0, 1);
uniform_int_distribution<int> braindis(0, Bot::BRAIN_SIZE-1);
uniform_int_distribution<int> dirdis(0, BotField::OFFSET_COUNT-1);
uniform_int_distribution<Bot::neuron_type> neurondis(0u, 255u);





// core
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
	neuron_type action, arg;
	while(count < REPEAT_COMMAND_COUNT)
	{
		action = brain[p] & MASK;
		arg = brain[p] >> 3;

		switch(action)
		{
		case NUL:
		{
			int i = 0;
			for(; brain[p] & MASK == NUL && i != BRAIN_SIZE; ++i)
				incp();
			if(i == BRAIN_SIZE)
				return;
			break;
		}

		case MOVE:
			move(f);
			incp();
			return;

		case EAT:
			eat(f);
			incp();
			return;

		case TURN:
			turn(arg%3);
			incp();
			break;

		case CHECK:
			check(f);
			incp();
			break;

		case CALL:
			call(arg%FUN_COUNT);
			break;

		case JUMP_FORWARD:
			jumpf(arg);
			break;

		case JUMP_BACKWARD:
			jumpb(arg);
			break;

		default:
			throw 1;

		}

		++count;
	}



	return;
}

Bot *Bot::bud()
{
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

	child->brain[ braindis(dre) ] = neurondis(dre);



	return child;
}



// actions
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

void Bot::check(field_type const &f)
{
	auto to = getto();
	auto const &toc = f.att(to);

	int off = 0;
	if(!valid(to, f) || toc.bot || toc.body)
		off = 2;
	else if(toc.plant)
		off = 1;

	p = (p + off*CHECK_OFFSET) % BRAIN_SIZE;
	
	return;
}

void Bot::call(neuron_type arg)
{
	p = MAINFUN_SIZE + arg*FUN_SIZE;
	return;
}

void Bot::jumpf(neuron_type arg)
{
	p = (p + arg) % BRAIN_SIZE;
	return;
}

void Bot::jumpb(neuron_type arg)
{
	p = tape(p-(int)arg, BRAIN_SIZE);
	return;
}



// private help
inline PointI Bot::getto() const
{
	return {
		x + field_type::OFFSET[dir][0],
		y + field_type::OFFSET[dir][1]
	};
}

inline void Bot::incp()
{
	p = (p + 1) % BRAIN_SIZE;
	return;
}

inline bool Bot::valid(
	PointI const &to,
	field_type const &f
) const
{
	return to.y >= 0 && to.y < f.h;
}





// end
