#ifndef HEXAGON_CELL_PRINTER_HPP
#define HEXAGON_CELL_PRINTER_HPP





template<typename T>
class HexagonCellPrinter: public sf::CircleShape
{
public:
	typedef T value_type;

	HexagonCellPrinter()
	{
		setPointCount(6);
		setRotation(90);
		setFillColor(sf::Color::Transparent);
		setSideSize(50.0f);
		return;
	}

	HexagonCellPrinter(value_type const &val): HexagonCellPrinter()
	{
		set(val);
	}


	HexagonCellPrinter &setSideSize(float side)
	{
		setRadius(side);
		setOrigin( side, side );
		return *this;
	}

	HexagonCellPrinter &set(value_type const &val)
	{
		switch(val)
		{
		case 0:
			setFillColor(sf::Color::White);
			break;
		case 1:
			setFillColor(sf::Color::Black);
			break;
		default:
			setFillColor(sf::Color::Transparent);
		}
		return *this;
	}


	
};





#endif
