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
Color const backgroundcolor(0xfd, 0xea, 0xa8);

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





// end
