#ifndef PLANT_HPP
#define PLANT_HPP





struct BotField;

struct Plant
{
	static constexpr double const
		TAKE_FROM_EATH = 0.25,
		TAKE_TO_SELF = 0.05,
		MAX_ENERGY = 750.0,
		BURN_CHANCE = 0.000005,
		BUD_CHANCE = 0.005;

	int x = 0, y = 0;
	double energy = 0.0;

	void update(BotField &f);
	inline bool valid(BotField const &f, int dir);
};






#endif
