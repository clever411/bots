#ifndef BOT_HPP
#define BOT_HPP

#include <random>

#include <clever/Point.hpp>





// objects
extern std::default_random_engine dre;
extern std::uniform_real_distribution<double> realdis;





// main
struct BotField;

struct Bot
{
	typedef BotField field_type;
	typedef uint8_t neuron_type;



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

	// brain
	static constexpr int const
		MAINFUN_SIZE = 32,
		FUN_SIZE = 16,
		FUN_COUNT = 6,
		BRAIN_SIZE = MAINFUN_SIZE + FUN_SIZE*FUN_COUNT,
		REPEAT_COMMAND_COUNT = 16,
		CHECK_OFFSET = 4;

	static constexpr neuron_type const
		MASK = 0x07,
		NUL = 0x00,
		MOVE = 0x01,
		EAT = 0x02,
		TURN = 0x03,
		CHECK = 0x04,
		CALL = 0x05,
		JUMP_FORWARD = 0x06,
		JUMP_BACKWARD = 0x07;




	// data-members
	double energy = BUD_PRICE;
	int x = 0, y = 0, dir = 0;
	int worldage = 0, age = 0, generation = 0;

	float
		steppricek = 1.0f, agesteptaxk = 1.0f,
		maxenergyk = 1.0f,
		budreqk = 1.0f, budpricek = 1.0f;

	neuron_type brain[BRAIN_SIZE] = {
		CHECK,
		MOVE, JUMP_BACKWARD | (0x02 << 3), NUL, NUL,
		EAT, MOVE, JUMP_BACKWARD | (0x07 << 3), NUL,
		TURN | (0x02 << 3), JUMP_BACKWARD | (0x0a << 3), NUL, NUL,
		NUL //, ...
	};
	int p = 0; // position in brain





	// methods
	void update(field_type &f);

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




	
private:
	Bot *bud();

	void move(field_type &f);
	void eat(field_type &f);
	void turn(neuron_type arg);
	void check(field_type const &f);
	void call(neuron_type arg);
	void jumpf(neuron_type arg);
	void jumpb(neuron_type arg);

	inline void incp();
	inline clever::PointI getto() const;
	inline bool valid(
		clever::PointI const &to,
		field_type const &f
	) const;
	

};





#endif
