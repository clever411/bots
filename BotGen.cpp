#include "BotGen.hpp"





Gen &Gen::mutate()
{
	static std::uniform_int_distribution<int>
		mutdis(0, CHARS_COUNT-1);

	double *chars[] = {
		&air_, &plant_, &body_, &mineral_
	};

	int from;
	do
	{
		from = mutdis(dre);
	}
	while( *chars[from] - MUTATE_POWER < 0.0 );

	*chars[from] -= MUTATE_POWER;
	*chars[mutdis(dre)] += MUTATE_POWER;

	return *this;
}





// end
