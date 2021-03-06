#include "init.hpp"

#include <cstring>
#include <iostream>
#include <memory>

#include <clever/SFML/HelpFunction.hpp>

#include <entities/Bot.hpp>
#include <field/BotField.hpp>
#include <field/Cell.hpp>
#include <utils/CellPrinter.hpp>

#include "declare.hpp"


using namespace clever;
using namespace sf;
using namespace std;







// objects
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "The Wonderful World";
unsigned int FRAMERATE_LIMIT = 60u;


Color const gridcolor(0xed, 0xd1, 0x9c);
Color const maincolor(0x5b, 0x3a, 0x29);

Font font;
unsigned int FONT_SIZE = 35u;
unsigned int EN_FONT_SIZE = 22u;
unsigned int EF_FONT_SIZE = 22u;

int const LABEL_LENGTH = 8;
int const EN_LABEL_LENGTH = 15;
int const EF_LABEL_LENGTH = 18;


int const DEFAULT_FIELD_WIDTH = 120 * 2 / 3;
int const DEFAULT_FIELD_HEIGHT = 240 * 2 / 3;







// init functions
void init_window()
{
	window.create(vmode, TITLE, Style::Fullscreen);
	window.setPosition({0u, 0u});
	window.setFramerateLimit(FRAMERATE_LIMIT);
	return;
}

void init_field()
{
	field.init_botfield(
		DEFAULT_FIELD_WIDTH,
		DEFAULT_FIELD_HEIGHT
	);
	return;
}


void init_layout()
{
	layout.size = makep<float>(window.getSize());
	layout.push( { 0.857143, 0.142857 } );

	// field & labels
	layout[0].type = Layout::Type::vertical;
	layout[0].push( { 0.875, 0.125 } );

	// field
	fieldlay = &layout[0][0];

	// labels
	labelslay = &layout[0][1];
	labelslay->push( { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } );
	auto loctype = makep(Layout::LocalType::second, Layout::LocalType::second);
	(*labelslay)[0].setloc( { 1, 2 }, loctype );
	(*labelslay)[1].setloc( { 1, 3 }, loctype );
	(*labelslay)[2].setloc( { 1, 2 }, loctype );
	(*labelslay)[3].setloc( { 1, 2 }, loctype );
	(*labelslay)[4].setloc( { 1, 2 }, loctype );
	(*labelslay)[5].setloc( { 1, 2 }, loctype );

	// mapping
	mappinglay = &layout[1];
	mappinglay->type = Layout::Type::vertical;
	mappinglay->setloc(1, 6);

	// all
	layout.adjust();



	return;
}

void init_printer()
{
	printer.groundgrad = { {
		Color(0x00, 0x00, 0x00, 0x00),
		Color(0x00, 0x00, 0x00, 0xff)
	} };

	printer.airgrad = { {
		Color(0x00, 0x00, 0x00, 0x00),
		Color(0xff, 0x00, 0x00, 0xff)
	} };

	printer.plantgrad = Gradient::gen('g', 'r');
	printer.plantgrad.colors[0].a = 0x66;
	printer.plantgrad.colors[1].a = 0xaa;

	printer.botgrad = Gradient{ { sf::Color(0xff, 0x80, 0x80), sf::Color(0xa0, 0x00, 0x00) } };
	printer.botgrad.colors[0].a = 0xcc;
	printer.botgrad.colors[1].a = 0xff;

	printer.bodygrad = Gradient::gen('b', 'r');
	printer.bodygrad.colors[0].a = 0xbb;
	printer.bodygrad.colors[1].a = 0xff;

	printer.mineralgrad = Gradient::DARKLING_BLUE;
	printer.mineralgrad.colors[0].a = 0x33;
	printer.mineralgrad.colors[1].a = 0x77;



	return;
}

void init_mapprinter()
{
	mapprinter.groundgrad = printer.groundgrad;
	mapprinter.airgrad = printer.airgrad;
	mapprinter.plantgrad = printer.plantgrad;
	mapprinter.botgrad = printer.botgrad;
	mapprinter.bodygrad = printer.bodygrad;
	mapprinter.mineralgrad = printer.mineralgrad;

	return;
}


