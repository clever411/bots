#ifndef CLEVER_GRADIENT_HPP
#define CLEVER_GRADIENT_HPP

#include <vector>

#include <SFML/Graphics.hpp>





namespace clever
{




	
// Использовать следующим образом:
// 1. Создать экземпляр
// 2. Установить colors — цвета от каких к каким должен
//    идти градиент
// 3. Вызывать operator(float) для получения цвета;
//    k должно быть число от 0.0 до 1.0 (при большем
//    значении будет выбираться последний в colors цвет):
//    цвет будет равномерно переходить от одного к другому
//    при увеличении k
// Используйте статическую функцию gen(char f, char s), чтобы
// сгенерировать градиент особым образом: f-цвет (должен принимать
// значения 'r', 'g' или 'b') имеет наибольшее влияние, затем — s,
// и наименьшее влияние имеет неуказанный оттенок из rgb
struct Gradient
{
	std::vector<sf::Color> colors;

	sf::Color operator()(float k) const;
	
	static Gradient const
		DARKLING_RED,
		DARKLING_GREEN,
		DARKLING_BLUE,
		DARKLING_YELLOW,
		DARKLING_MAGENTA,
		DARKLING_CYAN;

	static Gradient gen(int f, int s);
};





}





#endif
