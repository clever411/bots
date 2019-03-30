#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/HexagonField.hpp>





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
	// body
	static constexpr int const
		CHARACTERS_COUNT = 5;
	static constexpr double const
		MAX_ENERGY = 1000.0,
		STEP_PRICE = 1.0,
		AGE_STEP_TAX = 0.1,
		AGE_DEATH_TAX = 5.0,
		BUD_REQ = 400.0,
		BUD_PRICE = 200.0,
		MAX_MUTATION = 0.25,
		MUTATION_POWER = 0.02,
		TURN_CHANCE = 0.5;

	double energy;
	int dir;
	int age;
	int generation;

	float
		steppricek, agesteptaxk,
		maxenergyk,
		budreqk, budpricek;





	// brain
	static constexpr int const
		MAINFUN_SIZE = 32,
		FUN_SIZE = 16,
		FUN_COUNT = 6,
		BRAIN_SIZE = MAINFUN_SIZE + FUN_SIZE*FUN_COUNT,
		REPEAT_COMMAND_COUNT = 16,
		CHECK_OFFSET = 4;

	static constexpr uint8_t const
		MASK = 0x07,
		NUL = 0x00,
		MOVE = 0x01,
		EAT = 0x02,
		TURN = 0x03,
		CHECK = 0x04,
		CALL = 0x05,
		JUMP_FORWARD = 0x06,
		JUMP_BACKWARD = 0x07;

	uint8_t brain[BRAIN_SIZE];
	int p; // position in brain



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
	inline double deathedge() const
	{
		return AGE_DEATH_TAX * age;
	}

	Bot *bud();



	static Bot const DEFAULT;
};

struct Body
{
	static constexpr double const
		ROT_SPEED = 1.0,
		ROT_ACCELERATION = 1.1;

	double energy;
	int age;

	static Body const DEFAULT;
};

struct Cell
{
	static constexpr double const
		DEFAULT_GROUND_ENERGY = 50.0,
		SMOOTH = 0.5;

	double energy;
	double temp;
	Plant *plant;
	Bot *bot;
	Body *body;

	static Cell const DEFAULT;
};





// core
struct BotField: public clever::HexagonField<Cell>
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
	void ravage_ground(double k);



private:
	void set_cells_();

	clever::HexagonField<double> smoothf_ = {0, 0, nullptr};



};





#endif
