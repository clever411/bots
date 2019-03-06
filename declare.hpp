#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/Field.hpp>
#include <clever/SFML/FieldAdapter.hpp>

#include "CellPrinter.hpp"





// types
typedef int value_type;
typedef CellPrinter printer_type;
typedef clever::Field<value_type> field_type;
typedef clever::FieldAdapter<value_type, printer_type> adapter_type;
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
extern sf::Text agelabel;
extern sf::Text speedlabel;

extern adapter_type adapter;



	// Field & Widgets
extern field_type field;
extern int const DEFAULT_FIELD_WIDTH;
extern int const DEFAULT_FIELD_HEIGHT;

extern statstring_type agestring;
extern statstring_type speedstring;





#endif
