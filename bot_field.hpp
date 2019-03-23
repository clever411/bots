#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/Field.hpp>





// types
struct Plant
{
	static constexpr double const
		TAKE_FROM_EATH = 0.1,
		TAKE_TO_SELF = 0.05,
		MAX_ENERGY = 100.0,
		BURN_CHANCE = 0.01;

	double energy;

	static Plant const DEFAULT;
};

struct Bot
{
	static constexpr int const
		CHARACTERS_COUNT = 5;
	static constexpr double const
		MAX_ENERGY = 500.0,
		STEP_PRICE = 0.0,
		AGE_STEP_TAX = 0.001,
		AGE_DIE_TAX = 0.5,
		BUD_REQ = 300.0,
		BUD_PRICE = 100.0,
		MAX_MUTATION = 0.25,
		MUTATION_POWER = 0.02;

	double energy;
	int age;
	int generation;

	float
		steppricek, agesteptaxk,
		maxenergyk,
		budreqk, budpricek;

	inline double stepprice() const
	{
		return STEP_PRICE * (2.0 - steppricek);
	}
	inline double agesteptax() const
	{
		return AGE_STEP_TAX * (2.0 - agesteptaxk);
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
	inline double dieedge() const
	{
		return AGE_DIE_TAX * age;
	}

	Bot *bud();



	static Bot const DEFAULT;
};

struct Body
{
	static constexpr double const
		ROT_SPEED = 0.5,
		ROT_ACCELERATION = 1.04;

	double energy;
	int age;

	static Body const DEFAULT;
};

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 50.0,
		SMOOTH = 0.33;

	double energy;
	Plant *plant;
	Bot *bot;
	Body *body;

	static Cell const DEFAULT;
};





// core
struct BotField: public clever::Field<Cell>
{
	// members
	std::list<Cell*> bots = {};

	double
		summen = 0.0,
		grounden = 0.0,
		planten = 0.0,
		boten = 0.0,
		bodyen = 0.0;



	// destroy
	~BotField();



	// functions
	BotField &free();

	void init_botfield(int wedth, int height);
	void reset();

	void update_field();
	void update_ground();
	void update_standing();
	void update_bots();

	bool push(int x, int y, Bot *bot);
	bool push(int x, int y, Plant *plant);
	double fillground(int x, int y);

	void random_fill(int cellcount);



private:
	clever::Field<double> smoothf_ = {0, 0, nullptr};



};





#endif
