#include <cstring>
#include <memory>

#include "init.hpp"

#include "declare.hpp"


using namespace clever;
using namespace sf;
using namespace std;





// init functions
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

void init_adapter()
{
	// field
	shared_ptr<field_type> p(
		&field,
		[](field_type *) { return; }
	);

	// printer
	auto printer = make_shared<printer_type>();

	printer->plantgrad_ = Gradient::gen('g', 'r');
	printer->plantgrad_.colors[0].a = 0xaa;
	printer->plantgrad_.colors[1].a = 0xee;

	printer->botgrad_ = Gradient{ { sf::Color(0xa0, 0x00, 0x00), sf::Color(0xff, 0x80, 0x80) } };
	printer->botgrad_.colors[0].a = 0xaa;
	printer->botgrad_.colors[1].a = 0xee;

	printer->bodygrad_ = Gradient::gen('b', 'r');
	printer->bodygrad_.colors[0].a = 0xaa;
	printer->bodygrad_.colors[1].a = 0xee;

	printer->emptygrad_ = { {
		Color(0x00, 0x00, 0x00, 0x00),
		Color(0x00, 0x00, 0x00, 0xff)
	} };

	// set to adapter
	adapter.setField(p).
	setPrinter(printer).
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

void init_agelabel()
{
	// main
	agelabel.setFont( font );
	agelabel.setFillColor( maincolor );
	agelabel.setString( agestring.get() );
	agelabel.setCharacterSize( FONT_SIZE );

	// position
	auto bounds = agelabel.getLocalBounds();
	agelabel.setOrigin(
		bounds.width / 2.0,
		bounds.height
	);
	agelabel.setPosition(
		window.getSize().x / 8.0,
		( window.getSize().y + adapter.getSize().y ) / 2.0
	);

	return;
}

void init_speedlabel()
{
	// main
	speedlabel.setFont( font );
	speedlabel.setFillColor( maincolor );
	speedlabel.setCharacterSize( FONT_SIZE );
	speedlabel.setString( speedstring.get() );

	// position
	auto bounds = speedlabel.getGlobalBounds();
	speedlabel.setOrigin(
		bounds.width / 2.0,
		bounds.height
	);
	speedlabel.setPosition(
		window.getSize().x / 8.0 * 3.0,
		( window.getSize().y + adapter.getSize().y ) / 2.0
	);

	return;
}

void init_enslabel()
{
	// objects
	Text *labels[] = {
	 	&summenlabel, &groundenlabel, &plantenlabel,
		&botenlabel, &bodyenlabel
	};
	statstring_type *strings[] = {
		&summenstring, &groundenstring, &plantenstring,
		&botenstring, &bodyenstring
	};
	int i = 0;
	auto winsize = window.getSize();
	auto adsize = adapter.getSize();
	double r = ( winsize.y - adsize.y );

	for(auto l : labels)
	{
		l->setFont(font);
		l->setFillColor(maincolor);
		l->setCharacterSize(EN_FONT_SIZE);
		l->setString( strings[i]->get() );

		auto bounds = l->getGlobalBounds();
		l->setOrigin(
			bounds.width / 2.0,
			bounds.height
		);
		l->setPosition(
			winsize.x / 8.0 * ( 5 + i/3*2 ),
			adsize.y + r * (1+i%3) / 4
		);

		++i;
	}



	return;
}





// end
