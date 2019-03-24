#ifndef CLEVER_POINT_HPP
#define CLEVER_POINT_HPP

#include <cmath>
#include <utility>

#include <clever/IostreamFunction.hpp>





namespace clever
{





template<typename T>
struct Point
{
	// types
	typedef T value_type;
	




	// data-members
	value_type x, y;
	
	
	
	
	
	// create
	Point() {}
	Point(value_type x, value_type y): x(x), y(y) {}
	
	template<typename U>
	Point(std::pair<U, U> const &p): x(p.first), y(p.second) {}

	template<class P>
	Point(P const &p): x(p.x), y(p.y) {}

	template<class P>
	Point &operator=(P const &p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	
	
	
	
	
	// conversion
	template<class P>
	inline operator P() const;

	template<typename U>
	inline operator std::pair<U, U>() const;

	template<class P>
	inline P to() const;

	template<typename U = value_type>
	inline std::pair<U, U> topair() const;



	// geometry
	inline double hypot() const;

	template<typename P>
	inline double dis(P const &p) const;



	// print
	template<class Ostream>
	Ostream &print( Ostream &os ) const;
};










// in implement operators:
//   +, -, *, /
//   +=, -=, *=, /=
// functions:
//   makep(C<T>) -> Point<T>
//   operator<<(Ostream, Point<T>)
#include "Point_implement.hpp"
	
	
	
	
	
typedef Point<char> PointC;
typedef Point<int> PointI;
typedef Point<unsigned> PointU;
typedef Point<float> PointF;
typedef Point<double> PointD;





}





#endif
