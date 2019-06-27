#ifndef CELL_HPP
#define CELL_HPP





struct Plant;
struct Bot;
struct Body;
struct Mineral;

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 50.0,
		SMOOTH_FACTOR = 0.75,
		TOAIR_FACTOR = 0.001,

		DEFAULT_AIR_ENERGY = 25.0f,
		AIRSMOOTH_FACTOR = 0.8;



	double energy = 0.0, airenergy = 0.0;
	double temp = 1.0, airtemp = 1.0;
	double tempenv = 6.0, airtempenv = 6.0;

	Plant *plant = nullptr;
	Bot *bot = nullptr;
	Body *body = nullptr;
	Mineral *mineral = nullptr;

};





#endif
