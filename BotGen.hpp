#ifndef BOG_GENS
#define BOG_GENS

#include <random>
#include <string>

extern std::default_random_engine dre;





struct Gen
{
	// core
	Gen &mutate();



	// take	
	inline double air() const
	{
		return air_*AIR_TAKE_FACTOR;
	}
	
	inline double plant() const
	{
		return plant_*PLANT_TAKE;
	}

	inline double body() const
	{
		return body_*BODY_TAKE;
	}

	inline double mineral() const
	{
		return mineral_*MINERAL_TAKE;
	}

	
	
	// other
	template<class Ostream>
	Ostream &print( Ostream &os, std::string const &tab ) const
	{
		os << tab << "air: " << air_ << '\n' <<
		      tab << "plant: " << plant_ << '\n' <<
		      tab << "body: " << body_ << '\n' <<
		      tab << "mineral: " << mineral_ << '\n';
		return os;
	}

	

private:

	static constexpr double const
		AIR_TAKE_FACTOR = 0.25,
		PLANT_TAKE = 50.0,
		MINERAL_TAKE = 25.0,
		BODY_TAKE = 100.0,
		MUTATE_POWER = 0.1;

	static constexpr int const
		CHARS_COUNT = 4;
	

	double
		air_ = 1.0,
		plant_ = 1.0,
		body_ = 1.0,
		mineral_ = 1.0;



};





#endif
