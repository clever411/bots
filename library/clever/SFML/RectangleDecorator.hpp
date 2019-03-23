#ifndef CLEVER_RECTNAGLE_DECORATOR_HPP
#define CLEVER_RECTNAGLE_DECORATOR_HPP

#include "Widget.hpp"



namespace clever
{



/*
 * 	Экземпляр состоит из следующих сущностей:
 * 	- потомок(Widget);
 * 	- прямоугольник;
 * 	- отступы(borders);
 * 	- флаг resized.
 * 	Потомок - объект класса Widget. Этот объект
 * декорируется этим классом.
 * 	Прямоугольник - объект класса sf::RectangleShape.
 * Должен быть установлен в ручную, этим контролируется
 * цвет, внешняя линия, текстура и прочее. Размер
 * прямоугольника менять вручную запрещено, он всегда
 * определяется отступами и размером декорируемого
 * объекта.
 * 	Отступы - отступы от декорируемого объекта.
 * 	Флаг resized - информирует был ли изменен 
 * экземпляр с прошлого сброса флага.
 *
 * 	Экземпляр этого класса может находится в
 * нескольких состояниях: 
 * 	- определенныом;
 * 	- неопределенном.
 * 	Экземпляр находится в определенным состоянии,
 * когда указатели на потомка и прямоугольник
 * определены(не равны nullptr). Иначе экземпляр
 * находится в неопределенном состоянии.
 *
 * 	Если вы изменили без ведома экземпляра размер
 * потомка, для корректной работы необходимо, что бы перед
 * рисованием была вызвана фунция updateSize() или 
 * update(double).
 */

class RectangleDecorator: public Widget
{
public:
	/*
	 * Коснтруктор, по умолчанию экземпляр находится в 
	 * неопределенном состоянии.
	 */
	RectangleDecorator(
		Widget *widget = nullptr,
		sf::RectangleShape *rect = nullptr,
		sf::Vector2f const &borders = {0.0f, 0.0f}
	);
	/*
	 * Деструктор. Уничтожает потомка и прямоугольник.
	 */
	virtual ~RectangleDecorator();

	/*
	 * Вызывает функцию обновления у потомка(если определен).
	 * Если при этом изменится размер потомка вызовет
	 * функцию updateSize().
	 */
	virtual void update(double time) override;

	virtual void onClick(
		sf::Mouse::Button button,
		sf::Vector2f const &point
	) override;
		
	/*
	 * Рисует себя и потомка, если находится в неопределеном
	 * состоянии ничего не рисует.
	 */
	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;


	/*
	 * Возвращает размер прямоугольника, если находится в 
	 * неопределенном состоянии возвращает обнуленный вектор.
	 */
	virtual sf::Vector2f getSize() const override;
	/*
	 * Был ли изменен размер? Возвращает флаг resized.
	 */
	virtual bool isResized() const override;
	/*
	 * Сбрасывает флаг изменения размера
	 */
	virtual void resetResized() override;
	/*
	 * Обновляет размер прямоугольника по размеру потомка
	 * и отступам. Всегда вызывайте эту функцию после установки
	 * потомка и отступов. Устанавливает флаг resized.
	 */
	void updateSize();

	/*
	 * Возвращает потомка.
	 */
	Widget *getWidget() const;
	/*
	 * Возвращает потомка, одновременно обнуляя указатель.
	 * Вызывает updateSize().
	 */
	Widget *takeWidget();
	/*
	 * Устанавливает потомка, если есть уже уставновленный - 
	 * уничтожает установленный. Вызывает updateSize().
	 */
	void setWidget(Widget *newobject);

	/*
	 * Возвращает прямоугольник.
	 */
	sf::RectangleShape const *getRectangle() const;
	/*
	 * Устанавливает прямоугольник, если есть уже
	 * установленный - уничтожает. Вызывает updateSize().
	 */
	void setRectangle(sf::RectangleShape *newrect);

	/*
	 * Возвращает отступы.
	 */
	sf::Vector2f const &getBorders() const;
	/*
	 * Устанавливает отступы. Вызывает функцию updateSize().
	 */
	void setBorders(float newhborder, float newvborder);
	void setBorders(sf::Vector2f const &newborders);

private:
	Widget *_widget;
	sf::RectangleShape *_rect;
	sf::Vector2f _borders;

	bool _isresized = false;

};



}



#endif
