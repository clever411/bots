#ifndef LABEL_HPP
#define LABEL_HPP

#include <functional>
#include <string>

#include <SFML/Graphics.hpp>





struct Label: public sf::Text
{
	std::function<std::string()> value;
	inline Label &update()
	{
		setString(value());
		return *this;
	}
};





#endif
