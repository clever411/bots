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
		DARKLING_RED,
		DARKLING_GREEN,
		DARKLING_BLUE,
		DARKLING_YELLOW,
		DARKLING_MAGENTA,
		DARKLING_CYAN,
		DARKLING_RRG;

	static Gradient gen(int f, int s);
};





}





#endif
