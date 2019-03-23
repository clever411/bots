#ifndef CLEVER_BUTTON_HPP
#define CLEVER_BUTTON_HPP

#include <functional>
#include "RectangleDecorator.hpp"





namespace clever {





/*
 * 	Класс предназначен для отлавливания нажатий. При нажатии
 * вызывается установленная функция(по умолчанию ничего).
 * 	Класс наследутеся от RectangleDecorator, поэтому необходимо
 * установить потомка экземпляру для корректного отбражения виджета.
 */

class Button: public RectangleDecorator
{
public:
	/*
	 * Конструктор. Передает все аргументы в конструктор
	 * RectangleDecorator.
	 */
	Button(
		Widget *widget = nullptr,
		sf::RectangleShape *rect = nullptr,
		sf::Vector2f const &borders = {0.0f, 0.0f}
	);

	/*
	 * Деструктор. Ничего не делает.
	 */
	virtual ~Button();



	/*
	 * Вызывает установленную функцию, по умолчанию функция не
	 * установлена, поэтому ничего не вызывается.
	 */
	virtual void onClick(
		sf::Mouse::Button button,
		sf::Vector2f const &
	) override;

	/*
	 * Возвращает установленную функцию.
	 */
	std::function<void(sf::Mouse::Button)> const &
	getOnClickFunction() const;
	
	/*
	 * Устанавливает функцию.
	 */
	void setOnClickFunction(
		std::function<void(sf::Mouse::Button)> const &newfun
	);


private:
	std::function<void(sf::Mouse::Button)> _onclickfun;


};




}





#endif
