#ifndef CELL_HPP
#define CELL_HPP





struct Plant;
struct Bot;
struct Body;

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 50.0,
		SMOOTH = 0.5;


	double energy = 0.0;
	double temp = 1.0;
	Plant *plant = nullptr;
	Bot *bot = nullptr;
	Body *body = nullptr;
};





#endif
