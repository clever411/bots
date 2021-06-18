#include "Bot.hpp"

#include <iostream>

#include <field/BotField.hpp>
#include <field/Cell.hpp>

#include "Body.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"


using namespace clever;
using namespace std;





// objects
uniform_int_distribution<int> dirdis(0, BotField::OFFSET_COUNT);

double Bot::energy_from_air = 0.0;
double Bot::energy_from_plants = 0.0;
double Bot::energy_from_body = 0.0;
double Bot::energy_from_minerals = 0.0;





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

	// step
	bool isdie;
	spend_energy(f, delta, isdie);
	if(isdie)
		return;
	cell.energy += delta;
	

	
	// bud
	if(
		energy > budreq() &&
		sqrt(
			(energy - budreq()) /
			(maxenergy() - budreq())
		) > (double)rand() / RAND_MAX
	)
	{
		int choice;
		int count = -1;
		do
		{
			choice = dirdis(dre);
			++count;
		}
		while(
			( !valid(f, choice) ||
			  f.neart(x, y, choice).bot ||
			  f.neart(x, y, choice).body ) &&
			count < REPEAT_COMMAND_COUNT
		);


		if(count != REPEAT_COMMAND_COUNT)
		{
			PointI to = f.getxy( &f.neart(x, y, choice) );
			Bot *bot = bud();
			bot->x = to.x;
			bot->y = to.y;
			f.at(to).bot = bot;

			return;
		}
	}
	
	

	// on brain
	for(int count = 0; count < REPEAT_COMMAND_COUNT; ++count)//; RIGHT?
	{
		switch(getaction(brain[p]))
		{
		case NUL:
		{
			int i = 0;
			for(; getaction(brain[p]) == NUL && i != BRAIN_SIZE; ++i)
				p = (p + 1) % BRAIN_SIZE;
			if(i == BRAIN_SIZE)
				return;
			break;
		}

		case MOVE:
			move( f, isdie );
			if(isdie)
				return;
			p = getjumpf( brain[p] );
			return;

		case EAT:
			eat( f, getarg(brain[p]) );
			p = getjumpf( brain[p] );
			return;

		case TURN:
			turn( getarg( brain[p] ) );
			p = getjumpf( brain[p] );
			break;

		case CHECK:
			if( check(f, getarg(brain[p])) )
				p = getjumpf( brain[p] );
			else
				p = getjumps( brain[p] );
			break;

		default:
			throw logic_error("Bot::update() -> action is unknown");

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
		braindis(0, BRAIN_SIZE-1);

	// bud
	Bot *child = new Bot(*this);
	child->age = 0;
	++child->generation;
	child->dir = dirdis(dre);
	child->p = 0;
	double const delta = budprice();
	energy -= delta;
	child->energy = delta;


	// mutate
	child->brain[ braindis(dre) ] = random_neuron();
	child->gen.mutate();


	return child;
}

void Bot::move(field_type &f, bool &isdie)
{
	// is valid
	auto to = getto();
	if( !valid(f, to) )
		return;

	// is empty
	f.correct(to);
	auto &toc = f.at(to);
	if(toc.bot || toc.body)
		return;

	// spend energy
	double const delta = MOVE_PRICE_FACTOR * (stepprice() + age * agesteptax());
	spend_energy(f, delta, isdie);
	if(isdie)
		return;
	f.at(x, y).energy += delta;

	// move
	f.at(x, y).bot = nullptr;
	x = to.x;
	y = to.y;
	toc.bot = this;

	return;
}

bool Bot::eat(field_type &f, neuron_type arg)
{
	auto &toc = f.neart(x, y, dir);
	switch(arg)
	{
	case 0:
		if(toc.plant)
		{
			auto &plant = *toc.plant;
			double take = min(maxenergy() - energy, gen.plant());
			if( !( plant.energy > take ) )
			{
				energy += plant.energy;
				energy_from_plants += plant.energy;
				delete toc.plant;
				toc.plant = nullptr;
			}
			else
			{
				plant.energy -= take;
				energy += take;
				energy_from_plants += take;
			}

			return true;
		}
		return false;

	case 1:
		if(toc.body)
		{
			auto &body = *toc.body;
			double const delta = min(
				maxenergy() - energy,
				gen.body()
			);
			if( !( body.energy > delta ) )
			{
				energy += body.energy;
				energy_from_body += body.energy;
				delete toc.body;
				toc.body = nullptr;
			}
			else
			{
				body.energy -= delta;
				energy += delta;
				energy_from_body += delta;
			}

			return true;
		}
		return false;

	case 2:
		{
			double const delta = min(
				maxenergy() - energy,
				gen.mineral()
			);
			if( !(toc.mineral.energy > delta) )
				energy += toc.mineral.energy,
				energy_from_minerals += toc.mineral.energy,
				toc.mineral.energy = 0.0;
			else
				toc.mineral.energy -= delta,
				energy += delta,
				energy_from_minerals += delta;
		}
		return true;

	case 3:
		{
			auto &to = f.at(x, y);
			double const delta = to.airenergy * gen.air();
			to.airenergy -= delta;
			energy += delta;
			energy_from_air += delta;
		}
		return true;

	default:
		throw 1;
	}
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
		return !toc.bot && !toc.body && valid(f, dir);
	case 1:
		return toc.plant;
	case 2:
		return toc.bot;
	case 3:
		return toc.body;
	default:
		throw 1;
	}
}

void Bot::spend_energy( field_type &f, double delta, bool &isdie )
{
	if( !( energy - delta > deathedge() ) )
	{
		f.at(x, y).bot = nullptr,
		f.at(x, y).body = new Body { energy, 0 };
		delete this;
		isdie = true;
	}
	else
		energy -= delta;

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
		CHECK | (3 << ARG_OFFSET)
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
	field_type const &f,
	PointI const &to
)
{
	return to.y >= 0 && to.y < f.h;
}

inline bool Bot::valid(
	field_type const &f,
	int dir
) const
{
	return y + f.OFFSET[dir][1] >= 0 && y + f.OFFSET[dir][1] < f.h;
}





// end
