#ifndef CLEVER_FIELD_HPP
#define CLEVER_FIELD_HPP

#include <algorithm>
#include <cstring>
#include <utility>





namespace clever
{



template<typename ValueType>
struct Field
{
	// types
	typedef ValueType value_type;
	
	
	
	
	
	// static const members
	static constexpr int const OFFSET_COUNT = 8;
	static constexpr int const OFFSET[OFFSET_COUNT][2] = {
		{ -1, -1 }, { 0, -1 }, { 1, -1 }, //  Directions:
		                       { 1, 0  }, //  0  1  2
		                       { 1, 1  }, //  7  *  3
		            { 0, 1  },            //  6  5  4
		{ -1, 1  },                       // 
		{ -1, 0  },                       // 
	};
	




	// data-members
	int w = 0, h = 0;
	value_type *d = nullptr;
	
	
	
	
	
	// init, free
	inline Field &init();
	inline Field &init(int neww, int newh);
	inline Field &free();





	// check vlaid
		// simple
	inline bool isValid(int x, int y) const;

	template<class Point>
	inline bool isValid(Point const &p) const;
	
	inline bool isValid(std::pair<int, int> const &p) const;



		// for near
	inline bool isValid(int x, int y, int dir) const;

	template<class Point>
	inline bool isValid(Point const &p, int dir) const;

	inline bool isValid(std::pair<int, int> const &p, int dir) const;





	// correct
	inline void correct(int &x, int &y) const;

	template<class Point>
	inline void correct(Point &p) const;
	
	inline void correct(std::pair<int, int> &p) const;





	// get 
	inline void get(value_type const *p, int &x, int &y) const;





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


		// for std::pair
	inline value_type const &at(
		std::pair<int, int> const &p
	) const;
	
	inline value_type &at(std::pair<int, int> const &p);



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


		// tape at for std::pair
	inline value_type &tapeAt(
		std::pair<int, int> const &p
	);
	
	inline value_type const &tapeAt(
		std::pair<int, int> const &p
	) const;



		// operator at
	inline value_type const *operator[](int n) const;
	inline value_type *operator[](int n);



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

		// near at for std::pair
	inline value_type &near(
		std::pair<int, int> const &p, int dir
	);

	inline value_type const &near(
		std::pair<int, int> const &p, int dir
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

		// near at for std::pair
	inline value_type &nearTape(
		std::pair<int, int> const &p, int dir
	);

	inline value_type const &nearTape(
		std::pair<int, int> const &p, int dir
	) const;




	// clear & zeroize
	inline void clear();
	inline void clear(value_type const &value);

	inline void zeroize();
	inline void zeroize(int line);
	inline void zeroize(int bline, int n);





	// iterators
		// simple
	inline value_type *begin();
	inline value_type *end();

	inline value_type const *cbegin() const;
	inline value_type const *cend() const;



		// for line
	inline value_type *begin(int line);
	inline value_type *end(int line);
	
	inline value_type const *cbegin(int line);
	inline value_type const *cend(int line);





};	



#include "Field_implement.hpp"



}





#endif
