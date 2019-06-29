#ifndef BOT_HPP
#define BOT_HPP

#include <random>

#include <clever/Point.hpp>

#include "BotGen.hpp"





// objects
extern std::default_random_engine dre;





// main
struct BotField;
struct Gen;

struct Bot
{
	typedef BotField field_type;
	typedef uint32_t neuron_type;



	// body
	static constexpr double const
		MAX_ENERGY = 1000.0,
		DEATH_EDGE = 50.0,
		STEP_PRICE = 0.25,
		AGE_STEP_TAX = 0.01,
		AGE_DEATH_TAX = 0.5,
		BUD_REQ = 400.0,
		BUD_PRICE = 150.0,
		MOVE_PRICE_FACTOR = 4.0;


	// brain
	static constexpr int const
		BRAIN_SIZE = 64,
		REPEAT_COMMAND_COUNT = 16;


	static constexpr neuron_type const
		ACTION_OFFSET = 0,
		ACTION_MASK = 0x0f,

		ARG_OFFSET = 4,
		ARG_MASK = 0x0fff,

		JUMPF_OFFSET = 16, JUMPS_OFFSET = 24,
		JUMP_MASK = 0xff,

		NUL = 0x00,
		MOVE = 0x01,
		EAT = 0x02,
		TURN = 0x03,
		CHECK = 0x04;




	// data-members
	double energy = BUD_PRICE;
	int x = 0, y = 0, dir = 0;
	int worldage = 0, age = 0, generation = 0;
	Gen gen;

	neuron_type brain[BRAIN_SIZE] = {
		// CHECK,
		// MOVE, JUMP_BACKWARD | (0x02 << 3), NUL, NUL,
		// EAT, MOVE, JUMP_BACKWARD | (0x07 << 3), NUL,
		// TURN | (0x02 << 3), JUMP_BACKWARD | (0x0a << 3), NUL, NUL,
		// NUL //, ...
	};
	int p = 0; // position in brain





	// methods
	Bot();
	void update(field_type &f);
	void random_fill_brain();

	inline double stepprice() const
	{
		return STEP_PRICE;
	}
	inline double agesteptax() const
	{
		return AGE_STEP_TAX;
	}
	inline double maxenergy() const
	{
		return MAX_ENERGY;
	}
	inline double budreq() const
	{
		return BUD_REQ;
	}
	inline double budprice() const
	{
		return BUD_PRICE;
	}
	inline double deathedge() const
	{
		return DEATH_EDGE + age * AGE_DEATH_TAX;
	}



	static inline neuron_type getaction( neuron_type neuron )
	{
		return (neuron >> ACTION_OFFSET) & ACTION_MASK;
	}
	static inline neuron_type getarg( neuron_type neuron )
	{
		return (neuron >> ARG_OFFSET) & ARG_MASK;
	}
	static inline neuron_type getjumpf( neuron_type neuron )
	{
		return (neuron >> JUMPF_OFFSET) & JUMP_MASK;
	}
	static inline neuron_type getjumps( neuron_type neuron )
	{
		return (neuron >> JUMPS_OFFSET) & JUMP_MASK;
	}


	
private:

	Bot *bud();

	void move(field_type &f, bool &isdie);
	bool eat(field_type &f, neuron_type arg);
	void turn(neuron_type arg);
	bool check( field_type const &f, neuron_type arg );
	void spend_energy( field_type &f, double delta, bool &isdie );


	neuron_type random_neuron();


	inline clever::PointI getto() const;
	inline bool valid(
		clever::PointI const &to,
		field_type const &f
	) const;
	



};





#endif
