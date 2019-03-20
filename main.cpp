#include <iostream>
#include <chrono>

#include <clever/HelpFunction.hpp>
#include <clever/Stopwatch.hpp>
#include <clever/SFML/HelpFunction.hpp>

#include "declare.hpp"
#include "init.hpp"

#include "Stat.hpp"


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
	init_enslabel();
	
	
	
	

	// objects
	bool
		up = false,
		upfield = false,
		upage = false,
		upspeed = true,
		writestat = false;

	bool
		ikeywaspush = false,
		bkeywaspush = false;

	double updatespeed = 1.0f; // count per second
	double updateperiod = 1.0 / updatespeed;
	double stage = 0.0f;

	Stopwatch<chrono::system_clock> watch;
	double timepass = 0.0f; // in seconds

	int age = 0;

	double
		summen, grounden,
		planten, boten;

	static constexpr int const LABELS_SIZE = 7;
	Text *labels[] = {
		&agelabel, &speedlabel,
		&summenlabel, &groundenlabel, &plantenlabel,
		&botenlabel, &bodyenlabel
	};
	statstring_type *strings[] = {
		&agestring, &speedstring,
		&summenstring, &groundenstring, &plantenstring,
		&botenstring, &bodyenstring
	};

	Stat stat;





	// main loop
	Event event;
	watch.start();
	while(window.isOpen())
	{
		// handle events
			// usual key
		while(window.pollEvent(event))
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
					field.reset();
					age = 0;
					up = false;
					upfield = true;
					upage = true;
					stat.write("resetstat.txt");
					stat.reset();
					break;
				case Keyboard::F:
					field.random_fill(100);
					upfield = true;
					break;
				case Keyboard::Add: case Keyboard::Up:
					if( updatespeed < 1000.0 )
					{
						if( updatespeed > 99.5 )
							updatespeed += 10.0;
						else if(updatespeed > 9.75)
							updatespeed += 1.0;
						else if(updatespeed > 2.95)
							updatespeed += 0.5;
						else
							updatespeed += 0.1;
						updateperiod = 1.0 / updatespeed;
						upspeed = true;
					}
					break;
				case Keyboard::Subtract: case Keyboard::Down:
					if(updatespeed > 0.15)
					{
						if(updatespeed > 105.0)
							updatespeed -= 10.0;
						else if(updatespeed > 10.5)
							updatespeed -= 1.0;
						else if(updatespeed > 3.25)
							updatespeed -= 0.5;
						else
							updatespeed -= 0.1;
						updateperiod = 1.0 / updatespeed;
						upspeed = true;
					}
					break;
				case Keyboard::Space:
					up = !up;
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

			// key press on field
		if(
			bool isikey = Keyboard::isKeyPressed( Keyboard::I ),
			isbkey = Keyboard::isKeyPressed( Keyboard::B ),
			isleft = Mouse::isButtonPressed( Mouse::Button::Left );
			isbkey || isikey || isleft || Mouse::isButtonPressed( Mouse::Button::Right )
		)
		{
			auto point = adapter.cursorOn(
				Vector2f(Mouse::getPosition(window)) -
				adapter.getPosition()
			);
			if(field.isValid(point))
			{
				auto &cell = field.at(point);
				if(isikey)
				{
					if(!ikeywaspush)
					{
						ikeywaspush = true;
						if(cell.plant)
						{
							cout << "it's plant\n"
								"energy: " << cell.plant->energy << "\n"
								"------------------------------" << endl;
						}
						else if(cell.bot)
						{
							cout << "it's bot\n"
								"energy:     " << cell.bot->energy      << "\n"
								"age:        " << cell.bot->age         << "\n"
								"generation: " << cell.bot->generation  << "\n\n"
								"step price: " << cell.bot->steppricek  << "\n"
								"age tax:    " << cell.bot->agesteptaxk << "\n"
								"max energy: " << cell.bot->maxenergyk  << "\n"
								"bud req:    " << cell.bot->budreqk     << "\n"
								"bud price:  " << cell.bot->budpricek   << "\n"
								"------------------------------\n\n" << endl;
						}
						else if(cell.body)
						{
							cout << "it's body\n"
								"energy: " << cell.body->energy << "\n"
								"age:    " << cell.body->age << "\n"
								"------------------------------" << endl;
						}
					}
				}
				else
				{
					upfield = true;
					if(isbkey)
					{
						Bot *bot = new Bot(Bot::DEFAULT);
						bot->energy = bot->budprice();
						field.push( point.first, point.second, bot );
					}
					else if(isleft)
						field.fillground(point.first, point.second);
					else
						field.push(
							point.first, point.second,
							new Plant(Plant::DEFAULT)
						);
				}
			}
		}
		else
		{
			ikeywaspush = bkeywaspush = false;
		}


		
		// update
			// update time
		timepass = chrono::duration_cast<
			chrono::duration< double, ratio<1> >
		>( watch.stop().duration() ).count();
		watch.reset().start();


			// update field
		if( up )
		{
			stage += timepass;
			if( stage >= updateperiod )
			{
				do
				{
					stage -= updateperiod;
					field.update_field();
					++age;
					stat.add(
						field.summen,
						field.grounden,
						field.planten,
						field.boten,
						field.bodyen
					);
				}
				while( stage >= updateperiod );
				upfield = true;
				upage = true;
				writestat = true;
			}
		}

			// up strings
		if( upage )
		{
			agestring = "age: " + to_string(age);
			upage = false;
		}

		if( upspeed )
		{
			speedstring = "speed: " + cutzero( to_string(updatespeed) );
			upspeed = false;
		}

		if( upfield )
		{
			summenstring =
				"summ energy:   " +
				to_string( int( round(field.summen) ) );

			groundenstring =
				"ground energy: " +
				cutzero( to_string( int( field.grounden * 10.0 ) / 10.0 ) );

			plantenstring =
				"plants energy: " +
				cutzero( to_string( int( field.planten * 10.0 ) / 10.0 ) );

			botenstring =
				"bots energy:   " +
				cutzero( to_string( int( field.boten * 10.0 ) / 10.0 ) );

			bodyenstring =
				"bodyes energy: " +
				cutzero( to_string( int( field.bodyen * 10.0 ) / 10.0 ) );

			adapter.update();
			upfield = false;
		}

			// update text labels
		for(int i = 0; i < LABELS_SIZE; ++i)
			if( strings[i]->isChanged() )
				labels[i]->setString( strings[i]->get() );



		// draw
		window.clear( Color(backgroundcolor) );
		window.draw( adapter );
		for(auto i : labels)
			window.draw(*i);
		window.display();
	}
	
	stat.write("endstat.txt");

	
	
	
	
	return 0;
}





// end
