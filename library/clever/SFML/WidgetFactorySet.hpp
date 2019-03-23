#ifndef CLEVER_WIDGET_FACTORY_SET_HPP
#define CLEVER_WIDGET_FACTORY_SET_HPP

#include <vector>
#include <SFML/Graphics.hpp>



namespace clever
{



struct WidgetFactorySet
{
	static WidgetFactorySet const *getDefault();
	WidgetFactorySet();
	~WidgetFactorySet();

	std::vector<sf::Vector2f> layoutBorders;
	
	std::vector<sf::RectangleShape> decoratorRectangles;
	std::vector<sf::Vector2f> decoratorBorders;
	
	std::vector<sf::RectangleShape> rectangleWidgets;

	std::vector<sf::Text> statusbarTexts;
	std::vector<sf::Vector2f> statusbarSpaces;

private:
	static WidgetFactorySet _initDefault();
	static sf::Font _initFont();
};



}



#endif
