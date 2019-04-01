#include <iostream>
#include <chrono>

#include <clever/HelpFunction.hpp>
#include <clever/Stopwatch.hpp>
#include <clever/SFML/HelpFunction.hpp>

#include "declare.hpp"
#include "init.hpp"
#include "BotField.hpp"
#include "Cell.hpp"
#include "Plant.hpp"
#include "Bot.hpp"
#include "Body.hpp"
#include "Mineral.hpp"
#include "CellPrinter.hpp"
#include "Stat.hpp"


using namespace clever;
using namespace sf;
using namespace std;





// functions
void print(Bot const &bot)
{
	cout << "it's bot\n"
		"energy:     " << bot.energy      << "\n"
		"age:        " << bot.age         << "\n"
		"generation: " << bot.generation  << "\n\n"
		"step price: " << bot.steppricek  << "\n"
		"age tax:    " << bot.agesteptaxk << "\n"
		"max energy: " << bot.maxenergyk  << "\n"
		"bud req:    " << bot.budreqk     << "\n"
		"bud price:  " << bot.budpricek   << "\n\n"
		"brain:";

	for(int i = 0; i < Bot::BRAIN_SIZE; ++i)
	{
		if(i % 8 == 0)
		{
			cout << '\n';
			if(!i)
				cout << fills("m)", 4);
			else if(i%16 || i/16 < 2)
				cout << fills("", 4);
			else
				cout << fills(
					to_string(i/16 - 2) + ")",
					4
				);
		}

		auto action = bot.brain[i];
		auto param = action >> 3;
		action &= Bot::MASK;
		switch(action)
		{
		case Bot::NUL:
			cout << fills("NUL", 10);
			break;
		case Bot::MOVE:
			cout << fills("MOVE", 10);
			break;
		case Bot::EAT:
			cout << fills("EAT", 10);
			break;
		case Bot::TURN:
			cout << fills(
				"TURN(" + to_string(param%3) + ")",
				10
			);
			break;
		case Bot::CHECK:
			cout << fills("CHECK", 10);
			break;
		case Bot::CALL:
			cout << fills(
				"CALL(" + to_string(param%Bot::FUN_COUNT) + ")",
				10
			);
			break;
		case Bot::JUMP_FORWARD:
			cout << fills(
				"JUMPF(" + to_string(param) + ")",
				10
			);
			break;
		case Bot::JUMP_BACKWARD:
			cout << fills(
				"JUMPB(" + to_string(param) + ")",
				10
			);
			break;
		}
	}

	cout << "\n"
		"addr: " << &bot << "\n"
		// "wage: " << bot.worldage   << "\n"
		"p:    " << bot.p   << "\n"
		"dir:  " << bot.dir << "\n"
		"------------------------------\n\n";

	return;
}

void print(Plant const &plant)
{
	cout << "it's plant\n"
		"energy: " << plant.energy << "\n"
		"------------------------------\n\n";
	return;
}

void print(Body const &body)
{
	cout << "it's body\n"
		"energy: " << body.energy << "\n"
		"age:    " << body.age << "\n"
		"------------------------------\n\n";

	return;
}

void print(Cell const &cell)
{
	cout << "it's empty\n"
		"energy: " << cell.energy << "\n"
		"------------------------------\n\n";

	return;
}

void increase_speed(double &s)
{
	if( s > 99.5 )
		s += 10.0;
	else if(s > 9.75)
		s += 1.0;
	else if(s > 2.95)
		s += 0.5;
	else
		s += 0.1;
	return;
}

void reduce_speed(double &s)
{
	if(s > 105.0)
		s -= 10.0;
	else if(s > 10.5)
		s -= 1.0;
	else if(s > 3.25)
		s -= 0.5;
	else
		s -= 0.1;
	return;
}





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

	double updatespeed = 1.0f; // count per second
	double updateperiod = 1.0 / updatespeed;
	double stage = 0.0f;

	Stopwatch<chrono::system_clock> watch;
	double timepass = 0.0f; // in seconds

	int age = 0;

	double
		summen, grounden,
		planten, boten;

	static constexpr int const LABELS_COUNT = 7;
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
	PointI pos;
	Cell *cell;
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
				case Keyboard::G:
					field.ravage_ground(0.1);
					break;
				case Keyboard::I:
					pos = adapter.cursorOn(
						makep<float>(Mouse::getPosition(window))
					);
					if(field.isValid(pos))
					{
						cell = &field.at(pos);
						if(cell->bot)
							print(*cell->bot);
						else if(cell->body)
							print(*cell->body);
						else if(cell->plant)
							print(*cell->plant);
						else
							print(*cell);
					}
					break;
				case Keyboard::Add: case Keyboard::Up:
					if( updatespeed < 4000.0 )
					{
						increase_speed(updatespeed);
						updateperiod = 1.0 / updatespeed;
						upspeed = true;
					}
					break;
				case Keyboard::Subtract: case Keyboard::Down:
					if(updatespeed > 0.15)
					{
						reduce_speed(updatespeed);
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
			bool isbkey = Keyboard::isKeyPressed( Keyboard::B ),
			isleft = Mouse::isButtonPressed( Mouse::Button::Left ),
			isright = Mouse::isButtonPressed( Mouse::Button::Right );
			isbkey || isleft || isright
		)
		{
			pos = adapter.cursorOn(
				makep<float>(Mouse::getPosition(window))
			);
			if(field.isValid(pos))
			{
				auto &cell = field.at(pos);
				upfield = true;
				if(isbkey)
				{
					Bot *bot = new Bot(Bot::DEFAULT);
					bot->energy = bot->budprice();
					field.push( pos.x, pos.y, bot );
				}
				else if(isleft)
					field.push(pos.x, pos.y);
				else if(isright)
					field.push(
						pos.x, pos.y,
						new Plant
					);
			}
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
					field.update();
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
		for(int i = 0; i < LABELS_COUNT; ++i)
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
