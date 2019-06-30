#include "declare.hpp"

#include "BotField.hpp"
#include "Cell.hpp"
#include "Plant.hpp"
#include "Bot.hpp"
#include "Body.hpp"
#include "Mineral.hpp"
#include "CellPrinter.hpp"


using namespace clever;
using namespace sf;





// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "The Wonderful World";
unsigned int FRAMERATE_LIMIT = 60u;

Color const backgroundcolor(0xfd, 0xea, 0xa8);
Color const gridcolor(0xed, 0xd1, 0x9c);
Color const maincolor(0x5b, 0x3a, 0x29);

Font font;
unsigned int FONT_SIZE = 40u;
unsigned int EN_FONT_SIZE = 22u;
unsigned int EF_FONT_SIZE = 22u;
Text
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

Text *labels[] = {
	&agelabel, &speedlabel,
	&summenlabel, &groundenlabel, &airenlabel,
	&plantenlabel, &botenlabel,
	&bodyenlabel, &mineralenlabel,
	&efairlabel, &efplantslabel,
	&efbodylabel, &efmineralslabel
};


Layout layout,
       *fieldlay, *mappinglay, *labelslay;
printer_type printer;
mapprinter_type mapprinter;
adapter_type adapter;
mapadapter_type mapadapter;



// field
field_type field;
int const DEFAULT_FIELD_WIDTH = 80;
int const DEFAULT_FIELD_HEIGHT = 160;

statstring_type
	agestring  ("age:   0  "),
	speedstring("speed: 0.0"),

	summenstring   ("E summ:    0  "),
	groundenstring ("E ground:  0  "),
	airenstring    ("E air:     0  "),
	plantenstring  ("E plants:  0  "),
	botenstring    ("E bots:    0  "),
	bodyenstring   ("E bodyes:  0  "),
	mineralenstring("E mineral: 0  "),

	efairstring     ("EF air:     0  "),
	efplantsstring  ("EF plants:  0  "),
	efbodystring    ("EF bodyes:  0  "),
	efmineralsstring("EF mineral: 0  ");


statstring_type *strings[] = {
	&agestring, &speedstring,
	&summenstring, &groundenstring, &airenstring,
	&plantenstring, &botenstring,
	&bodyenstring, &mineralenstring,
	&efairstring, &efplantsstring,
	&efbodystring, &efmineralsstring
};
int const LABSTR_COUNT = sizeof(labels) / sizeof(decltype(*labels));




// end
