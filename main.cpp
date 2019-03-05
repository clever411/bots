#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <clever/Field.hpp>
#include <clever/SFML/FieldAdapter.hpp>
#include <clever/SFML/CellPrinter.hpp>


using namespace sf;
using namespace std;





// types
typedef int value_type;
typedef clever::Field<value_type> field_type;
typedef clever::CellPrinter<value_type> printer_type;
typedef clever::FieldAdapter<value_type, printer_type> adapter_type;





// global objects
	// SFML
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 60u;

Event event;



	// Field
field_type field;
adapter_type adapter;





// init
void init_window()
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
	// core
	shared_ptr<field_type> p(
		&field,
		[](field_type *) { return; }
	);
	adapter.setField( p ).
	setSize(
		Vector2f( window.getSize() )
	).
	update().
	setBordertocell(0.15f);


	// size
	auto size = adapter.getSize();
	auto wsize = window.getSize();
	adapter.setPosition(
		( wsize.x - size.x ) / 2.0,
		( wsize.y - size.y ) / 2.0
	);


	return;
}

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
	init_window();
	init_field(field);
	init_adapter(adapter, field);
	
	
	
	

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
				case Keyboard::Space:
					update_field(field);
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
					Vector2f(Mouse::getPosition()) -
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
		adapter.update();



		// draw
		window.clear(Color::White);
		window.draw(adapter);
		window.display();
	}
	
	
	
	
	
	return 0;
}





// end