void init_adapter()
{
	adapter.setField( shared_ptr<field_type>(
		&field,
		[](field_type *) { return; }
	) ).
	setPrinter( shared_ptr<printer_type>(
		&printer,
		[](printer_type *) { return; }
	) ).
	setSize( fieldlay->bounds() ).
	setDrawGridEnable(false);

	return;
}

void init_mapadapter()
{
	mapadapter.setField( shared_ptr<mapfield_type>(
		&field.mapping,
		[](mapfield_type *) { return; }
	) ).
	setPrinter( shared_ptr<mapprinter_type>(
		&mapprinter,
		[](mapprinter_type *) { return; }
	) ).
	setSize( mappinglay->bounds(0) ).
	setDrawGridEnable(false).
	setOrigin( mappinglay->bounds(0) / 2.0f );


	return;
}


void init_font()
{
	font.loadFromFile("res/Anonymous_Pro.ttf");
	return;
}

void init_labels()
{
	labels[2].getval = []()->string {
		return string("E summ:   ") + (
			field.summen >= 100000.0 ?
			to_string( (int) round( field.summen/1000 ) ) + "k" :
			to_string( (int) round( field.summen ) )
		);
	};
	labels[3].getval = []()->string {
		return string("E ground: ") + (
			field.grounden >= 100000.0 ?
			to_string( (int) round( field.grounden/1000 ) ) + "k" :
			to_string( (int) round( field.grounden ) )
		);
	};
	labels[4].getval = []()->string {
		return string("E air:    ") + (
			field.airen >= 100000.0 ?
			to_string( (int) round( field.airen/1000 ) ) + "k" :
			to_string( (int) round( field.airen ) )
		);
	};
	labels[5].getval = []()->string {
		return string("E plants: ") + (
			field.planten >= 100000.0 ?
			to_string( (int) round( field.planten/1000 ) ) + "k" :
			to_string( (int) round( field.planten ) )
		);
	};
	labels[6].getval = []()->string {
		return string("E bots:   ") + (
			field.boten >= 100000.0 ?
			to_string( (int) round( field.boten/1000 ) ) + "k" :
			to_string( (int) round( field.boten ) )
		);
	};
	labels[7].getval = []()->string {
		return string("E bodyes:  ") + (
			field.bodyen >= 100000.0 ?
			to_string( (int) round( field.bodyen/1000 ) ) + "k" :
			to_string( (int) round( field.bodyen ) )
		);
	};
	labels[8].getval = []()->string {
		return string("E mineral: ") + (
			field.mineralen >= 100000.0 ?
			to_string( (int) round( field.mineralen/1000 ) ) + "k" :
			to_string( (int) round( field.mineralen ) )
		);
	};

	labels[9].getval = []()->string {
		return string("EF air:    ") + to_string( (int) round( Bot::energy_from_air ) / 1000 ) + "k";
	};
	labels[10].getval = []()->string {
		return string("EF plants: ") + to_string( (int) round( Bot::energy_from_plants ) / 1000 ) + "k";
	};
	labels[11].getval = []()->string {
		return string("EF bodyes:  ") + to_string( (int) round( Bot::energy_from_body ) / 1000 ) + "k";
	};
	labels[12].getval = []()->string {
		return string("EF mineral: ") + to_string( (int) round( Bot::energy_from_minerals ) / 1000 ) + "k";
	};

	for(int i = 0; i < LABELS_COUNT; ++i)
	{
		labels[i].setFont( font );
		labels[i].setFillColor( maincolor );
		labels[i].setCharacterSize(
			i < 2 ? FONT_SIZE : ( i < LABELS_COUNT-4 ? EN_FONT_SIZE : EF_FONT_SIZE )
		);

		labels[i].setString( fills( "fg",
			i < 2 ? LABEL_LENGTH : ( i < LABELS_COUNT-4 ? EN_LABEL_LENGTH : EF_LABEL_LENGTH )
		) );
		labels[i].setOrigin(
			labels[i].getLocalBounds().width / 2.0f,
			labels[i].getLocalBounds().height
		);

		labels[i].setPosition(
			(*labelslay)(i).to<Vector2f>()
		);
	}


	return;
}



void init()
{
	init_window();
	init_field();
	init_layout();
	init_printer();
	init_mapprinter();
	init_adapter();
	init_mapadapter();
	init_font();
	init_labels();

	return;
}

void free()
{
	field.free();
	layout.free();
	return;
}





// end
