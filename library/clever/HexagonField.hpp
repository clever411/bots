#ifndef CLEVER_HEXAGON_FIELD_HPP
#define CLEVER_HEXAGON_FIELD_HPP

#include <cstring>
#include <iterator>
#include <type_traits>
#include <utility>

#include <clever/HelpFunction.hpp>
#include <clever/Point.hpp>
#include <clever/Type.hpp>





namespace clever
{





template<typename T>
struct HexagonField
{
	// types
	typedef T value_type;



		// iterator-class
private:
	struct Simple {};
	struct Const {};
	struct TapeAt {};

	template<class IsConst, class TapeMode>
	class Iterator: public std::iterator<
		std::bidirectional_iterator_tag,
		typename IF<
			std::is_same<IsConst, Const>::value,
			HexagonField::value_type const,
			HexagonField::value_type
		>::value_type
	>
	{
	public:
		// types
		typedef typename Iterator::value_type value_type;

		typedef typename IF<
			std::is_same<IsConst, Const>::value,
			HexagonField const, HexagonField
		>::value_type field_type;





		// copy
		template<class C, class TM>
		Iterator( Iterator<C, TM> const &tocp );

		template<class C, class TM>
		Iterator &operator=(Iterator<C, TM> const &rhs);
		
		

		// move
		Iterator &operator++();
		inline Iterator operator++(int);

		Iterator &operator--();
		inline Iterator operator--(int);

		Iterator &incy();
		Iterator &incy(int n);

		Iterator &reducey();
		Iterator &reducey(int n);



		// at
		inline value_type &operator*() const;
		inline value_type *operator->() const;

		inline value_type *base() const;
		inline PointI point() const;



		// get info
		template<class C, class TM>
		bool operator==(Iterator<C, TM> const &rhs) const;

		template<class C, class TM>
		inline bool operator!=(Iterator<C, TM> const &rhs) const;

		inline bool isedge() const;
		inline bool isend() const;

		// создаёт новый итератор, который можно потом изменять:
		// отправить, например, в функцию make_reverse_iterator;
		// из этого итератора может выйти. Но создаётся новый! В
		// цикле вызывать эту функцию для проверки дошёл ли до 
		// конца итератор - нельзя, используй для этого либо isend,
		// либо iterendc
		Iterator iterend() const;
		inline Iterator const &iterendc() const;
		


	private:
		friend class HexagonField;

		static Iterator create_iterend();



		// methods
		Iterator();
		Iterator(
			field_type &field,
			int left = 0, int top = 0,
			int width = -1, int height = -1
		);

		inline void plusplus(Simple);
		inline void plusplus(TapeAt);

		inline void minusminus(Simple);
		inline void minusminus(TapeAt);



		// data-members
		int top, left, width, height, fw, fh;
		int x, y;
		mutable value_type *d;
		value_type *fd;




	};



public:
		// other
	typedef Iterator<Simple, Simple> iterator_type;
	typedef Iterator<Const, Simple> const_iterator_type;
	typedef Iterator<Simple, TapeAt> iterator_tape_type;
	typedef Iterator<Const, TapeAt> const_iterator_tape_type; 
	
	
	
	
	
	
	
	
	
	
	// static constants
	static constexpr int const OFFSET_COUNT = 6;
	static constexpr int const OFFSET[OFFSET_COUNT][2] = {
		{ 0, -2 }, { 1, -1 }, { 1, 1 },   // начиная сверху,
		{ 0, 2 },  { -1, 1 }, { -1, -1 }  // по часовой стрелке
	};
	
	
	
	
	
	// data-members
	int w, h;
	value_type *d;
	
	
	
	
	
	// init, free
	inline HexagonField &init();
	inline HexagonField &init(int width, int height);
	inline HexagonField &free();



	// clear, zeroize
	inline HexagonField &clear();
	inline HexagonField &clear(value_type const &val);
	inline HexagonField &zeroize();




	
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
	inline value_type &att(int x, int y);
	inline value_type const &att(int x, int y) const;


		// tape at for point
	template<class Point>
	inline value_type const &att(
		Point const &p
	) const;

	template<class Point>
	inline value_type &att(
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
	inline value_type &neart(int x, int y, int dir);
	inline value_type const &neart(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &neart(Point const &p, int dir);

	template<class Point>
	inline value_type const &neart(
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



		// class-iterator 
			// simple
	inline iterator_type iterator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_type const &iterend() const;

			// simple const
	inline const_iterator_type citerator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_type const &citerend() const;


			// tape
	inline iterator_tape_type iteratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_tape_type const &iterendt() const;

			// tape const
	inline const_iterator_tape_type citeratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_tape_type const &citerendt() const;





	template<class Ostream>
	Ostream &print( Ostream &os ) const;





};





#include "HexagonField_implement.hpp"





}





template<class Ostream, typename ValueType>
Ostream &operator<<(Ostream &os, clever::HexagonField<ValueType> const &toprint)
{
	toprint.print(os);
	return os;
}







#endif
