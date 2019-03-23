#ifndef CLEVER_STATUS_BAR_HPP
#define CLEVER_STATUS_BAR_HPP

#include <string>

#include "Widget.hpp"
#include <clever/ChangingObject.hpp>



namespace clever
{



/*
 *	Экземпляр класса состоит из сущностей:
 *	- текст;
 * 	- статус;
 * 	- пространство;
 * 	- выравнивание;
 * 	- флаг resized.
 * 	Текст - это указатель на объект класса sf::Text,
 * используется для рисования текста, его можно установить
 * с помощью соответствующей функции.
 *	Статус - константный указатель на объект класса
 * clever::ChangingObject<std::string>. Используется
 * для поддержки актуальности отоброжаемой информации.
 * Если вы измените статус(во вне) с помощью соответствующих
 * функций класса clever::ChangingObject<std::string> то
 * при вызове функции update() установится новый текст.
 *     	Пространство - то что будет возвращать функция
 * getSize().
 * 	Выравнивание - выравнивание строки используя ее
 * фактический размер в пространстве.
 * 	Флаг resized - информирует был ли изменен размер
 * после прошлого сброса флага.
 * 
 *	У экземпляра этого класса есть несколько возможных
 * состояний:
 *     	- определенный.
 *	- неопределенный;
 * 	Экземпляр называется определенным, если определены
 * текст и статус(указатели на них != nullptr). Иначе
 * экземпляр называется неопределенным.
 */

class StatusBar: public Widget
{
public:
	enum Aligning
	{
		left,	/* Выравнивать по левому краю	|text  |*/
		center,	/* Выравнивать по центру      	| text |*/
		right	/* Выравнивать по правому краю	|  text|*/
	};

	/*
	 * Создает экземпляр, по умолчанию текст и статус неопределены.
	 * Если вызвать функцию draw в неопределенном состоянии
	 * ничего нарисовано не будет.
	 */
	StatusBar(
		sf::Text *text = nullptr,
		clever::ChangingObject<std::string> const *status = nullptr,
		sf::Vector2f const &scpace = {0.0f, 0.0f}
	);

	/*
	 * Деструктор. Уничтожает экземпляр. Удаляет текст, но не
	 * удляет статус.
	 */
	virtual ~StatusBar();
	
	/*
	 * Обновляет экземпляр - проверяет изменился ли статус, 
	 * если изменился то устанавливает новый статус в текст.
	 * Но если экземпляр находится в неопределенном состоянии,
	 * ничего не делается.
	 */
	virtual void update(double time) override;

	/*
	 * Рисует экземпляр. Если экземпляр находится в неопределенном
	 * состоянии, ничего не делается.
	 */
	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;

	
	/*
	 * Возвращает размер(пространство).
	 * Тоже самое что и getSpace().
	 */
	virtual sf::Vector2f getSize() const override;
	/*
	 * Был ли изменен размер? Возвращает флаг resized.
	 */
	virtual bool isResized() const override;
	/*
	 * Сбрасывает флаг, говорящий об изменении размера.
	 */
	virtual void resetResized() override;

	/*
	 * Автоматически устанавливает пространство.
	 * Пространство = размер текста на коэффециент.
	 * Устанавливает флаг isresized.
	 */
	void updateSpace(float kx = 1.0f, float ky = 1.0f);
	void updateSpace(sf::Vector2f const &k);

	/*
	 * Возвращает текст.
	 */
	sf::Text const *getText() const;
	/*
	 * Устанавливает текст.
	 */
	void setText(sf::Text *newtext);

	/*
	 * Возвращает статус.
	 */
	clever::ChangingObject<std::string> const *getStatus() const;
	/*
	 * Устанавливает статус.
	 */
	void setStatus(
		clever::ChangingObject<std::string> const *newstatus
	);

	/*
	 * Возвращает пространство.
	 */
	sf::Vector2f getSpace() const;
	/*
	 * Устанавливает пространство. После вызова функции
	 * устанавливается флаг isresized.
	 */
	void setSpace(sf::Vector2f const &newspace);

	/*
	 * Возвращает выравнивание.
	 */
	Aligning getAligning() const;
	/*
	 * Устанавливает выравнивание.
	 */
	void setAligning(Aligning newalign);

private:
	void _adjustPosition();

	sf::Text *_text;
	clever::ChangingObject<std::string> const *_status;

	bool _isresized = false;

	sf::Vector2f _space = {0.0f, 0.0f};
	Aligning _align = center;
	
};



}



#endif
