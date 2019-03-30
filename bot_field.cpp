#include "bot_field.hpp"

#include <cmath>
#include <iostream>

#include <clever/HelpFunction.hpp>


using namespace clever;
using namespace std;





// objects
Plant const Plant::DEFAULT = {
	0.0
};

Bot const Bot::DEFAULT = {
	0.0, 0, 0, 0,
	1.0, 1.0, 1.0, 1.0, 1.0,
	{
		CHECK,
		MOVE, JUMP_BACKWARD | (0x02 << 3), NUL, NUL,
		EAT, MOVE, JUMP_BACKWARD | (0x07 << 3), NUL,
		TURN | (0x02 << 3), JUMP_BACKWARD | (0x0a << 3), NUL, NUL,
		TURN | (0x02 << 3), JUMP_BACKWARD | (0x0e << 3), NUL, NUL,
		NUL
	},
	0
};

Body const Body::DEFAULT = {
	0.0, 0
};

Cell const Cell::DEFAULT = {
	0.0, 1.0, nullptr, nullptr, nullptr
};

std::default_random_engine dre( time(0) );
std::uniform_real_distribution<double> realdis(0.0, 1.0);
std::uniform_int_distribution<int> dirdis(0, BotField::OFFSET_COUNT-1);
std::uniform_int_distribution<int> mutdis(0, Bot::CHARACTERS_COUNT-1);
std::uniform_int_distribution<int> turndis(0, 1);
std::uniform_int_distribution<int> braindis(0, Bot::BRAIN_SIZE-1);
std::uniform_int_distribution<uint8_t> neurondis(0u, 255u);





// bot functions
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

	brain[ braindis(dre) ] = neurondis(dre);



	return child;
}





// destroy
BotField::~BotField()
{
	if(smoothf_.d)
		smoothf_.free();
	return;
}





// core
BotField &BotField::free()
{
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		if(b->plant)
			delete b->plant;
		if(b->bot)
			delete b->bot;
		if(b->body)
			delete b->body;
	}

	bots.clear();
	delete[] d;

	return *this;
}


void BotField::init_botfield(int width, int height)
{
	init(width, height);
	set_cells_();
	return;
}

void BotField::reset()
{
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		if(b->plant)
			delete b->plant;
		if(b->bot)
			delete b->bot;
		if(b->body)
			delete b->body;
	}

	bots.clear();
	summen = grounden = planten = boten = 0.0;
	set_cells_();

	return;
}


void BotField::update_field()
{
	update_ground();
	update_standing();
	update_bots();

	return;
}

void BotField::update_ground()
{
	// prepare
	if( smoothf_.w != w || smoothf_.h != h )
	{
		if(smoothf_.d)
			smoothf_.free();
		smoothf_.init(w, h);
	}
	smoothf_.zeroize();



	// main
	double delta;
	double t[OFFSET_COUNT];
	double st;

	int x, y;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		getxy(b, x, y);
		delta = b->energy * Cell::SMOOTH;
		b->energy -= delta;

		st = 0.0;
		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if(y+OFFSET[i][1] < 0 || y+OFFSET[i][1] >= h)
			{
				st += b->temp;
				continue;
			}
			t[i] = neart(x, y, i).temp;
			st += t[i];
		}

		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if(y+OFFSET[i][1] < 0 || y+OFFSET[i][1] >= h)
			{
				b->energy += delta*b->temp/st;
				continue;
			}
			smoothf_.neart(x, y, i) += delta*t[i]/st;
		}
	}

	for(auto b = begin(), e = end(); b != e; ++b)
		b->energy += smoothf_.d[b-d];



	return;
}


void BotField::update_standing()
{
	double delta;
	Plant *plant;
	Body *body;

	for(auto cell = begin(), e = end(); cell != e; ++cell)
	{
		// plant
		if(cell->plant)
		{
			plant = cell->plant;
			delta = min(
				(Plant::MAX_ENERGY - plant->energy) * Plant::TAKE_TO_SELF,
				cell->energy * Plant::TAKE_FROM_EATH
			);
			cell->energy -= delta;
			grounden -= delta;
			plant->energy += delta;
			planten += delta;
		}

		// body
		if(cell->body)
		{
			body = cell->body;
			delta = Body::ROT_SPEED * pow(
				Body::ROT_ACCELERATION, sqrt(double(body->age))
			);

			if( !(body->energy > delta) )
			{
				cell->energy += body->energy;
				grounden += body->energy;
				bodyen -= body->energy;

				delete body;
				cell->body = nullptr;
			}
			else
			{
				body->energy -= delta;
				bodyen -= delta;
				cell->energy += delta;
				grounden += delta;

				++body->age;
			}
		}

		// saw plant
		if(
			!cell->plant && !cell->bot && !cell->body &&
			(
				cell->energy /
				Cell::DEFAULT_GROUND_ENERGY
			) * Plant::BURN_CHANCE >
			realdis(dre)
		)
		{
			cell->plant = new Plant{ 0.0 };
		}
	}



	return;
}

