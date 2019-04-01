#include "BotField.hpp"

#include <cmath>
#include <iostream>

#include <clever/HelpFunction.hpp>


using namespace clever;
using namespace std;





// objects
std::default_random_engine dre( time(0) );
std::uniform_real_distribution<double> realdis;





// create, destroy
BotField::BotField() {} 

BotField::~BotField()
{
	if(smoothf_.d)
		smoothf_.free();
	return;
}

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

	delete[] d;

	return *this;
}



// core
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

	age = 0;
	summen = grounden = planten = boten = 0.0;
	set_cells_();

	return;
}



// update
void BotField::update()
{
	update_ground();
	update_standing();
	return;
}




// enter
bool BotField::push(int x, int y, Bot *bot)
{
	auto *cell = &at(x, y);
	if(cell->plant || cell->bot || cell->body)
		return false;
	bot->worldage = age;
	bot->x = x;
	bot->y = y;
	cell->bot = bot;
	boten += bot->energy;
	summen += bot->energy;
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

double BotField::push(int x, int y)
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
		push(x, y);
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



// private implement
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
			if( y + OFFSET[i][1] < 0 || y + OFFSET[i][1] >= h )
			{
				st += b->temp;
				continue;
			}
			t[i] = neart(x, y, i).temp;
			st += t[i];
		}

		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if( y + OFFSET[i][1] < 0 || y + OFFSET[i][1] >= h )
			{
				 b->energy += delta * b->temp / st;
				 continue;
			}
			smoothf_.neart(x, y, i) += delta * t[i] / st;
		}

	}


	for(int i = 0; i < w*h; ++i)
		d[i].energy += smoothf_.d[i];


	return;
}

void BotField::update_standing()
{
	++age;

	double delta;
	Plant *plant;
	Body *body;

	for(auto b = begin(), e = end(); b != e; ++b)
	{
		if(b->bot && b->bot->worldage < age)
			b->bot->update(*this);

		// plant
		if(b->plant)
		{
			plant = b->plant;
			delta = min(
				(Plant::MAX_ENERGY - plant->energy) * Plant::TAKE_TO_SELF,
				b->energy * Plant::TAKE_FROM_EATH
			);
			b->energy -= delta;
			grounden -= delta;
			plant->energy += delta;
			planten += delta;
		}

		// body
		if(b->body)
		{
			body = b->body;
			delta = Body::ROT_SPEED * pow(
				Body::ROT_ACCELERATION, sqrt(double(body->age))
			);

			if( !(body->energy > delta) )
			{
				b->energy += body->energy;
				grounden += body->energy;
				bodyen -= body->energy;

				delete body;
				b->body = nullptr;
			}
			else
			{
				body->energy -= delta;
				bodyen -= delta;
				b->energy += delta;
				grounden += delta;

				++body->age;
			}
		}

		// saw plant
		if(
			!b->plant && !b->bot && !b->body &&
			(
				b->energy /
				Cell::DEFAULT_GROUND_ENERGY
			) * Plant::BURN_CHANCE >
			realdis(dre)
		)
		{
			b->plant = new Plant{ 0.0 };
		}

	}



	return;
}

void BotField::set_cells_()
{
	int x, y;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		getxy(b, x, y);
		*b = Cell();
		b->temp = 1.0 + pow(double(y), 2.0);
	}
	return;
}





// end
