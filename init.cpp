#include <cstring>
#include <memory>

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
	shared_ptr<field_type> p(
		&field,
		[](field_type *) { return; }
	);
	adapter.setField( p ).
	setSize(
		Vector2f( window.getSize() )
	).
	update().
	setGridColor(Color(gridcolor)).
	setDrawBoundsEnable(false).
	update();


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
		window.getSize().x / 3.0,
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
		window.getSize().x * 2.0 / 3.0,
		( window.getSize().y + adapter.getSize().y ) / 2.0
	);

	return;
}





// end
