#ifndef BODY_HPP
#define BODY_HPP





struct Cell;

struct Body
{
	static constexpr double const
		ROT_SPEED = 1.0,
		ROT_ACCELERATION = 1.12;

	double energy = 0.0;
	int age = 0;

	void update(Cell &cell);

};





#endif
