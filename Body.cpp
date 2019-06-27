#include "Body.hpp"

#include <cmath>

#include "Cell.hpp"
#include "Mineral.hpp"





void Body::update(Cell &cell)
{
	double delta = ROT_SPEED * pow(
		ROT_ACCELERATION, sqrt(double(age))
	);
	++age;

	if(!cell.mineral)
		cell.mineral = new Mineral;

	if( !(energy > delta) ) // || !(energy - delta > TOMINERAL_EDGE) )
	{
		cell.mineral->energy += energy;
		cell.body = nullptr;
		delete this;
		return;
	}

	energy -= delta;
	cell.mineral->energy += delta;

	return;
}





// end
