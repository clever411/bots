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
		);

	if( !(energy - toairdelta > 0) )
	{
		cell.airenergy += toairdelta;
		cell.mineral = nullptr;
		delete this;
		return;
	}

	energy -= toairdelta;
	cell.airenergy += toairdelta;

	return;
}





// end
