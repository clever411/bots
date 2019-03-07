#include <iostream>
#include <chrono>

#include <clever/HelpFunction.hpp>
#include <clever/Stopwatch.hpp>
#include <clever/SFML/HelpFunction.hpp>

#include "declare.hpp"
#include "init.hpp"
#include "life.hpp"


using namespace clever;
using namespace sf;
using namespace std;





// main
int main( int argc, char *argv[] )
{
	// init
	init_window();
	init_field();
	init_adapter();
	init_font();
	init_agelabel();
	init_speedlabel();
	
	
	
	

	// objects
	bool updateflag = false;
	double updatespeed = 1.0f; // count per second
	speedstring = "speed: " + cutzero( to_string(updatespeed) );
	double updateperiod = 1.0 / updatespeed;
	double stage = 0.0f;
	Stopwatch<chrono::system_clock> watch;
	double timepass = 0.0f;
	int age = 0;





	// main loop
	Event event;
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
					field.zeroize();
					age = 0;
					agestring = "age: " + to_string(age);
					updateflag = false;
					break;
				case Keyboard::Add: case Keyboard::Up:
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
						speedstring = "speed: " + cutzero( to_string(updatespeed) );
					}
					break;
				case Keyboard::Subtract: case Keyboard::Down:
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
						speedstring = "speed: " + cutzero( to_string(updatespeed) );
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
		if(
			bool isleft = Mouse::isButtonPressed( Mouse::Button::Left );
			isleft || Mouse::isButtonPressed( Mouse::Button::Right )
		)
		{
			field.at(
				adapter.cursorOn(
					Vector2f(Mouse::getPosition(window)) -
					adapter.getPosition()
				)
			) = isleft ? 1 : 0;
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
			if( stage >= updateperiod )
			{
				do
				{
					stage -= updateperiod;
					update_field();
					++age;
				}
				while( stage >= updateperiod );
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
