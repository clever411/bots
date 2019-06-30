#ifndef MINERAL_HPP
#define MINERAL_HPP





struct Cell;

struct Mineral
{
	static constexpr double const
		UNHIDDEN_SPEED = 0.1,
		MIN_DISSOLUTION = 0.001,
		DISSOLUTION_FACTOR = 0.0001;

	double hidenergy = 0.0, energy = 0.0;

	void update(Cell &cell);

};





#endif
