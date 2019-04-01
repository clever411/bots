#include "Body.hpp"

#include <cmath>

#include "Cell.hpp"





void Body::update(Cell &cell)
{
	double delta = ROT_SPEED * pow(
		ROT_ACCELERATION, sqrt(double(age))
	);
	++age;

	if( !(energy > delta) )
	{
		cell.energy += energy;
		cell.body = nullptr;
		delete this;
		return;
	}

	energy -= delta;
	cell.energy += delta;

	return;
}





// end
