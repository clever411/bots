// conversion
template<typename T> template<class P>
inline Point<T>::operator P() const
{
	P p;
	p.x = x;
	p.y = y;
	return p;
}


template<typename T> template<typename U>
inline Point<T>::operator std::pair<U, U>() const
{
	return std::pair<U, U>(x, y);
}


template<typename T> template<class P>
inline P Point<T>::to() const
{
	P p;
	p.x = x;
	p.y = y;
	return p;
}


template<typename T> template<typename U>
inline std::pair<U, U> Point<T>::topair() const
{
	return std::pair<U, U>(x, y);
}





// geometry
template<typename T>
inline double Point<T>::hypot() const
{
	return std::hypot(x, y);
}


template<typename T> template<typename P>
inline double Point<T>::dis(P const &p) const
{
	return std::hypot(p.x-x, p.y-y);
}





// print
template<typename T> template<class Ostream>
inline Ostream &Point<T>::print( Ostream &os ) const
{
	os << "(";
	clever::print(os, x) << ", ";
	clever::print(os, y) << ")";
	return os;
}







// operators
template<typename T, typename U>
inline Point<decltype(T()+U())> operator+(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x+rhs.x, lhs.y+rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()-U())> operator-(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x-rhs.x, lhs.y-rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()*U())> operator*(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x*rhs.x, lhs.y*rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()/U())> operator/(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x/rhs.x, lhs.y/rhs.y};
}





template<typename T, typename U>
inline Point<T> &operator+=(Point<T> &lhs, Point<U> const &rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator-=(Point<T> &lhs, Point<U> const &rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator*=(Point<T> &lhs, Point<U> const &rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator/=(Point<T> &lhs, Point<U> const &rhs)
{
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;
	return lhs;
}







// print
template<class Ostream, typename T>
inline Ostream &operator<<( Ostream &os, Point<T> const &toprint )
{
	return toprint.print(os);
}







// help
template<template<typename> class C, typename T>
inline Point<T> makep(C<T> const &from)
{
	return Point<T>{from.x, from.y};
}







// end
