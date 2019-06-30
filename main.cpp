#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <set>

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
void print(Plant const &plant)
{
	cout << "it's plant\n"
		"energy: " << plant.energy << "\n"
		"------------------------------\n\n";
	return;
}

void print(Bot const &bot)
{
	static auto const
		acttostr = [](Bot::neuron_type neuron)->string
		{
			string str;
			switch(Bot::getaction(neuron))
			{
			case Bot::NUL:
				return "NUL";
			case Bot::MOVE:
				return "MOV";
			case Bot::EAT:
				str = "EAT ";
				switch(Bot::getarg(neuron))
				{
				case 0: // plant
					str.push_back('P');
					return str;
				case 1: // body
					str.push_back('B');
					return str;
				case 2: // minerals
					str.push_back('M');
					return str;
				case 3: // air
					str.push_back('A');
					return str;
				default:
					throw logic_error("print(Bot) -> switch::EAT::switch");
				}
			case Bot::CHECK:
				str = "CHK ";
				switch(Bot::getarg(neuron))
				{
				case 0: // empty
					str.push_back('E');
					return str;
				case 1: // plant
					str.push_back('P');
					return str;
				case 2: // bot
					str += "BT";
					return str;
				case 3: // body
					str += "BD";
					return str;
				case 4: // mineral
					str.push_back('M');
					return str;
				default:
					throw logic_error("print(Bot) -> switch::Bot::CHECK: ");
				}
			case Bot::TURN:
				str = "TRN ";
				switch(Bot::getarg(neuron))
				{
				case 0:
					str.push_back('L');
					return str;
				case 1:
					str.push_back('R');
					return str;
				case 2:
					str += "RD";
					return str;
				default:
					throw logic_error("print(Bot) switch::Bot::TURN");
				}
			default:
				throw logic_error("print(Bot) switch");
			}
		};



	// main
	cout << "it's bot\n"
		"energy:     " << bot.energy      << "\n"
		"age:        " << bot.age         << "\n"
		"generation: " << bot.generation  << "\n\n"
		"gen:\n";
	bot.gen.print(cout, "    ") << "\n\n";



	// print brain
	cout << "brain" << endl;

	list<int> row = { 0 };
	set<int> was;

	string str;
	bool notempty = true;
	while(notempty)
	{
		notempty = false;
		int count = row.size();
		for(auto b = row.begin(); count; --count, ++b)
		{
			static constexpr int const CFILLS = 18;

			if(*b < 0)
			{
				cout << fills("", CFILLS);
				continue;
			}

			if(was.find(*b) != was.end())
			{
				cout << fills("end", CFILLS);
				*b = -1;
				continue;
			}

			notempty = true;
			was.insert(*b);
			str = fills(to_string(*b), 3) +
				fills(acttostr( bot.brain[*b] ), 7);

			if(bot.getaction( bot.brain[*b] ) == Bot::NUL) 
			{
				str += to_string(++*b);
			}
			else if(bot.getaction( bot.brain[*b] ) == Bot::CHECK)
			{
				str += to_string( bot.getjumpf( bot.brain[*b] ) ) + "," +
					to_string( bot.getjumps( bot.brain[*b] ) );
				row.push_back(int( bot.getjumps( bot.brain[*b] ) ));
				*b = bot.getjumpf( bot.brain[*b] );
			}
			else
			{
				str += to_string( bot.getjumpf( bot.brain[*b] ) );
				*b = bot.getjumpf( bot.brain[*b] );
			}

			cout << fills(str, CFILLS);
		}

		cout << endl;
	}



	// other
	cout << "\n"
		"p:    " << bot.p   << "\n"
		"dir:  " << bot.dir << "\n"
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

void print(Mineral const &mineral)
{
	cout << "it's mineral\n"
		"energy: " << mineral.energy << "\n"
		"------------------------------\n\n";

	return;
}

void print(Cell const &cell)
{
	if(cell.bot)
		print(*cell.bot);
	else if(cell.body)
		print(*cell.body);
	else if(cell.plant)
		print(*cell.plant);
	else
		cout << "it's empty\n"
			"energy: " << cell.energy << "\n"
			"hid mineral energy: " << cell.mineral.hidenergy << "\n"
			"mineral energy: " << cell.mineral.energy << "\n"
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



void draw_mappings()
{
	static constexpr int const MODE_COUNT = 6;
	static constexpr MapUnitPrinter::Mode const modes[] = {
		MapUnitPrinter::Mode::groundmode,
		MapUnitPrinter::Mode::airmode,
		MapUnitPrinter::Mode::plantmode,
		MapUnitPrinter::Mode::botmode,
		MapUnitPrinter::Mode::bodymode,
		MapUnitPrinter::Mode::mineralmode
	};

	for(int i = 0; i < MODE_COUNT; ++i)
	{
		mapprinter.setMode(modes[i]);
		mapadapter.setPosition(
			(*mappinglay)(i)
		);
		window.draw(mapadapter);
	}
	
	return;
}





// main
int main( int argc, char *argv[] )
{
	// init
	init();
	

	
	// objects
	bool
		up = false,
		upfield = true,
		writestat = false;

	double updatespeed = 100.0f; // count per second
	double updateperiod = 1.0 / updatespeed;
	double stage = 0.0f;

	Stopwatch<chrono::system_clock> watch;
	double timepass = 0.0f; // in seconds

	int age = 0.0;

	double
		summen, grounden,
		planten, boten;

	Stat stat;

	labels[0].getval = [&]()->string {
		return string("age:   ") + to_string(age);
	};
	labels[1].getval = [&]()->string {
		return string("speed: ") + cutzero( to_string(updatespeed) );
	};





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
					labels[0].change();
					up = false;
					upfield = true;
					stat.write("resetstat.txt");
					stat.reset();
					break;

				case Keyboard::F:
					field.random_fill(200);
					upfield = true;
					break;

				case Keyboard::G:
					field.ravage_ground(0.1);
					upfield = true;
					break;

				case Keyboard::H:
					field.random_bots(10);
					upfield = true;
					break;

				case Keyboard::I:
					pos = adapter.cursorOn(
						makep<float>(Mouse::getPosition(window))
					);
					if(field.isValid(pos))
					{
						cell = &field.at(pos);
						print(field.at(pos));
					}
					break;

				case Keyboard::M:
					printer.changeMode();
					break;

				case Keyboard::Add: case Keyboard::Up:
					if( updatespeed < 4000.0 )
					{
						increase_speed(updatespeed);
						updateperiod = 1.0 / updatespeed;
						labels[1].change();
					}
					break;

				case Keyboard::Subtract: case Keyboard::Down:
					if(updatespeed > 0.15)
					{
						reduce_speed(updatespeed);
						updateperiod = 1.0 / updatespeed;
						labels[1].change();
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
					Bot *bot = new Bot();
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
					stat.add( {
						(float)field.summen,
						(float)field.grounden,
						(float)field.airen,
						(float)field.planten,
						(float)field.boten,
						(float)field.bodyen,
						(float)field.mineralen
					} );
				}
				while( stage >= updateperiod );
				upfield = true;
				writestat = true;
			}
		}

		if( upfield )
		{
			for(int i = 2; i < LABELS_COUNT; ++i)
				labels[i].change();

			adapter.update();
			mapadapter.update();
			upfield = false;
		}

			// update labels
		for(int i = 0; i < LABELS_COUNT; ++i)
			labels[i].update();



		// draw
		window.clear( Color(backgroundcolor) );
		window.draw( adapter );
		draw_mappings();
		for(int i = 0; i < LABELS_COUNT; ++i)
			window.draw(labels[i]);
		window.display();
	}
	
	stat.write("endstat.txt");

	
	
	
	
	return 0;
}





// end
