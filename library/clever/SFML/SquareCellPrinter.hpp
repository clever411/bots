#ifndef SQUARE_CELL_PRINTER
#define SQUARE_CELL_PRINTER

#include <SFML/Graphics.hpp>





template<typename T>
class SquareCellPrinter: public sf::RectangleShape
{
public:
	typedef T value_type;

	SquareCellPrinter()
	{
		setFillColor(sf::Color::Transparent);
		setSideSize(50.0f);
		return;
	}

	SquareCellPrinter(value_type const &val): SquareCellPrinter()
	{
		set(val);
	}


	SquareCellPrinter &setSideSize(float side)
	{
		setSize( { side, side } );
		setOrigin( side/2.0f, side/2.0f );
		return *this;
	}

	SquareCellPrinter &set(value_type const &val)
	{
		switch(val)
		{
		case 0:
			setFillColor(sf::Color(0x00, 0x00, 0x00, 0x44));
			break;
		case 1:
			setFillColor(sf::Color(0xff, 0x00, 0x00, 0x7f));
			break;
		default:
			setFillColor(sf::Color::Transparent);
			break;
		}
		return *this;
	}


	
};





#endif
