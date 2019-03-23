#ifndef CLEVER_WIDGET_FACTORY_HPP
#define CLEVER_WIDGET_FACTORY_HPP

#include <utility>
#include <vector>

#include "Widgets.hpp"





namespace clever
{



/*
 * 	Этот класс предназначен для упрощения создания виджетов. Экземпляр
 * класса состоит из одной сущности:
 * 	- набор.
 * 	Набор - константный указатель на экземпляр класса WidgetFactorySet.
 * Он необходим для указания какие цвета ставить, кокого размера ставить
 * отступы и т.п.
 */

class WidgetFactory
{
public:
	/*
	 * Конструктор объекта, если набор не указан будет использован
	 * набор по умолчанию(WidgetFactorySet::getDefault()).
	 */
	WidgetFactory(WidgetFactorySet const *set = nullptr);

	/*
	 * Создает кнопку. Вариант определяет вариант декоратора,
	 * которым будет инициализированна кнопка.
	 */
	Button *createButton(
		unsigned int decvariant = 0,
		Widget *widget = nullptr
	) const;

	Button *createButton(
		unsigned int decvariant,
		Widget *widget,
		std::function<void(sf::Mouse::Button)> const &fun
	) const;

	/*
	 * Создает разметку определенного варианта, возвращает указатель.
	 */
	Layout *createLayout(
		unsigned int variant = 0,
		Layout::Orientation orientation = Layout::horizontal,
		std::vector<Widget*> const &elements = {}
	) const;

	/*
	 * Создает прямоугольный декоратор определенного варианта, 
	 * возвращает указатель.
	 */
	RectangleDecorator *createRectangleDecorator(
		unsigned int variant = 0,
		Widget *widget = nullptr
	) const;

	Spacer *createSpacer(
		sf::Vector2f const &size = {0.0f, 0.0f}
	) const;

	/*
	 * Создает статус бар определенного варианта, возвращает указатель.
	 */
	StatusBar *createStatusBar(
		unsigned int variant = 0,
		clever::ChangingObject<std::string> const *status = nullptr
	) const;

	/*
	 * Создает статус бар определенного варианта, устанавливает
	 * пространство, возвращает указатель.
	 */
	StatusBar *createStatusBar(
		unsigned int variant,
		clever::ChangingObject<std::string> const *status,
		sf::Vector2f const &spaces
	) const;


	/*
	 * Создает статус бар определенного варанта, создает кнопку, в
	 * качестве потомка у которой выступает статус бар. Возвращает
	 * указатели на оба объекта.
	 */
	std::pair<Button*, StatusBar*> createClickableStatusBar(
		unsigned int decvariant = 0,
		unsigned int barvariant = 0,
		clever::ChangingObject<std::string> const *status = nullptr
	) const;

	/*
	 * Тоже что и выше, но сразу устанавливает функцию кнопке.
	 */
	std::pair<Button*, StatusBar*> createClickableStatusBar(
		unsigned int decvariant,
		unsigned int barvariant,
		clever::ChangingObject<std::string> const *status,
		std::function<void(sf::Mouse::Button)> const &fun
	) const;

	/*
	 * Создает разметку определенного варианта и прямоукольный декоратор
	 * определенного варианта. Помещает разметку в декоратор. Возвращает
	 * указатели на оба объекта. Первый - декоратор, второй - разметка.
	 */
	std::pair<RectangleDecorator*, Layout*> createDecorativeLayout(
		unsigned int decvariant = 0,
		unsigned int layvariant = 0,
		Layout::Orientation orientation = Layout::horizontal,
		std::vector<Widget*> const &elements = {}
	) const;

	/*
	 * Создает статус бар определенного варианта и прямоугольный декоратор
	 * определенного варианта. Помещает статус бар в декоратор. Возвращает
	 * указатели на оба объекта. Первый - декоратор, второй - разметка.
	 */
	std::pair<RectangleDecorator*, StatusBar*> createDecorativeStatusBar(
		unsigned int decvariant = 0,
		unsigned int barvariant = 0,
		clever::ChangingObject<std::string> const *status = nullptr
	) const;

private:
	WidgetFactorySet const *_set;
	
};



}





#endif
