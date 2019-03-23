#ifndef CLEVER_WIDGET_BOX_HPP
#define CLEVER_WIDGET_BOX_HPP

#include <SFML/Graphics.hpp>



namespace clever
{



/*
 * 	Этот класс предоставляет абстракцию виджета. Виджет можно
 * трансформировать, рисовать и обновлять. Также можно узнать размер
 * виджета и был ли он изменен с прошлого сброса флага resized.
 * При клике по виджету вызывается соответствующая функция.
 */

class Widget:
	public sf::Transformable, // Объект можно трансформировать
	public sf::Drawable // Объект можно рисовать
{
public:
	/*
	 * Конструктор.
	 */
	Widget();
	/*
	 * Деструктор. Виртуалный.
	 */
	virtual ~Widget();

	/*
	 * Обновить, передается аргумент - время.
	 */
	virtual void update(double time) = 0;
	/*
	 * Вызывается, когда по виджету происходит клик.
	 * По умолчанию ничего не делает.
	 */
	virtual void onClick(
		sf::Mouse::Button button,
		sf::Vector2f const &koor
	);

	/*
	 * Возвращает размер виджета. Размер определяет сколько пространства
	 * в окне виджет занимает. Используется для разметки и для
	 * автоматичской установки размера дакоратора и т.п.
	 */
	virtual sf::Vector2f getSize() const = 0;
	/*
	 * Информирует был ли изменен размер с прошлого сброса флага.
	 * Используется для того, чтобы каждый раз не вычислять, где должны
	 * находиться объкты в разметке и т.п.
	 */
	virtual bool isResized() const = 0;
	/*
	 * Сбрасывает флаг resized.
	 */
	virtual void resetResized() = 0;

private:
	/*
	 * Объект копировать нельзя.
	 */
	Widget(Widget const &widget);
	Widget& operator=(Widget const &widget);
	
};



}



#endif
