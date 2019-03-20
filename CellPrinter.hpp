#ifndef CELL_PRINTER_HPP
#define CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>

#include "bot_field.hpp"





class CellPrinter: public sf::RectangleShape
{
public:
	enum Type
	{
		plant, bot, body, empty, none
	};

	CellPrinter(Cell const &cell = Cell::DEFAULT);


	CellPrinter &set(Cell const &cell);



private:
	Type last_ = none;



};





#endif
