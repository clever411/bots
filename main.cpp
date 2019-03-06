#include <cstring>
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include <clever/ChangingObject.hpp>
#include <clever/Field.hpp>
#include <clever/HelpFunction.hpp>
#include <clever/Stopwatch.hpp>
#include <clever/SFML/FieldAdapter.hpp>
#include <clever/SFML/HelpFunction.hpp>


using namespace clever;
using namespace sf;
using namespace std;







// types
typedef struct CellPrinter: public RectangleShape
{
	CellPrinter(int value = 0)
	{
		set(value);
		return;
	}
	~CellPrinter() {}

	CellPrinter &set(int value);

} printer_type;

typedef int value_type;
typedef Field<value_type> field_type;
typedef FieldAdapter<value_type, printer_type> adapter_type;
typedef ChangingObject<string> statstring_type;








// global objects
	// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 144u;

Color const backgroundcolor(0xfd, 0xea, 0xa8);
Color const gridcolor(0xec, 0xc9, 0x97);
Color const maincolor(0x30, 0x21, 0x12);

Event event;
Font font;



	// Field & Widgets
field_type field;
adapter_type adapter;
Text agelabel;
Text speedlabel;
statstring_type agestring("age: 0  ");
statstring_type speedstring("speed: 0.0");







// CellPrinter realization
printer_type &printer_type::set(int value)
{
	switch(value)
	{
	case 0:
		setFillColor( Color::Transparent );
		break;
	default:
		setFillColor( Color( maincolor ) );
		break;
	}
	return *this;
}




// init functions
void init_window( RenderWindow &window )
{
	window.create(vmode, TITLE, Style::None);
	window.setPosition({0u, 0u});
	window.setFramerateLimit(FRAMERATE_LIMIT);
	return;
}

void init_field( field_type &field )
{
	constexpr int const DEFAULT_WIDTH = 50;
	constexpr int const DEFAULT_HEIGHT = 25;

	field.w = DEFAULT_WIDTH;
	field.h = DEFAULT_HEIGHT;
	field.d = new value_type[ field.w*field.h ];
	memset( field.d, 0, sizeof(value_type)*field.w*field.h );
	return;
}

void init_adapter( adapter_type &adapter, field_type &field )
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

void init_font(Font &font)
{
	font.loadFromFile( "Anonymous_Pro.ttf" );
	return;
}

void init_agelabel( Text &agelabel, Font const &font )
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

void init_speedlabel( Text &label, Font const &font )
{
	// main
	label.setFont( font );
	label.setFillColor( maincolor );
	label.setCharacterSize( 60 );
	label.setString( speedstring.get() );

	// position
	label.setOrigin(
		label.getGlobalBounds().width / 2.0,
		0
	);
	label.setPosition(
		window.getSize().x * 2.0 / 3.0,
		adapter.getSize().y + 10.0
	);

	return;
}



// update functions
bool update_cell( field_type const &field, int x, int y )
{
	int count = 0;

	if( field.tapeAt( x-1, y-1 ) )
		++count;
	if( field.tapeAt( x, y-1 ) )
		++count;
	if( field.tapeAt( x+1, y-1 ) )
		++count;

	if( field.tapeAt( x-1, y ) )
		++count;
	if( field.tapeAt( x+1, y ) )
		++count;

	if( field.tapeAt( x-1, y+1 ) )
		++count;
	if( field.tapeAt( x, y+1 ) )
		++count;
	if( field.tapeAt( x+1, y+1 ) )
		++count;

	return field.at(x, y) ?
		( count == 2 || count == 3 ) :
		( count == 3 );
}

void update_field( field_type &field )
{
	static field_type spf = {0, 0, nullptr};
	if(spf.w != field.w || spf.h != field.h)
	{
		if(spf.d)
			delete[] spf.d;
		spf = {
			field.w, field.h,
			new field_type::value_type[ field.w*field.h ]
		};
	}
	for(int x = 0; x < field.w; ++x)
	{
		for(int y = 0; y < field.h; ++y)
		{
			spf.at(x, y) = update_cell(field, x, y) ? 6 : 0;
		}
	}
	swap( field.d, spf.d );
	return;
}







// main
int main( int argc, char *argv[] )
{
	// init
	init_window(window);
	init_field(field);
	init_adapter(adapter, field);
	init_font(font);
	init_agelabel(agelabel, font);
	init_speedlabel(speedlabel, font);
	
	
	
	

	// objects
	bool updateflag = false;
	double updatespeed = 1.0f; // count per second
	speedstring.change(
		"speed: " + cutzero( to_string(updatespeed) )
	);
	double updateperiod = 1.0 / updatespeed;
	double stage = 0.0f;
	Stopwatch<chrono::system_clock> watch;
	double timepass = 0.0f;
	int age = 0;





	// main loop
	watch.start();
	while(window.isOpen())
	{
		// handle events
			// main
		if(window.pollEvent(event))
		{

			switch(event.type)
			{
			case Event::KeyPressed:

				switch(event.key.code)
				{
				case Keyboard::C:
					window.close();
					continue;
				case Keyboard::R:
					memset(
						field.d, 0,
						sizeof(field_type::value_type) * field.w * field.h
					);
					age = 0;
					agestring.change( "age: " + to_string(age) );
					updateflag = false;
					break;
				case Keyboard::Add:
					if( updatespeed < 100.0 )
					{
						if(updatespeed > 9.75)
							updatespeed += 1.0;
						else
							if(updatespeed > 2.95)
								updatespeed += 0.5;
							else
								updatespeed += 0.1;
						updateperiod = 1.0 / updatespeed;
						speedstring.change(
							"speed: " + cutzero(to_string(updatespeed))
						);
					}
					break;
				case Keyboard::Subtract:
					if(updatespeed > 0.15)
					{
						if(updatespeed > 10.5)
							updatespeed -= 1.0;
						else
							if(updatespeed > 3.25)
								updatespeed -= 0.5;
							else
								updatespeed -= 0.1;
						updateperiod = 1.0 / updatespeed;
						speedstring.change(
							"speed: " + cutzero(to_string(updatespeed))
						);
					}
					break;
				case Keyboard::Space:
					updateflag = !updateflag;
					stage = 0.0f;
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}

		}

			// mouse press
		if( Mouse::isButtonPressed( Mouse::Button::Left ) )
		{
			field.at(
				adapter.cursorOn(
					Vector2f(Mouse::getPosition(window)) -
					adapter.getPosition()
				)
			) = 6;
		}

			// key press
		if( Keyboard::isKeyPressed( Keyboard::C ) )
		{
			window.close();
			continue;
		}


		
		// update
			// update time
		timepass = chrono::duration_cast<
			chrono::duration< double, ratio<1> >
		>( watch.stop().duration() ).count();
		watch.reset().start();

			// update field
		if( updateflag )
		{
			stage += timepass;
			while( stage >= updateperiod )
			{
				stage -= updateperiod;
				update_field( field );
				++age;
				agestring.change( "age: " + to_string(age) );
			}
		}
		adapter.update();

			// update labels
		if( agestring.isChanged() )
			agelabel.setString( agestring.get() );
		if( speedstring.isChanged() )
			speedlabel.setString( speedstring.get() );



		// draw
		window.clear( Color(backgroundcolor) );
		window.draw(adapter);
		window.draw(agelabel);
		window.draw(speedlabel);
		window.display();
	}
	
	
	
	
	
	return 0;
}





// end
