#ifndef MINERAL_HPP
#define MINERAL_HPP





struct Cell;

struct Mineral
{
	static constexpr double const
		MIN_DISSOLUTION = 0.1,
		DISSOLUTION_FACTOR = 0.01;

	double energy;

	void update(Cell &cell);

};





#endif