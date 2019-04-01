#ifndef PLANT_HPP
#define PLANT_HPP






struct Plant
{
	static constexpr double const
		TAKE_FROM_EATH = 0.1,
		TAKE_TO_SELF = 0.05,
		MAX_ENERGY = 100.0,
		BURN_CHANCE = 0.01;

	double energy = 0.0;
};






#endif
