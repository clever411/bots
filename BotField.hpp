#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/HexagonField.hpp>

#include "Cell.hpp"
#include "Plant.hpp"
#include "Bot.hpp"
#include "Body.hpp"





struct BotField: public clever::HexagonField<Cell>
{
	// members
	int age = 0;

	double
		summen = 0.0,
		grounden = 0.0,
		planten = 0.0,
		boten = 0.0,
		bodyen = 0.0;



	// create, destroy
	BotField();
	~BotField();



	// functions
	BotField &free();

	void init_botfield(int wedth, int height);
	void reset();
	void update();

	bool push(int x, int y, Bot *bot);
	bool push(int x, int y, Plant *plant);
	double push(int x, int y);

	void random_fill(int cellcount);
	void ravage_ground(double k);



private:
	void update_ground();
	void update_standing();

	void set_cells_();
	
	clever::HexagonField<double> smoothf_ = {0, 0, nullptr};



};





#endif
