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
	field.init(
		DEFAULT_FIELD_WIDTH,
		DEFAULT_FIELD_HEIGHT
	).
	zeroize();
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
	setDrawBoundsEnable(false);


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
	agelabel.setCharacterSize( 60 );

	// position
	agelabel.setOrigin(
		agelabel.getGlobalBounds().width / 2.0,
		0
	);
	agelabel.setPosition(
		window.getSize().x / 3.0,
		adapter.getSize().y + 10.0
	);
	return;
}

void init_speedlabel()
{
	// main
	speedlabel.setFont( font );
	speedlabel.setFillColor( maincolor );
	speedlabel.setCharacterSize( 60 );
	speedlabel.setString( speedstring.get() );

	// position
	speedlabel.setOrigin(
		speedlabel.getGlobalBounds().width / 2.0,
		0
	);
	speedlabel.setPosition(
		window.getSize().x * 2.0 / 3.0,
		adapter.getSize().y + 10.0
	);

	return;
}





// end
