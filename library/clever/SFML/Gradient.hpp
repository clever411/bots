#ifndef CLEVER_GRADIENT_HPP
#define CLEVER_GRADIENT_HPP

#include <vector>

#include <SFML/Graphics.hpp>





namespace clever
{




	
struct Gradient
{
	std::vector<sf::Color> colors;

	sf::Color operator()(float k) const;
	
	static Gradient const
		BRIGHTENING_RED,
		BRIGHTENING_GREEN,
		BRIGHTENING_BLUE,
		BRIGHTENING_YELLOW,
		BRIGHTENING_MAGENTA,
		BRIGHTENING_CYAN,
		BRIGHTENING_RRG;

	static Gradient gen(int f, int s);
};





}





#endif
