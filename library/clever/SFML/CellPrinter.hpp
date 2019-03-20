#ifndef CLEVER_CELL_PRINTER_HPP
#define CLEVER_CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>





namespace clever
{





template<typename T>
class CellPrinter: public sf::RectangleShape
{
public:
	// types
	typedef T value_type;


	// constructor
	CellPrinter(value_type const &value = value_type());
	~CellPrinter();


	// set value
	CellPrinter &set(value_type const &value);

};





// constructor, destructor
template<typename T>
CellPrinter<T>::CellPrinter(value_type const &value)
{
	set(value);
	return;
}

template<typename T>
CellPrinter<T>::~CellPrinter() {}



// set value
template<typename T>
CellPrinter<T> &CellPrinter<T>::set(value_type const &value)
{
	switch(value) {
	case 0:
		setFillColor(sf::Color::White);
		break;
	case 1:
		setFillColor(sf::Color::Red);
		break;
	case 2:
		setFillColor(sf::Color::Yellow);
		break;
	case 3:
		setFillColor(sf::Color::Green);
		break;
	case 4:
		setFillColor(sf::Color::Blue);
		break;
	case 5:
		setFillColor(sf::Color::Magenta);
		break;
	case 6:
		setFillColor(sf::Color::Black);
		break;
	default:
		setFillColor(sf::Color::Transparent);
		break;
	}

	return *this;
}




}





#endif
