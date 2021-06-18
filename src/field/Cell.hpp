#ifndef CELL_HPP
#define CELL_HPP

#include <entities/Mineral.hpp>





struct Plant;
struct Bot;
struct Body;

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 50.0,
		SMOOTH_FACTOR         = 0.75,
		TOAIR_FACTOR          = 0.001,

		DEFAULT_AIR_ENERGY    = 30.0f,
		AIRSMOOTH_FACTOR      = 0.8;


	double  energy  = 0.0, airenergy  = 0.0;
	Mineral mineral = Mineral();
	double  temp    = 1.0, airtemp    = 1.0;
	double  tempenv = 6.0, airtempenv = 6.0;

	Plant *plant = nullptr;
	Bot   *bot   = nullptr;
	Body  *body  = nullptr;
};





#endif
