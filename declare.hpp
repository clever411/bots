#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/HexagonField.hpp>
#include <clever/Layout.hpp>
#include <clever/SFML/FieldAdapter.hpp>





// types
struct CellPrinter;
struct MapUnitPrinter;
struct BotField;
struct MapUnit;


typedef CellPrinter printer_type;
typedef MapUnitPrinter mapprinter_type;

typedef BotField field_type;
typedef clever::HexagonField<MapUnit> mapfield_type;

typedef clever::HexagonFieldAdapter<field_type, printer_type> adapter_type;
typedef clever::HexagonFieldAdapter<mapfield_type, mapprinter_type> mapadapter_type;

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
extern unsigned int EF_FONT_SIZE;
extern sf::Text
	agelabel,
	speedlabel,
	summenlabel,
	groundenlabel,
	airenlabel,
	plantenlabel,
	botenlabel,
	bodyenlabel,
	mineralenlabel,

	efairlabel,
	efplantslabel,
	efbodylabel,
	efmineralslabel;

extern sf::Text *labels[];


extern clever::Layout layout,
       *fieldlay, *mappinglay, *labelslay;
extern printer_type printer;
extern mapprinter_type mapprinter;
extern adapter_type adapter;
extern mapadapter_type mapadapter;



	// Field & Widgets
extern field_type field;
extern int const DEFAULT_FIELD_WIDTH;
extern int const DEFAULT_FIELD_HEIGHT;

extern statstring_type
	agestring,
	speedstring,

	summenstring,
	groundenstring,
	airenstring,
	plantenstring,
	botenstring,
	bodyenstring,
	mineralenstring,

	efairstring,
	efplantsstring,
	efbodystring,
	efmineralsstring;

extern statstring_type *strings[];
extern int const LABSTR_COUNT;





#endif
