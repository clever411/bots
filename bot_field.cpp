#include "bot_field.hpp"

#include <iostream>


using namespace std;





// objects
Bot const Bot::DEFAULT = {
	0.0, 0
};

Plant const Plant::DEFAULT = {
	0.0
};

Cell const Cell::DEFAULT = {
	0.0, nullptr, nullptr
};

std::default_random_engine BotField::dre_( time(0) );
std::uniform_real_distribution<double> BotField::realdis_(0.0, 1.0);
std::uniform_int_distribution<int> BotField::dirdis_(0, OFFSET_SIZE-1);





// destroy
BotField::~BotField()
{
	if(smoothf_.d)
		smoothf_.free();
	return;
}





// core
void BotField::init_botfield(int width, int height)
{
	init(width, height);
	clear(Cell::DEFAULT);
	return;
}


void BotField::update_field()
{
	update_ground();
	// first bots becouse they eating plants
	if(!bots.empty())
		update_bots();
	if(!plants.empty())
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
		delta = at(x, y).energy * SMOOTH;
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
		delta = STEP_PRICE + bot->age*AGE_TAX;
		++bot->age;
		if( !( bot->energy > delta ) )
		{
			cell->energy += bot->energy;
			delete cell->bot;
			cell->bot = nullptr;
			bots.erase(b++);
			--b;
			continue;
		}
		bot->energy -= delta;
		cell->energy += delta;
		
		
		// bud
		if(
			bot->energy > BUD_REQ // &&
			// (bot->energy - BUD_REQ) / (BOT_MAXENERGY - BUD_REQ) > realdis_(dre_)
		)
		{
			count = 0;
			do
			{
				choice = dirdis_(dre_);
				to = &tapeAt(x+OFFSET[choice][0], y+OFFSET[choice][1]);
				++count;
			}
			while( (to->plant || to->bot) && count < 16 );

			if(count == 16) // antifreeze
				continue;
			
			bot->energy -= BUD_PRICE;
			to->bot = new Bot{ BUD_PRICE, 0 };
			bots.push_front(to); 
			continue;
		}
		
		
		// move
		count = 0;
		do
		{
			choice = dirdis_(dre_);
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
			if( !( BOT_MAXENERGY - bot->energy < plant.energy ) )
			{
				bot->energy += plant.energy;
				delete to->plant;
				to->plant = nullptr; // remove from list 'plants' in 'update_plants'
			}
			else
			{
				plant.energy -= BOT_MAXENERGY - bot->energy;
				bot->energy = BOT_MAXENERGY;
			}
		}


		continue;
	}



	return;
}

void BotField::update_plants()
{
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
			(PLANT_MAXENERGY - plant->energy) * PLANT_TAKE_TO_SELF,
			cell->energy * PLANT_TAKE_FROM_EATH
		);
		cell->energy -= delta;
		plant->energy += delta;
	}

	return;
}


bool BotField::push(int x, int y, Bot *bot)
{
	auto *cell = &at(x, y);
	if(cell->bot)
		return false;
	cell->bot = bot;
	bots.push_back(cell);
	return true;
}

bool BotField::push(int x, int y, Plant *plant)
{
	auto *cell = &at(x, y);
	if(cell->plant)
		return false;
	cell->plant = plant;
	plants.push_back(cell);
	return true;
}





// end
