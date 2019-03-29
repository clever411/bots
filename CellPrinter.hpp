#ifndef CELL_PRINTER_HPP
#define CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>

#include "bot_field.hpp"
#include "Gradient.hpp"





class CellPrinter: public sf::CircleShape
{
public:
	CellPrinter();
	CellPrinter(Cell const &cell);

	CellPrinter &setSideSize(float a);
	CellPrinter &set(Cell const &cell);


	clever::Gradient
		plantgrad_,
		botgrad_,
		bodygrad_,
		emptygrad_;



};





#endif
