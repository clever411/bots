#ifndef CLEVER_HEXAGONAL_FIELD_HPP
#define CLEVER_HEXAGONAL_FIELD_HPP

#include <cstring>
#include <utility>

#include <clever/Point.hpp>





namespace clever
{





template<typename T>
struct HexagonalField
{
	// types
	typedef T value_type;
	
	
	
	
	
	// static constants
	static constexpr int const OFFSET_COUNT = 6;
	static constexpr int const OFFSET[OFFSET_COUNT][2] = {
		{ 0, -2 }, { 1, -1 }, { 1, 1 },   // начиная сверху,
		{ 0, 2 },  { -1, 1 }, { -1, -1 }  // по часовой стрелке
	};
	
	
	
	
	
	// data-members
	value_type *d;
	int w, h;
	
	
	
	
	
	// init, free
	inline HexagonalField &init();
	inline HexagonalField &init(int width, int height);
	inline HexagonalField &free();



	// clear, zeroize
	inline HexagonalField &clear();
	inline HexagonalField &clear(value_type const &val);
	inline HexagonalField &zeroize();




	
	// check vlaid
		// simple
	inline bool isValid(int x, int y) const;

	template<class Point>
	inline bool isValid(Point const &p) const;



		// for near
	inline bool isValid(int x, int y, int dir) const;

	template<class Point>
	inline bool isValid(Point const &p, int dir) const;



	// correct
	inline void correct(int &x, int &y) const;

	template<class Point>
	inline void correct(Point &p) const;



	// get 
	inline void getxy(int i, int &x, int &y) const;
	inline PointI getxy(int i) const;

	inline void getxy(value_type const *p, int &x, int &y) const;
	inline PointI getxy(value_type const *p) const;

	inline int geti(int x, int y) const;

	template<class Point>
	inline int geti(Point const &p) const;



	// geometry origin
	inline PointF origin(int x, int y, float a) const;
	inline PointF origin(PointI const &p, float a) const;
	inline PointF origin(value_type const *p, float a) const;





	// at
		// simple
	inline value_type &at(int x, int y);
	inline value_type const &at(int x, int y) const;


		// for point
	template<class Point>
	inline value_type const &at(
		Point const &p
	) const;

	template<class Point>
	inline value_type &at(
		Point const &p
	);



		// tape at simple
	inline value_type &tapeAt(int x, int y);
	inline value_type const &tapeAt(int x, int y) const;


		// tape at for point
	template<class Point>
	inline value_type const &tapeAt(
		Point const &p
	) const;

	template<class Point>
	inline value_type &tapeAt(
		Point const &p
	);



		// near at simple
	inline value_type &near(int x, int y, int dir);
	inline value_type const &near(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &near(Point const &p, int dir);

	template<class Point>
	inline value_type const &near(
		Point const &p, int dir
	) const;

		

		// near tape at simple
	inline value_type &nearTape(int x, int y, int dir);
	inline value_type const &nearTape(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &nearTape(Point const &p, int dir);

	template<class Point>
	inline value_type const &nearTape(
		Point const &p, int dir
	) const;





	// iterators
		// simple
	inline value_type *begin();
	inline value_type *end();

	inline value_type const *begin() const;
	inline value_type const *end() const;



		// for line
	inline value_type *begin(int line);
	inline value_type *end(int line);
	
	inline value_type const *begin(int line) const;
	inline value_type const *end(int line) const;





};





#include "HexagonalField_implement.hpp"





}





#endif
