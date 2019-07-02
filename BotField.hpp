#ifndef BOT_FIELD_HPP
#define BOT_FIELD_HPP

#include <list>
#include <random>

#include <clever/FieldParallelWork.hpp>
#include <clever/HexagonField.hpp>





struct Cell;
struct Plant;
struct Bot;



struct MapUnit
{
	double
		grounden = 0.0,
		airen = 0.0,
		planten = 0.0,
		boten = 0.0,
		bodyen = 0.0, 
		mineralen = 0.0;
	int density = 0;
};



struct BotField: public clever::HexagonField<Cell>
{
	static constexpr int const MAPPING_KOFF = 6;

	// members
	int age = 0;

	double
		summen = 0.0,
		grounden = 0.0,
		airen = 0.0,
		planten = 0.0,
		boten = 0.0,
		bodyen = 0.0, 
		mineralen = 0.0;

	HexagonField<MapUnit> mapping;



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
	void push(int x, int y);

	void random_fill(int cellcount);
	void ravage_ground(double k);
	void random_bots(int count);
	
	void calculate_energy();



private:
	inline bool valid(clever::PointI const &p);
	inline bool valid(clever::PointI const &p, int dir);

	void update_environment_();
	void update_ground_(int x, int y);

	void update_entities_();
	void update_entity_(int x, int y);

	void set_cells_();
	

	struct SmoothUnit
	{
		double ground, air;
	};

	clever::HexagonField<SmoothUnit> smoothf_ = {0, 0, nullptr};
	clever::HexagonFieldParallelWork<8> worker_;



};





#endif
