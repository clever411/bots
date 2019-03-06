#include "declare.hpp"

using namespace clever;
using namespace sf;





// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 144u;

Color const backgroundcolor(0xfd, 0xea, 0xa8);
Color const gridcolor(0xec, 0xc9, 0x97);
Color const maincolor(0x30, 0x21, 0x12);

Font font;
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
