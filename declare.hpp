#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/SFML/FieldAdapter.hpp>





// types
struct CellPrinter;
struct BotField;

typedef CellPrinter printer_type;
typedef BotField field_type;
typedef clever::HexagonFieldAdapter<field_type, printer_type> adapter_type;
typedef clever::ChangingObject<std::string> statstring_type;





// objects
	// SFML
extern sf::RenderWindow window;
extern sf::VideoMode vmode;
extern char const *TITLE;
extern unsigned int FRAMERATE_LIMIT;

extern sf::Color const backgroundcolor;
extern sf::Color const gridcolor;
extern sf::Color const maincolor;

extern sf::Font font;
extern unsigned int FONT_SIZE;
extern unsigned int EN_FONT_SIZE;
extern sf::Text
	agelabel,
	speedlabel,
	summenlabel,
	groundenlabel,
	plantenlabel,
	botenlabel,
	bodyenlabel;

extern adapter_type adapter;



	// Field & Widgets
extern field_type field;
extern int const DEFAULT_FIELD_WIDTH;
extern int const DEFAULT_FIELD_HEIGHT;

extern statstring_type
	agestring,
	speedstring,
	summenstring,
	groundenstring,
	plantenstring,
	botenstring,
	bodyenstring;





#endif
