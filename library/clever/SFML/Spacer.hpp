#ifndef CLEVER_SPACER_HPP
#define CLEVER_SPACER_HPP

#include "Widget.hpp"





namespace clever
{


/*
 * 	Этот класс предназначен, чтобы просто занимать пространство.
 * У этого класса есть только размер и флаг resized.
 */

class Spacer: public Widget
{
public:
	/*
	 * Конструктор. По умолчанию размер равен {0.0f, 0.0f}.
	 */
	Spacer(sf::Vector2f const &size = {0.0f, 0.0f});
	/*
	 * Деструктор. Виртуальный, ничего не делает.
	 */
	virtual ~Spacer();


	/*
	 * Функция рисования, ничего не делает.
	 */
	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;

	/*
	 * Функция обновления, ничего не делает.
	 */
	virtual void update(double time) override;

	/*
	 * Возвращает установленный размер.
	 */
	virtual sf::Vector2f getSize() const override;
	/*
	 * Возвращает флаг resized. Он говорит о том, был ли изменен размер
	 * после прошлого сброса флага.
	 */
	virtual bool isResized() const override;
	/*
	 * Сбрасывает флаг resized.
	 */
	virtual void resetResized() override;

	/*
	 * Устанавливает размер, если размер отличается от предыдущего
	 * устанавливает флаг resized.
	 */
	void setSize(sf::Vector2f const &newsize);

private:
	sf::Vector2f _size;
	bool _isresized = false;

};



}





#endif
