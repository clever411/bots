#ifndef CELL_PRINTER_HPP
#define CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>

#include <clever/SFML/Gradient.hpp>





struct Cell;
struct MapUnit;

class CellPrinter: public sf::CircleShape
{
public:
	// types
	enum Mode
	{
		groundmode, airmode
	};



	CellPrinter();

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





class MapUnitPrinter: public sf::CircleShape
{
public:
	// types
	enum Mode
	{
		groundmode, airmode, plantmode,
		botmode, bodymode, mineralmode
	};



	MapUnitPrinter();

	MapUnitPrinter &setSideSize(float a);
	MapUnitPrinter &set(MapUnit const &unit);

	MapUnitPrinter &setMode(Mode newmode);



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
