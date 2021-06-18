#include "Plant.hpp"

#include <algorithm>
#include <random>

#include <field/BotField.hpp>
#include <field/Cell.hpp>


using namespace std;





void Plant::update(BotField &f)
{
	double delta = min(
		(MAX_ENERGY - energy) * TAKE_TO_SELF,
		f.at(x, y).energy * TAKE_FROM_EATH
	);

	f.at(x, y).energy -= delta;
	energy += delta;

	Cell *cell;
	for(int i = 0; i < f.OFFSET_COUNT; ++i)
	{
		if( !valid(f, i) )
			continue;

		cell = &f.neart(x, y, i);
		if( !cell->plant && (
				cell->energy /
				Cell::DEFAULT_GROUND_ENERGY
			) * BUD_CHANCE > (double)rand() / RAND_MAX
		)
		{
			cell->plant = new Plant;
			f.getxy( cell, cell->plant->x, cell->plant->y );
		}
	}

	return;
}

inline bool Plant::valid( BotField const &f, int dir )
{
	return y + f.OFFSET[dir][1] >= 0 && y + f.OFFSET[dir][1] < f.h;
}





// end
