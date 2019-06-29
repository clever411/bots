#include "BotField.hpp"

#include <cmath>
#include <iostream>

#include <clever/HelpFunction.hpp>

#include "Body.hpp"
#include "Bot.hpp"
#include "Cell.hpp"
#include "Mapping.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"


using namespace clever;
using namespace std;





// objects
std::default_random_engine dre( time(0) );





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
	mapping.free();

	return *this;
}



// core
void BotField::init_botfield(int width, int height)
{
	init(width, height);
	init_mapping(*this, mapping, MAPPING_KOFF);
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
	summen = grounden = airen =
		planten = boten = bodyen = mineralen = 0.0;
	set_cells_();

	return;
}



// update
void BotField::update()
{
	update_environment_();
	update_entities_();
	calculate_energy_();
	return;
}




// enter
bool BotField::push(int x, int y, Bot *bot, bool calc)
{
	auto *cell = &at(x, y);
	if(cell->bot || cell->body)
		return false;
	bot->worldage = age;
	bot->x = x;
	bot->y = y;
	cell->bot = bot;
	if(calc)
		calculate_energy_();
	return true;
}

bool BotField::push(int x, int y, Plant *plant)
{
	auto *cell = &at(x, y);
	if(cell->plant || cell->bot || cell->body)
		return false;
	cell->plant = plant;
	calculate_energy_();
	return true;
}

void BotField::push(int x, int y, bool calc)
{
	auto &cell = at(x, y);
	cell.energy = Cell::DEFAULT_GROUND_ENERGY;
	if(calc)
		calculate_energy_();
	return;
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
		push(x, y, false);
	}

	calculate_energy_();
	return;
}

void BotField::ravage_ground(double k)
{
	double delta;
	for(auto b = begin(), e = end(); b != e; ++b)
		b->energy *= k;
	calculate_energy_();
	return;
}

void BotField::random_bots(int count)
{
	uniform_int_distribution<int>
		widthdis(0, w-1), heightdis(0, h-1);
	Bot *bot = new Bot;
	int x, y;
	for(int i = 0; i < count; ++i)
	{
		bot->energy = bot->budprice();
		y = heightdis(dre);
		x = widthdis(dre)*2 + (y%2 ? 1 : 0);
		if(push(x, y, bot, false))
			bot = new Bot;
	}
	delete bot;
	calculate_energy_();
	return;
}



// private implement
inline bool BotField::valid(PointI const &p)
{
	return p.y >= 0 && p.y < h;
}

inline bool BotField::valid(PointI const &p, int dir)
{
	return p.y + OFFSET[dir][1] >= 0 && p.y + OFFSET[dir][1] < h;
}

void BotField::update_environment_()
{
	// prepare
	if( smoothf_.w != w || smoothf_.h != h )
	{
		if(smoothf_.d)
			smoothf_.free();
		smoothf_.init(w, h);
	}


	// ground
	smoothf_.zeroize();

	double delta;
	PointI p;

	for(auto b = begin(), e = end(); b != e; ++b)
	{
		p = getxy(b);

		// to air
		delta = b->energy * Cell::TOAIR_FACTOR;
		b->energy -= delta;
		b->airenergy += delta;

		// to other
		delta = b->energy * Cell::SMOOTH_FACTOR;
		b->energy -= delta;

		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if(!valid(p, i))
				b->energy += delta * b->temp / b->tempenv;
			else
				smoothf_.neart(p, i) += delta * neart(p, i).temp / b->tempenv;
		}
	}

	for(int i = 0; i < w*h; ++i)
		d[i].energy += smoothf_.d[i];
	
	

	// air
	smoothf_.zeroize();
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		p = getxy(b);

		delta = b->airenergy * Cell::AIRSMOOTH_FACTOR;
		b->airenergy -= delta;

		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if(!valid(p, i))
				b->airenergy += delta * b->airtemp / b->airtempenv;
			else
				smoothf_.neart(p, i) += delta * neart(p, i).airtemp / b->airtempenv;
		}
	}

	for(int i = 0; i < w*h; ++i)
		d[i].airenergy += smoothf_.d[i];



	return;
}

void BotField::update_entities_()
{
	++age;

	double delta;
	Plant *plant;
	Body *body;

	int x, y;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		if(b->bot && b->bot->worldage < age)
			b->bot->update(*this);

		// plant
		if(b->plant)
			b->plant->update(*this);

		// body
		if(b->body)
			b->body->update(*b);

		if(b->mineral)
			b->mineral->update(*b);

		// saw plant
		if(
			!b->plant &&
			(
				b->energy /
				Cell::DEFAULT_GROUND_ENERGY
			) * Plant::BURN_CHANCE > (double)rand() / RAND_MAX
		)
		{
			getxy(b, x, y);
			b->plant = new Plant{ x, y, 0.0 };
		}
	}



	return;
}


void BotField::calculate_energy_()
{
	grounden = airen =
		planten = boten =
		bodyen = mineralen = 0.0;
	mapping.zeroize();

	MapUnit *mp;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		mp = &mapping.at( map( getxy(b), MAPPING_KOFF ) );
		++mp->density;

		grounden += b->energy, mp->grounden += b->energy;
		airen += b->airenergy, mp->airen += b->airenergy;

		if(b->plant)
			planten += b->plant->energy,
			mp->planten += b->plant->energy;
		if(b->bot)
			boten += b->bot->energy,
			mp->boten += b->bot->energy;
		if(b->body)
			bodyen += b->body->energy,
			mp->bodyen += b->body->energy;
		if(b->mineral)
			mineralen += b->mineral->energy,
			mp->mineralen += b->mineral->energy;
	}

	summen = grounden + airen + planten + boten + bodyen + mineralen;
	return;
}


void BotField::set_cells_()
{
	PointI p;
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		p = getxy(b);
		*b = Cell();
		b->temp = 1.0 + pow(double(p.y), 2.0);
		b->airtemp = 1.0 + pow(double(h-1-p.y), 3.0);
	}

	for(auto b = begin(), e = end(); b != e; ++b)
	{
		p = getxy(b);
		b->tempenv = 0.0;
		b->airtempenv = 0.0;
		for(int i = 0; i < OFFSET_COUNT; ++i)
		{
			if(!valid(p, i))
			{
				b->tempenv += b->temp;
				b->airtempenv += b->airtemp;
			}
			else
			{
				b->tempenv += neart(p, i).temp;
				b->airtempenv += neart(p, i).airtemp;
			}
		}
	}

	return;
}





// end
