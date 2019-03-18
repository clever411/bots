#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/Field.hpp>





// constants
static constexpr int const OFFSET_SIZE = 8;
static constexpr int const OFFSET[OFFSET_SIZE][2] {
	{ -1, -1 }, { 0, -1 }, { 1, -1 },
	{ -1, 0 }, { 1, 0 },
	{ -1, 1 }, { 0, 1 }, { 1, 1 }
};







// types
struct Bot
{
	static constexpr int const
		CHARACTERS_COUNT = 5;
	static constexpr double const
		MAX_ENERGY = 1500.0,
		STEP_PRICE = 0.2,
		AGE_TAX = 0.005,
		BUD_REQ = 1000.0,
		BUD_PRICE = 500.0,
		MAX_MUTATION = 0.2,
		MUTATION_POWER = 0.005;

	double energy;
	int age;

	float
		steppricek, agetaxk,
		maxenergyk,
		budreqk, budpricek;

	inline double stepprice() const
	{
		return STEP_PRICE * (2.0 - steppricek);
	}
	inline double agetax() const
	{
		return AGE_TAX * (2.0 - agetaxk);
	}
	inline double maxenergy() const
	{
		return MAX_ENERGY * maxenergyk;
	}
	inline double budreq() const
	{
		return BUD_REQ * (2.0 - budreqk);
	}
	inline double budprice() const
	{
		return BUD_PRICE * (2.0 - budpricek);
	}

	Bot *bud();



	static Bot const DEFAULT;
};

struct Plant
{
	static constexpr double const
		TAKE_FROM_EATH = 0.25,
		TAKE_TO_SELF = 0.2,
		MAX_ENERGY = 400.0,
		BURN_CHANCE = 0.001;

	double energy;

	static Plant const DEFAULT;
};

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 75.0,
		SMOOTH = 0.33;

	double energy;
	Bot *bot;
	Plant *plant;

	static Cell const DEFAULT;
};





// core
struct BotField: public clever::Field<Cell>
{
	// members
	std::list<Cell*> bots = {};
	std::list<Cell*> plants = {};

	float
		summen = 0.0,
		grounden = 0.0,
		planten = 0.0,
		boten = 0.0;



	// destroy
	~BotField();



	// functions
	BotField &free();

	void init_botfield(int wedth, int height);
	void reset();

	void update_field();
	void update_ground();
	void update_bots();
	void update_plants();

	bool push(int x, int y, Bot *bot);
	bool push(int x, int y, Plant *plant);
	double fillground(int x, int y);



private:
	clever::Field<double> smoothf_ = {0, 0, nullptr};



};





#endif
