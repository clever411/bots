#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/Field.hpp>





// types
struct Bot
{
	double energy;
	int age;

	static Bot const DEFAULT;
};

struct Plant
{
	double energy;

	static Plant const DEFAULT;
};

struct Cell
{
	double energy;
	Bot *bot;
	Plant *plant;

	static Cell const DEFAULT;
};





// core
struct BotField: public clever::Field<Cell>
{
	// constants
	static constexpr int const OFFSET_SIZE = 8;
	static constexpr int const OFFSET[OFFSET_SIZE][2] {
		{ -1, -1 }, { 0, -1 }, { 1, -1 },
		{ -1, 0 }, { 1, 0 },
		{ -1, 1 }, { 0, 1 }, { 1, 1 }
	};

	static constexpr double const
		DEFAULT_GROUND_ENERGY = 75.0,
		SMOOTH = 0.5,
		PLANT_TAKE_FROM_EATH = 0.25,
		PLANT_TAKE_TO_SELF = 0.2,
		PLANT_MAXENERGY = 400.0,
		PLANT_BURN_CHANCE = 0.001,
		BOT_MAXENERGY = 1500.0,
		BUD_REQ = 750.0,
		BUD_PRICE = 500.0,
		STEP_PRICE = 0.2,
		AGE_TAX = 0.005;
	
	
	
	// members
	std::list<Cell*> bots = {};
	std::list<Cell*> plants = {};



	// destroy
	~BotField();



	// functions
	void init_botfield(int wedth, int height);
	void reset();

	void update_field();
	void update_ground();
	void update_bots();
	void update_plants();
	
	bool push(int x, int y, Bot *bot);
	bool push(int x, int y, Plant *plant);

	void get_energy(
		double &summen, double &grounden,
		double &planten, double &boten
	) const;



private:
	static std::default_random_engine dre_;
	static std::uniform_real_distribution<double> realdis_;
	static std::uniform_int_distribution<int> dirdis_;

	clever::Field<double> smoothf_ = {0, 0, nullptr};



};





#endif
