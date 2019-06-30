#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/HexagonField.hpp>
#include <clever/Layout.hpp>
#include <clever/SFML/FieldAdapter.hpp>

#include "Label.hpp"





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
extern sf::Color const backgroundcolor;

extern int const LABELS_COUNT;
extern Label labels[];


extern clever::Layout layout,
       *fieldlay, *mappinglay, *labelslay;
extern printer_type printer;
extern mapprinter_type mapprinter;
extern adapter_type adapter;
extern mapadapter_type mapadapter;



	// Field & Widgets
extern field_type field;





#endif
