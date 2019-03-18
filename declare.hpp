#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/Field.hpp>
#include <clever/SFML/CellPrinter.hpp>
#include <clever/SFML/FieldAdapter.hpp>

#include "bot_field.hpp"











// types
typedef clever::CellPrinter<Cell> printer_type;
typedef BotField field_type;
typedef clever::FieldAdapter<Cell, printer_type> adapter_type;
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
	groundenlabel,
	botenlabel,
	plantenlabel,
	summenlabel;

extern adapter_type adapter;



	// Field & Widgets
extern field_type field;
extern int const DEFAULT_FIELD_WIDTH;
extern int const DEFAULT_FIELD_HEIGHT;

extern statstring_type
	agestring,
	speedstring,
	groundenstring,
	botenstring,
	plantenstring,
	summenstring;





#endif