#ifndef CLEVER_FIELD_HPP
#define CLEVER_FIELD_HPP

#include <cstring>
#include <utility>

#include <clever/IostreamFunction.hpp>
#include <clever/Point.hpp>





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
	inline Field &init(int width, int height);
	inline Field &free();



	// clear & zeroize
	inline Field &clear();
	inline Field &clear(value_type const &value);

	inline Field &clearline(int line);
	inline Field &clearline(
		value_type const &value, int line
	);

	inline Field &clearlines(
		int bline, int nline
	);
	inline Field &clearlines(
		value_type const &value,
		int bline, int nline
	);

	inline Field &zeroize();
	inline Field &zeroize(int line);
	inline Field &zeroize(int bline, int nline);





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
	inline void get(int i, int &x, int &y) const;
	inline void get(value_type const *p, int &x, int &y) const;
	inline int get(int x, int y) const;



	inline Point<float> point(int x, int y, double a) const;





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



		// operator at
	inline value_type const *operator[](int n) const;
	inline value_type *operator[](int n);





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





	template<class Ostream>
	Ostream &print(
		Ostream &os,
		std::string const &elterm = "\t",
		std::string const &lnterm = "\n"
	) const;
	
	
	
	
	
};	





#include "Field_implement.hpp"





}





template<class Ostream, typename ValueType>
Ostream &operator<<(Ostream &os, clever::Field<ValueType> const &toprint)
{
	toprint.print(os);
	return os;
}





#endif
