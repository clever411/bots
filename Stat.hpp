#ifndef STAT_HPP
#define STAT_HPP

#include <cstdio>
#include <vector>





class Stat
{
public:
	struct Unit
	{
		float
			summ,
			ground,
			air,
			plant,
			bot,
			body,
			mineral;
	};



	Stat();

	void add(Unit const &unit);
	void write(char const *filename) const;
	void reset();



private:

	std::vector<Unit> code_;



};





#endif
