#ifndef CLEVER_LAYOUT_HPP
#define CLEVER_LAYOUT_HPP

#include <vector>
#include "Widget.hpp"

namespace clever
{

/*
 * 	Экземпляр класса состоит из следующих
 * сущностей:
 * 	- массив элементов(далее элементы);
 * 	- отступы;
 * 	- флаг ориентации;
 * 	- выравнивание;
 * 	- флаг resized.
 * 	Элементы - элементы, которые будут рисоваться
 * друг за другом(горизонтально или вертикально).
 * 	Отступы - промежутки, которые будут оставляться
 * между элементами.
 * 	Флаг ориентации определяет, где будет нарисован
 * следующий эелемент. Определяет ориентацию разметки.
 * 	Выравнивание определяет как будут выравнены 
 * элементы меньшие чем самый высокий(если выравнивание
 * по горизонтали) или самый широкий(если выравнивание
 * по вертикали).
 * 	Флаг resized показывает был ли изменен размер
 * после прошлого сброса флага.
 *
 */

class Layout: public Widget
{
public:
	enum Orientation
	{
		horizontal, vertical
	};

	enum Alignement
	{
		right, up, left, down, center
	};

	/*
	 * Конструктор, по умолчанию ориентация горизонтальная,
	 * элементов нет и отступы равны нулю.
	 */
	Layout(
		Orientation orientation = horizontal,
		std::vector<Widget*> const &elements = {},
		sf::Vector2f const &borders = {0.0f, 0.0f}
	);
	/*
	 * Деструктор. Уничтожает все элементы.
	 */
	virtual ~Layout();

	/*
	 * Обновляет каждый элемент, если их размер меняется,
	 * вызывается функция updateSize().
	 */
	virtual void update(double time) override;
	/*
	 * Вызывается при клике по виджету. Проверяет, был ли это клик по
	 * какомо-ту из элементов. Если был, то вызывает
	 * функцию onClick() у соответствующего элемента.
	 */
	virtual void onClick(
		sf::Mouse::Button button,
		sf::Vector2f const &koor
	) override;

	/*
	 * Рисует каждый элемент в соответствии с разметкой.
	 */
	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;


	/*
	 * Возвращает размер.
	 */
	virtual sf::Vector2f getSize() const override;
	/*
	 * Изменился ли размер? Возвращает флаг resized.
	 */
	virtual bool isResized() const override;
	/*
	 * Сбрасывает флаг resized.
	 */
	virtual void resetResized() override;
	
	/*
	 * Обновляет позиции элементов по размеру предыдущих,
	 * по размеру отступа и по ориентации. Устанавливает 
	 * флаг resized.
	 */
	void updateSize();
	/*
	 * Добавляет новый элемент массив элементов.
	 */
	void add(Widget *widget);
	/*
	 * Вставляет элемент перед заданым, если такого элемента нет
	 * вставляет в конец.
	 */
	void insertBefore(Widget const *before, Widget *toinsert);
	/*
	 * Удаляет указанный элемент из массива, уничтожает.
	 */
	void remove(Widget const *widget);
	/*
	 * Удаляет все элементы из массива, все уничтожает.
	 */
	void removeAll();
	/*
	 * Удаляет указанный элемент из массива, не уничтожает.
	 */
	void release(Widget const *widget);
	/*
	 * Удаляет все элементы из массива, никого не уничтожает.
	 */
	void releaseAll();

	/*
	 * Возвращает все элементы.
	 */
	std::vector<Widget*> const &getElements() const;

	/*
	 * Возвращает отступы.
	 */
	sf::Vector2f const &getBorders() const;
	/*
	 * Устанавливает новые отступы, вызывает функцию
	 * updateSize().
	 */
	void setBorders(sf::Vector2f const &newborders);

	/*
	 * Возвращает ориентацию.
	 */
	Orientation getOrientation() const;
	/*
	 * Устанавливает ориентацию, вызывает функцию
	 * updateSize().
	 */
	void setOrientation(Orientation neworientation);

	/*
	 * Возвращает выравнивание.
	 */
	Alignement getAlignement() const;
	/*
	 * Устанавливает выравнивание, вызывает функцию updateSize().
	 */
	void setAlignement(Alignement newalignement);

private:
	Orientation _orientation;
	std::vector<Widget*> _elements;
	sf::Vector2f _borders;
	Alignement _alignement = center;

	bool _isresized = false;

	sf::Vector2f _size = {0.0f, 0.0f};

};



}



#endif
