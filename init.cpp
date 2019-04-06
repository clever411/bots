#include "init.hpp"

#include <cstring>
#include <iostream>
#include <memory>

#include <clever/Layout.hpp>
#include <clever/SFML/HelpFunction.hpp>

#include "declare.hpp"
#include "BotField.hpp"
#include "Cell.hpp"
#include "CellPrinter.hpp"


using namespace clever;
using namespace sf;
using namespace std;





// init functions
void init()
{
	init_window();
	init_field();
	init_printer();
	init_adapter();
	init_font();
	init_labels();

	return;
}

void init_window()
{
	window.create(vmode, TITLE, Style::None);
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

void init_printer()
{
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

	printer.groundgrad = { {
		Color(0x00, 0x00, 0x00, 0x00),
		Color(0x00, 0x00, 0x00, 0xff)
	} };

	printer.airgrad = { {
		Color(0x00, 0x00, 0x00, 0x00),
		Color(0xff, 0x00, 0x00, 0xff)
	} };
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
	setSize(
		makep<float>(window.getSize())
	).
	setDrawGridEnable(false).
	setGridThickness(2.0f).
	setGridColor(sf::Color::White);


	return;
}

void init_font()
{
	font.loadFromFile( "Anonymous_Pro.ttf" );
	return;
}

void init_labels()
{
	Layout layout;
	layout.refp = { 0.0f, adapter.getSize().y };
	layout.size = { (float)window.getSize().x, window.getSize().y - adapter.getSize().y };
	layout.push({0.8f, 1.0f, 1.0f, 1.0f});
	auto loctype = makep(Layout::LocalType::second, Layout::LocalType::second);
	layout[0].setloc({1, 2}, loctype);
	layout[1].setloc({1, 3}, loctype);
	layout[2].setloc({1, 2}, loctype);
	layout[3].setloc({1, 2}, loctype);
	layout.adjust();


	
	Text *labels[] = {
		&agelabel, &speedlabel,
	 	&summenlabel, &groundenlabel, &airenlabel,
		&plantenlabel, &botenlabel,
		&bodyenlabel, &mineralenlabel
	};
	statstring_type *strings[] = {
		&agestring, &speedstring,
		&summenstring, &groundenstring, &airenstring,
		&plantenstring, &botenstring,
		&bodyenstring, &mineralenstring
	};
	static constexpr int const
		LABELS_COUNT = sizeof(labels) / sizeof(decltype(*labels));



	for(int i = 0; i < LABELS_COUNT; ++i)
	{
		labels[i]->setFont( font );
		labels[i]->setFillColor( maincolor );
		labels[i]->setCharacterSize( i < 2 ? FONT_SIZE : EN_FONT_SIZE );
		labels[i]->setString( strings[i]->get() );

		labels[i]->setOrigin(
			labels[i]->getLocalBounds().width / 2.0f,
			labels[i]->getLocalBounds().height
		);
		labels[i]->setPosition(
			layout(i).to<Vector2f>()
		);
	}



	layout.free();
	return;
}



void free()
{
	field.free();

}





// end
