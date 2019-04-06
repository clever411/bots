#ifndef CELL_PRINTER_HPP
#define CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>

#include "Gradient.hpp"





class Cell;

class CellPrinter: public sf::CircleShape
{
public:
	// types
	enum Mode
	{
		groundmode, airmode
	};

	CellPrinter();
	CellPrinter(Cell const &cell);

	CellPrinter &setSideSize(float a);
	CellPrinter &set(Cell const &cell);

	CellPrinter &changeMode();

	Mode mode = groundmode;

	clever::Gradient
		groundgrad,
		airgrad,
		plantgrad,
		botgrad,
		bodygrad,
		mineralgrad;



};





#endif