void BotField::update_bots()
{
	// objects
		// main
	Cell *cell;
	Bot *bot;
	int x, y, tox, toy;
		
		// for step
	double delta;

		// for bud, on brain
	int choice;
	int count;
	Cell *to;
	uint8_t command, action, param;



	// loop
	for(auto b = bots.begin(), e = bots.end(); b != e; ++b)
	{
		cell = *b;
		bot = cell->bot;
		getxy(cell, x, y);


		// step
		delta = bot->stepprice() + bot->age * bot->agesteptax();
		++bot->age;

			// death
		if( !( bot->energy - delta > bot->deathedge() ) )
		{
			cell->body = new Body { bot->energy, 0 };
			bodyen += bot->energy;
			boten -= bot->energy;

			delete cell->bot;
			cell->bot = nullptr;
			bots.erase(b++);
			--b;
			continue;
		}

			// all right
		bot->energy -= delta;
		boten -= delta;
		cell->energy += delta;
		grounden += delta;
		

		
		// bud
		if(
			bot->energy > bot->budreq() &&
			sqrt(
				(bot->energy - bot->budreq()) /
				(bot->maxenergy() - bot->budreq())
			) > realdis(dre)
		)
		{
			count = 0;
			do
			{
				choice = dirdis(dre);
				to = &neart(x, y, choice);
				++count;
			}
			while( (
				to->plant || to->bot || to->body ||
				y+OFFSET[choice][1] < 0 || y+OFFSET[choice][1] >= h
			) && count < 16 );

			if(count == 16) // antifreeze
				continue;
			
			to->bot = bot->bud();
			bots.push_front(to); 
			continue;
		}
		
		

		// on brain
		count = 0;
		tox = x+OFFSET[bot->dir][0];
		toy = y+OFFSET[bot->dir][1];
		to = &att(tox, toy);
		while(count < Bot::REPEAT_COMMAND_COUNT)
		{
			command = bot->brain[bot->p];
			action = command & Bot::MASK;
			param = command >> 3;
			bot->p = (bot->p + 1) % Bot::BRAIN_SIZE;

			switch(action)
			{
			case Bot::NUL:
				break;

			case Bot::MOVE:
				if( toy < 0 || toy >= h || to->bot || to->body )
					goto break_brain_loop_label;

				cell->bot = nullptr;
				to->bot = bot;
				cell = *b = to;

				goto break_brain_loop_label;

			case Bot::EAT:
				if(to->plant)
				{
					auto &plant = *to->plant;
					if( !( plant.energy > bot->maxenergy() - bot->energy ) )
					{
						bot->energy += plant.energy;
						boten += plant.energy;
						planten -= plant.energy;
						delete to->plant;
						to->plant = nullptr;
					}
					else
					{
						delta = bot->maxenergy() - bot->energy;
						plant.energy -= delta;
						planten -= delta;
						bot->energy += delta;
						boten += delta;
					}
				}

				goto break_brain_loop_label;

			case Bot::TURN:
				switch(param%3)
				{
				case 0:
					bot->dir = tape(bot->dir-1, OFFSET_COUNT);
					break;
				case 1:
					bot->dir = tape(bot->dir+1, OFFSET_COUNT);
					break;
				case 2:
					bot->dir = tape(
						bot->dir + ( turndis(dre) == 0 ? -1 : 1 ),
						OFFSET_COUNT
					);
					break;
				default:
					throw 1;
				}
				tox = x + OFFSET[bot->dir][0];
				toy = y + OFFSET[bot->dir][1];
				to = &att(tox, toy);
				
				break;

			case Bot::CHECK:
				if(to->plant)
					bot->p = (bot->p + Bot::CHECK_OFFSET) % Bot::BRAIN_SIZE;
				else if(to->bot)
					bot->p = (bot->p + 2*Bot::CHECK_OFFSET) % Bot::BRAIN_SIZE;
				else if(to->body || toy < 0 || toy >= h)
					bot->p = (bot->p + 3*Bot::CHECK_OFFSET) % Bot::BRAIN_SIZE;
				
				break;

			case Bot::CALL:
				choice = param % Bot::FUN_COUNT;
				bot->p = Bot::MAINFUN_SIZE + Bot::FUN_SIZE*choice;
				
				break;

			case Bot::JUMP_FORWARD:
				bot->p = tape(bot->p-1+param, Bot::BRAIN_SIZE);
				break;

			case Bot::JUMP_BACKWARD:
				bot->p = tape(bot->p-1-param, Bot::BRAIN_SIZE);
				break;

			default:
				throw 1;

			}

			++count;
		}
	break_brain_loop_label:
		;



	}



	return;
}


bool BotField::push(int x, int y, Bot *bot)
{
	auto *cell = &at(x, y);
	if(cell->plant || cell->bot || cell->body)
		return false;
	cell->bot = bot;
	boten += bot->energy;
	summen += bot->energy;
	bots.push_back(cell);
	return true;
}

bool BotField::push(int x, int y, Plant *plant)
{
	auto *cell = &at(x, y);
	if(cell->plant || cell->bot || cell->body)
		return false;
	cell->plant = plant;
	planten += plant->energy;
	summen += plant->energy;
	return true;
}

double BotField::fillground(int x, int y)
{
	auto &cell = at(x, y);
	double const delta = Cell::DEFAULT_GROUND_ENERGY - cell.energy;
	cell.energy += delta;
	grounden += delta;
	summen += delta;
	return delta;
}


void BotField::random_fill(int cellcount)
{
	std::uniform_int_distribution<int>
		widthdis(0, w-1), heightdis(0, h-1);
	int x, y;
	for(int i = 0; i < cellcount; ++i)
	{
		y = heightdis(dre);
		x = widthdis(dre)*2 + (y%2 ? 1 : 0);
		fillground(x, y);
	}

	return;
}

void BotField::ravage_ground(double k)
{
	double delta;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		delta = b->energy * k;
		b->energy -= delta;
		grounden -= delta;
		summen -= delta;
	}
	return;
}





// private
void BotField::set_cells_()
{
	int x, y;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		getxy(b, x, y);
		*b = Cell::DEFAULT;
		b->temp = 40.0 - 39.0*y/h;
	}
	return;
}





// end
