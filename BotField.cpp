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
	worker_.set(w, h);
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
	update_entities_();
	update_environment_();
	return;
}




// enter
bool BotField::push(int x, int y, Bot *bot)
{
	auto *cell = &at(x, y);
	if(cell->bot || cell->body)
		return false;
	bot->worldage = age;
	bot->x = x;
	bot->y = y;
	cell->bot = bot;
	return true;
}

bool BotField::push(int x, int y, Plant *plant)
{
	auto *cell = &at(x, y);
	if(cell->plant || cell->bot || cell->body)
		return false;
	cell->plant = plant;
	return true;
}

void BotField::push(int x, int y)
{
	auto &cell = at(x, y);
	if(cell.energy < Cell::DEFAULT_GROUND_ENERGY)
		cell.energy = Cell::DEFAULT_GROUND_ENERGY;
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
		push(x, y);
	}

	return;
}

void BotField::ravage_ground(double k)
{
	double delta;
	for(auto b = begin(), e = end(); b != e; ++b)
		b->energy *= k;
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
		if(push(x, y, bot))
			bot = new Bot;
	}
	delete bot;
	return;
}


void BotField::calculate_energy()
{
	// Почему-то при распараллеливании производительность уменьшается

	grounden = airen =
		planten = boten =
		bodyen = mineralen = 0.0;
	mapping.zeroize();



	auto athis = this;
	// worker_.update = [athis](int x, int y)->void
	auto fun = [athis](int x, int y)->void
	{
		auto &cell = athis->at(x, y);
		MapUnit &mp = athis->mapping.at( map( {x, y}, MAPPING_KOFF ) );
		++mp.density;

		athis->grounden += cell.energy, mp.grounden += cell.energy;
		athis->airen += cell.airenergy, mp.airen += cell.airenergy;

		if(cell.plant)
			athis->planten += cell.plant->energy,
			mp.planten += cell.plant->energy;
		if(cell.bot)
			athis->boten += cell.bot->energy,
			mp.boten += cell.bot->energy;
		if(cell.body)
			athis->bodyen += cell.body->energy,
			mp.bodyen += cell.body->energy;
		athis->mineralen += cell.mineral.hidenergy + cell.mineral.energy,
		mp.mineralen += cell.mineral.hidenergy + cell.mineral.energy;

		return;
	};
	// worker_();

	int x, y;
	for(int i = 0; i < w*h; ++i)
		getxy(i, x, y), fun(x, y);

	summen = grounden + airen + planten + boten + bodyen + mineralen;
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
	// А здесь при распараллеливании производительность заметно увеличивается

	// prepare
	if( smoothf_.w != w || smoothf_.h != h )
	{
		if(smoothf_.d)
			smoothf_.free();
		smoothf_.init(w, h);
	}
	smoothf_.zeroize();


	// with worker
	auto athis = this;
	auto afun = &BotField::update_ground_;
	worker_.update = [=](int x, int y) { (athis->*afun)(x, y); };
	worker_();

	worker_.update = [=](int x, int y)->void
	{
		athis->at(x, y).energy += athis->smoothf_.at(x, y).ground;
		athis->at(x, y).airenergy += athis->smoothf_.at(x, y).air;
		return;
	};
	worker_();


	// no worker
	// int x, y;
	// for(int i = 0; i < w*h; ++i)
		// getxy(i, x, y), update_ground_(x, y);

	// for(int i = 0; i < w*h; ++i)
		// d[i].energy += smoothf_.d[i].ground,
		// d[i].airenergy += smoothf_.d[i].air;
	

	return;
}

void BotField::update_ground_(int x, int y)
{
	double grounddelta, airdelta;
	double &sground = smoothf_.at(x, y).ground;
	double &sair = smoothf_.at(x, y).air;
	auto &cell = at(x, y);

	grounddelta = cell.energy * Cell::TOAIR_FACTOR;
	sground -= grounddelta;
	sair += grounddelta;

		// to other
	grounddelta = cell.energy * Cell::SMOOTH_FACTOR;
	sground -= grounddelta;

	// air
	airdelta = cell.airenergy * Cell::AIRSMOOTH_FACTOR;
	sair -= airdelta;

	for(int i = 0; i < OFFSET_COUNT; ++i)
	{
		// ground
		if(!valid({x, y}, i))
			sground += grounddelta * cell.temp / cell.tempenv;
		else
			smoothf_.neart(x, y, i).ground += grounddelta * neart(x, y, i).temp / cell.tempenv;

		// air
		if(!valid({x, y}, i))
			sair += airdelta * cell.airtemp / cell.airtempenv;
		else
			smoothf_.neart(x, y, i).air += airdelta * neart(x, y, i).airtemp / cell.airtempenv;
	}


	return;
}



void BotField::update_entities_()
{
	// Почему-то при распараллеливании производительность уменьшается

	++age;

	int x, y;
	for(auto b = begin(), e = end(); b != e; ++b)
		getxy(b, x, y), update_entity_(x, y);

	// auto athis = this;
	// auto afun = &BotField::update_entity_;
	// worker_.update = [=](int x, int y) { (athis->*afun)(x, y); };
	// worker_();

	return;
}

void BotField::update_entity_(int x, int y)
{
	auto &cell = at(x, y);

	// bot
	if(cell.bot && cell.bot->worldage < age)
		cell.bot->update(*this);

	// plant
	if(cell.plant)
		cell.plant->update(*this);
	else if(
		(cell.energy / Cell::DEFAULT_GROUND_ENERGY) *
		Plant::BURN_CHANCE > (double)rand() / RAND_MAX
	)
		cell.plant = new Plant{ x, y, 0.0 };

	// body
	if(cell.body)
		cell.body->update(cell);

	// mineral
	cell.mineral.update(cell);


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
