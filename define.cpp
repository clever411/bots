#include "declare.hpp"

using namespace clever;
using namespace sf;





template<>
clever::CellPrinter<Cell> &
clever::CellPrinter<Cell>::set( Cell const &cell )
{
	if(cell.plant)
		setFillColor( sf::Color(
			0, 255, 0, int(255*cell.plant->energy/BotField::PLANT_MAXENERGY)
		) );
	else if(cell.bot)
		setFillColor( sf::Color(
			255, 0, 0, int(255*cell.bot->energy/BotField::BOT_MAXENERGY)
		) );
	else
		setFillColor( sf::Color(
			0, 0, 0, int(255*cell.energy/100.0) 
		) );
	return *this;
}





// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 144u;

Color const backgroundcolor(0xfd, 0xea, 0xa8);
Color const gridcolor(0xed, 0xd1, 0x9c);
Color const maincolor(0x5b, 0x3a, 0x29);

Font font;
unsigned int FONT_SIZE = 50u;
Text agelabel;
Text speedlabel;

adapter_type adapter;



// field
field_type field;
int const DEFAULT_FIELD_WIDTH = 50;
int const DEFAULT_FIELD_HEIGHT = 25;

statstring_type agestring("age: 0  ");
statstring_type speedstring("speed: 0.0");





// end
