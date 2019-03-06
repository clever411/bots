#ifndef CELL_PRINTER_HPP
#define CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>





struct CellPrinter: public sf::RectangleShape
{
	CellPrinter(int value = 0);
	~CellPrinter();

	CellPrinter &set(int value);
};





#endif
