#include "declare.hpp"

using namespace clever;
using namespace sf;





template<>
clever::CellPrinter<Cell> &
clever::CellPrinter<Cell>::set( Cell const &cell )
{
	constexpr static int const
		WHITE = 0xaa;
	constexpr static auto const
		fun = [](int i) { return i > WHITE ? WHITE : i; };

	double k;
	if(cell.bot)
	{
		k = cell.bot->energy / BotField::BOT_MAXENERGY;
		setFillColor( sf::Color(
			0xff - int(k > 0.5 ? 0xff*(k-0.5) : 0),
			WHITE - fun( int(0xff * 2*k) ),
			WHITE - fun( int(0xff * 2*k) ),
			0xaa
		) );
	}
	else if(cell.plant)
	{
		k = cell.plant->energy / BotField::PLANT_MAXENERGY;
		setFillColor( sf::Color(
			WHITE - fun( int(0xff * 2*k) ),
			0xff - int(k > 0.5 ? 0xff*(k-0.5) : 0),
			WHITE - fun( int(0xff * 2*k) ),
			0xaa
		) );
	}
	else
	{
		k = cell.energy / BotField::DEFAULT_GROUND_ENERGY;
		setFillColor( sf::Color(
			0, 0, 0, int(255*k)
		) );
	}
	return *this;
}





// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 60u;

Color const backgroundcolor(0xfd, 0xea, 0xa8);
Color const gridcolor(0xed, 0xd1, 0x9c);
Color const maincolor(0x5b, 0x3a, 0x29);

Font font;
unsigned int FONT_SIZE = 50u;
unsigned int EN_FONT_SIZE = 30u;
Text
	agelabel,
	speedlabel,
	groundenlabel,
	botenlabel,
	plantenlabel,
	summenlabel;

adapter_type adapter;



// field
field_type field;
int const DEFAULT_FIELD_WIDTH = 100;
int const DEFAULT_FIELD_HEIGHT = 50;

statstring_type
	agestring("age: 0"),
	speedstring("speed: 0.0"),
	groundenstring("ground energy: 0.0"),
	botenstring   ("bots energy:   0.0"),
	plantenstring ("plants energy: 0.0"),
	summenstring  ("summ energy:   0.0");





// end
