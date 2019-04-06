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

	if( !(energy - delta > TOMINERAL_EDGE) )
	{
		if( !(energy > delta) )
		{
			cell.energy += energy;
			cell.body = nullptr;
			delete this;
			return;
		}

		energy -= delta;
		cell.energy += delta;

		cell.body = nullptr;
		if(cell.mineral)
			cell.mineral->energy += energy;
		else
			cell.mineral = new Mineral{ energy };

		delete this;
		return;
	}

	energy -= delta;
	cell.energy += delta;

	return;
}





// end
