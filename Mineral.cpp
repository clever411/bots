#include "Mineral.hpp"

#include <algorithm>

#include "Cell.hpp"
#include "Plant.hpp"


using namespace std;





void Mineral::update(Cell &cell)
{
	double const
		toairdelta = max(
			MIN_DISSOLUTION,
			energy * DISSOLUTION_FACTOR
		),
		fromplantdelta = cell.plant ?
			cell.plant->energy * FROM_PLANT_FACTOR :
			0.0;

	if( !(energy + fromplantdelta - toairdelta > 0) )
	{
		cell.airenergy += toairdelta;
		cell.mineral = nullptr;
		delete this;
		return;
	}

	if(cell.plant)
		cell.plant->energy -= fromplantdelta;

	energy += fromplantdelta - toairdelta;
	cell.airenergy += toairdelta;

	return;
}





// end
