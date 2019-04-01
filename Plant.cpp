#include "Plant.hpp"

#include <algorithm>

#include "Cell.hpp"

using namespace std;





void Plant::update(Cell &cell)
{
	double delta = min(
		(MAX_ENERGY - energy) * TAKE_TO_SELF,
		cell.energy * TAKE_FROM_EATH
	);

	cell.energy -= delta;
	energy += delta;

	return;
}





// end
