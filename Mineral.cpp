#include "Mineral.hpp"

#include <algorithm>

#include "Cell.hpp"


using namespace std;





void Mineral::update(Cell &cell)
{
	double delta = min(
		MIN_DISSOLUTION,
		energy * DISSOLUTION_FACTOR
	);

	if( !(energy > delta) )
	{
		cell.airenergy += delta;
		cell.mineral = nullptr;
		delete this;
		return;
	}

	energy -= delta;
	cell.airenergy += delta;

	return;
}





// end
