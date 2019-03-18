#include "bot_field.hpp"

#include <cmath>
#include <iostream>


using namespace std;





// objects
Bot const Bot::DEFAULT = {
	0.0, 0,
	1.0, 1.0, 1.0, 1.0, 1.0
};

Plant const Plant::DEFAULT = {
	0.0
};

Cell const Cell::DEFAULT = {
	0.0, nullptr, nullptr
};

std::default_random_engine dre( time(0) );
std::uniform_real_distribution<double> realdis(0.0, 1.0);
std::uniform_int_distribution<int> dirdis(0, OFFSET_SIZE-1);
std::uniform_int_distribution<int> mutdis(0, Bot::CHARACTERS_COUNT-1);





// bot functions
Bot *Bot::bud()
{
	// burn
	Bot *child = new Bot(*this);
	child->age = 0;
	double const delta = budprice();
	energy -= delta;
	child->energy = delta;



	// mutation
	float *characts[ CHARACTERS_COUNT ] = {
		&child->steppricek, &child->agetaxk,
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
	for(auto cell : plants)
		delete cell->plant;
	plants.clear();
	for(auto cell : bots)
		delete cell->bot;
	bots.clear();
	delete[] d;
	return *this;
}


void BotField::init_botfield(int width, int height)
{
	init(width, height);
	clear(Cell::DEFAULT);
	return;
}

void BotField::reset()
{
	clear(Cell::DEFAULT);
	for(auto cell : plants)
		delete cell->plant;
	plants.clear();
	for(auto cell : bots)
		delete cell->bot;
	summen = grounden = planten = boten = 0.0;
	bots.clear();
}


void BotField::update_field()
{
	update_ground();
	update_bots(); // first is bots becouse they eating plants
	update_plants();

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
	smoothf_.clear(0.0);



	// main
	double delta;

	for(int y = 0; y < h; ++y)
	for(int x = 0; x < w; ++x)
	{
		delta = at(x, y).energy * Cell::SMOOTH;
		at(x, y).energy -= delta;

		delta /= OFFSET_SIZE;
		for(int i = 0; i < OFFSET_SIZE; ++i)
		{
			smoothf_.tapeAt(
				x + OFFSET[i][0],
				y + OFFSET[i][1]
			) += delta;
		}
	}

	for(int y = 0; y < h; ++y)
	for(int x = 0; x < w; ++x)
	{
		at(x, y).energy += smoothf_.at(x, y);
	}



	return;
}

void BotField::update_bots()
{
	// objects
		// main
	Cell *cell;
	Bot *bot;
	int x, y;
		
		// for step
	double delta;

		// for bud and move
	int choice;
	int count;
	Cell *to;



	// loop
	for(auto b = bots.begin(), e = bots.end(); b != e; ++b)
	{
		cell = *b;
		bot = cell->bot;
		get(cell, x, y);


		// step
		delta = bot->stepprice() + bot->age * bot->agetax();
		++bot->age;
		if( !( bot->energy > delta ) )
		{
			cell->energy += bot->energy;
			grounden += bot->energy;
			boten -= bot->energy;
			delete cell->bot;
			cell->bot = nullptr;
			bots.erase(b++);
			--b;
			continue;
		}
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
				to = &tapeAt(x+OFFSET[choice][0], y+OFFSET[choice][1]);
				++count;
			}
			while( (to->plant || to->bot) && count < 16 );

			if(count == 16) // antifreeze
				continue;
			
			to->bot = bot->bud();
			bots.push_front(to); 
			continue;
		}
		
		
		// move
		count = 0;
		do
		{
			choice = dirdis(dre);
			to = &tapeAt( x+OFFSET[choice][0], y+OFFSET[choice][1] );
			++count;
		}
		while( to->bot && count < 16 );

		if(count == 16) // antifreeze
			continue;

		cell->bot = nullptr;
		to->bot = bot;
		cell = *b = to;
		
		
		// eat
		if(to->plant)
		{
			auto &plant = *to->plant;
			if( !( bot->maxenergy() - bot->energy < plant.energy ) )
			{
				bot->energy += plant.energy;
				boten += plant.energy;
				planten -= plant.energy;
				delete to->plant;
				to->plant = nullptr; // remove from list 'plants' in 'update_plants'
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


		continue;
	}



	return;
}

void BotField::update_plants()
{
	// update plants
	double delta;
	Cell *cell;
	Plant *plant;

	for(auto b = plants.begin(), e = plants.end(); b != e; ++b)
	{
		cell = *b;
		plant = cell->plant;
		if(!plant)
		{
			plants.erase(b++);
			--b;
			continue;
		}
		delta = min(
			(Plant::MAX_ENERGY - plant->energy) * Plant::TAKE_TO_SELF,
			cell->energy * Plant::TAKE_FROM_EATH
		);
		cell->energy -= delta;
		grounden -= delta;
		plant->energy += delta;
		planten += delta;
	}



	// sow plants
	for(auto b = begin(), e = end(); b != e; ++b)
	{
		if( b->plant || b->bot )
			continue;
		if(
			(
				b->energy /
				Cell::DEFAULT_GROUND_ENERGY
			) * Plant::BURN_CHANCE >
			realdis(dre)
		)
		{
			b->plant = new Plant{ 0.0 };
			plants.push_back(b);
		}
	}



	return;
}



bool BotField::push(int x, int y, Bot *bot)
{
	auto *cell = &at(x, y);
	if(cell->bot)
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
	if(cell->plant)
		return false;
	cell->plant = plant;
	planten += plant->energy;
	summen += plant->energy;
	plants.push_back(cell);
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





// end