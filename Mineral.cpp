#include "Mineral.hpp"

#include <algorithm>

#include "Cell.hpp"
#include "Plant.hpp"


using namespace std;





void Mineral::update(Cell &cell)
{
	if( !(hidenergy > UNHIDDEN_SPEED) )
		energy += hidenergy,
		hidenergy = 0.0;
	else
		hidenergy -= UNHIDDEN_SPEED,
		energy += UNHIDDEN_SPEED;

	double const
		toairdelta = max(
			MIN_DISSOLUTION,
			energy * DISSOLUTION_FACTOR
		);

	if( !(energy - toairdelta > 0) )
		cell.airenergy += energy,
		energy = 0.0;
	else
		energy -= toairdelta,
		cell.airenergy += toairdelta;

	return;
}





// end
