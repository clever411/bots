#ifndef STAT_HPP
#define STAT_HPP

#include <cstdio>
#include <vector>





class Stat
{
public:
	void add(
		float summen,
		float grounden,
		float planten,
		float boten
	);
	void write(char const *filename) const;
	void reset();



private:
	struct Unit
	{
		float
			summ,
			ground,
			plant,
			bot;
	};

	std::vector<Unit> code_;



};





#endif
