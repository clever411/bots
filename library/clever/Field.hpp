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
	




	// data-members
	int w = 0, h = 0;
	value_type *d = nullptr;
	
	
	
	
	
	// init, free
	inline Field &init();
	inline Field &init(int neww, int newh);
	inline Field &free();





	// check vlaid
	inline bool isValid(int x, int y) const;

	template<class Point>
	inline bool isValid(Point const &p) const;
	
	inline bool isValid(std::pair<int, int> const &p) const;





	// correct & get
	inline void correct(int &x, int &y) const;

	template<class Point>
	inline void correct(Point &p) const;
	
	inline void correct(std::pair<int, int> &p) const;


	void inline get(value_type const *el, int &x, int &y) const;

	template<class Point>
	void inline get(value_type const *el, Point &p) const;

	inline void get(value_type const *el, std::pair<int, int> &p) const;





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
