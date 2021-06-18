#include "Body.hpp"

#include <cmath>

#include <field/Cell.hpp>

#include "Mineral.hpp"





void Body::update(Cell &cell)
{
	double delta = ROT_SPEED * pow(
		ROT_ACCELERATION, sqrt(double(age))
	);
	++age;

	if( !(energy > delta) ) // || !(energy - delta > TOMINERAL_EDGE) )
	{
		cell.mineral.hidenergy += energy;
		cell.body = nullptr;
		delete this;
		return;
	}

	energy -= delta;
	cell.mineral.hidenergy += delta;

	return;
}





// end
