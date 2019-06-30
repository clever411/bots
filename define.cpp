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

int const LABEL_LENGTH = 10;
int const EN_LABEL_LENGTH = 15;
int const EF_LABEL_LENGTH = 18;

int const LABELS_COUNT = 13;
Label labels[LABELS_COUNT];



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





// end
