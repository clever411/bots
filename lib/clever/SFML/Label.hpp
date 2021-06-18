#ifndef LABEL_HPP
#define LABEL_HPP

#include <functional>
#include <string>

#include <SFML/Graphics.hpp>





struct Label: public sf::Text
{
	std::function<std::string()> getval;

	inline void update()
	{
		if(ischange_)
		{
			adjust();
			ischange_ = false;
		}
		return;
	}

	inline void adjust()
	{
		setString(getval());
		return;
	}

	inline void change() const
	{
		ischange_ = true;
		return;
	}

private:
	mutable bool ischange_ = true;

};





#endif
