#ifndef CLEVER_SFML_HELP_FUNCTION_HPP
#define CLEVER_SFML_HELP_FUNCTION_HPP

#include <cmath>

#include <SFML/Graphics.hpp>





namespace clever
{





// conversion 
template<typename T, typename U>
inline sf::Vector2<T> conversion(sf::Vector2<U> const &vec)
{
	return sf::Vector2<T>(T(vec.x), T(vec.y));
}

constexpr static double const PI = 3.141592653589;
inline double togradus(double angle)
{
	return 180.0f*angle/PI;
}

inline double toradian(double angle)
{
	return angle*PI/180.0f;
}



// angle
inline double angle(double x1, double y1, double x2, double y2)
{
	return std::acos(
		(x1*x2 + y1*y2) /
		(std::hypot(x1, y1) * std::hypot(x2, y2))
	);
}

template<typename T, typename U>
inline double angle(sf::Vector2<T> const &first, sf::Vector2<U> const &second)
{
	return angle(first.x, first.y, second.x, second.y);
}





}





// i/o for vector2
template<class Ostream, typename T>
inline Ostream &operator<<(
	Ostream &os, sf::Vector2<T> const &vec
)
{
	return os << "(" << vec.x << ", " << vec.y << ")";
}

template<class Istream, typename T>
inline Istream &operator>>(
	Istream &is, sf::Vector2<T> &vec
)
{
	return is >> vec.x >> vec.y;
}



// i/o for rect
template<class Ostream, typename T>
inline Ostream &operator<<(Ostream &os, sf::Rect<T> const &rect)
{
	return os << "(" << rect.left << ", " << rect.top <<
		")&(" << rect.width << ", " << rect.height << ")";
}

template<class Istream, typename T>
inline Istream &operator>>(Istream &is, sf::Rect<T> &rect)
{
	return is >> rect.left >> rect.top >> rect.width >> rect.height;
}





// arithmetic operators
	// vector2 and vector2 
template<typename T, typename U>
inline sf::Vector2<decltype(T()+U())> operator+(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x+rhs.x, lhs.y+rhs.y};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()-U())> operator-(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x-rhs.x, lhs.y-rhs.y};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()*U())> operator*(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x*rhs.x, lhs.y*rhs.y};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()/U())> operator/(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x/rhs.x, lhs.y/rhs.y};
}



	// vector and number
template<typename T, typename U>
inline sf::Vector2<decltype(T()/U())> operator*(
	sf::Vector2<T> const &lhs,
	U const &number
)
{
	return {lhs.x*number, lhs.y*number};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()/U())> operator*(
	U const &number,
	sf::Vector2<T> const &lhs
)
{
	return {lhs.x*number, lhs.y*number};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()/U())> operator/(
	sf::Vector2<T> const &lhs,
	U const &number
)
{
	return {lhs.x/number, lhs.y/number};
}

template<typename T, typename U>
inline sf::Vector2<decltype(T()/U())> operator/(
	U const &number,
	sf::Vector2<T> const &lhs
)
{
	return {lhs.x/number, lhs.y/number};
}





#endif
