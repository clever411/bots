// init, free
template<typename ValueType>
inline HexagonalField<ValueType> &
HexagonalField<ValueType>::init()
{
	d = new value_type[w*h];
	return *this;
}

template<typename ValueType>
inline HexagonalField<ValueType> &
HexagonalField<ValueType>::init(
	int width, int height
)
{
	w = width; h = height;
	d = new value_type[w*h];
	return *this;
}

template<typename ValueType>
inline HexagonalField<ValueType> &
HexagonalField<ValueType>::free()
{
	delete[] d;
	return *this;
}





// clear, zeroize
template<typename ValueType>
inline HexagonalField<ValueType> &HexagonalField<ValueType>::clear()
{
	clear(value_type());
	return *this;
}


template<typename ValueType>
inline HexagonalField<ValueType> &HexagonalField<ValueType>::clear(
	value_type const &val
)
{
	for(value_type *b = d, *e = d+w*h; b != e; ++b)
		*b = val;
	return *this;
}



template<typename ValueType>
inline HexagonalField<ValueType> &HexagonalField<ValueType>::zeroize()
{
	memset(d, 0, sizeof(value_type)*w*h);
	return *this;
}







// check vlaid
	// simple
template<typename ValueType>
inline bool HexagonalField<ValueType>::isValid(
	int x, int y
) const
{
	return
		x >= 0 && x/2 < w &&
		y >= 0 && y < h &&
		x%2 == y%2;
}


template<typename ValueType> template<class Point>
inline bool HexagonalField<ValueType>::isValid(
	Point const &p
) const
{
	return
		p.x >= 0 && p.x/2 < w &&
		p.y >= 0 && p.y < h &&
		p.x%2 == p.y%2;
}





	// for near
template<typename ValueType>
inline bool HexagonalField<ValueType>::isValid(
	int x, int y, int dir
) const
{
	return isValid(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}


template<typename ValueType>
template<class Point>
inline bool HexagonalField<ValueType>::isValid(
	Point const &p, int dir
) const
{
	return isValid(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}





// correct
template<typename ValueType>
inline void HexagonalField<ValueType>::correct(
	int &x, int &y
) const
{
	x = x < 0 ?
		2*w-1 - (-x-1)%(2*w) :
		x % (2*w);
	y = y < 0 ?
		h-1 - (-y-1)%h :
		y % h;
	return;
}

template<typename ValueType> template<class Point>
inline void HexagonalField<ValueType>::correct(
	Point &p
) const
{
	correct(p.x, p.y);
}





// get 
template<typename ValueType>
inline void HexagonalField<ValueType>::getxy(
	int i, int &x, int &y
) const
{
	y = i/w;
	x = i%w*2 + (y%2 ? 1 : 0);
	return;
}

template<typename ValueType>
inline PointI HexagonalField<ValueType>::getxy(
	int i
) const
{
	return {
		i%w*2 + (i/w%2 ? 1 : 0),
		i/w
	};
}


template<typename ValueType>
inline void HexagonalField<ValueType>::getxy(
	typename HexagonalField<ValueType>::value_type const *p,
	int &x, int &y
) const
{
	y = (p-d)/w;
	x = (p-d)%w*2 + (y%2 ? 1 : 0);
	return;
}

template<typename ValueType>
inline PointI HexagonalField<ValueType>::getxy(
	value_type const *p
) const
{
	return {
		(p-d)%w*2 + ((p-d)/w%2 ? 1 : 0),
		(p-d)/w
	};
}


template<typename ValueType>
inline int HexagonalField<ValueType>::geti(
	int x, int y
) const
{
	return x/2 + y*w;
}

template<typename ValueType> template<class Point>
inline int HexagonalField<ValueType>::geti(
	Point const &p
) const
{
	return p.x/2 + p.y*w;
}




// origin
template<typename ValueType>
inline PointF HexagonalField<ValueType>::origin(
	int x, int y, float a
) const
{
	return PointF{ 1.5f*a*x, 0.866025f*a*y };
}

template<typename ValueType>
inline PointF HexagonalField<ValueType>::origin(
	PointI const &p, float a
) const
{
	return PointF{ 1.5f*a*p.x, 0.866025f*a*p.y };
}

template<typename ValueType>
inline PointF HexagonalField<ValueType>::origin(
	typename HexagonalField<ValueType>::value_type const *p, float a
) const
{
	int x, y;
	getxy(p, x, y);
	return origin(x, y, a);
}







// at
	// simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::at(
	int x, int y
)
{
	return d[ geti(x, y) ];
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::at(
	int x, int y
) const
{
	return d[ geti(x, y) ];
}



	// for point
template<typename ValueType> template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::at(
	Point const &p
) const
{
	return d[ geti(p.x, p.y) ];
}

template<typename ValueType> template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::at(
	Point const &p
)
{
	return d[ geti(p.x, p.y) ];
}





	// tape at simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::att(
	int x, int y
)
{
	correct(x, y);
	return at(x, y);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::att(
	int x, int y
) const
{
	correct(x, y);
	return at(x, y);
}



	// tape at for point
template<typename ValueType> template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::att(
	Point const &p
) const
{
	return att(p.x, p.y);
}

template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::att(
	Point const &p
)
{
	return att(p.x, p.y);
}





	// near at simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::near(
	int x, int y, int dir
)
{
	return at( x+OFFSET[dir][0], y+OFFSET[dir][1] );
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::near(
	int x, int y, int dir
) const
{
	return at( x+OFFSET[dir][0], y+OFFSET[dir][1] );
}



	// near at for point
template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::near(
	Point const &p, int dir
)
{
	return at( p.x+OFFSET[dir][0], p.y+OFFSET[dir][1] );
}

template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::near(
	Point const &p, int dir
) const
{
	return at( p.x+OFFSET[dir][0], p.y+OFFSET[dir][1] );
}

	



	// near tape at simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::neart(
	int x, int y, int dir
)
{
	return att(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::neart(
	int x, int y, int dir
) const
{
	return att(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}



	// near at for point
template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::neart(
	Point const &p, int dir
)
{
	return att(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}

template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::neart(
	Point const &p, int dir
) const
{
	return att(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}







// iterators
	// simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type *
HexagonalField<ValueType>::begin()
{
	return d;
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type *
HexagonalField<ValueType>::end()
{
	return d + w*h;
}



template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const *
HexagonalField<ValueType>::begin() const
{
	return d;
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const *
HexagonalField<ValueType>::end() const
{
	return d + w*h;
}



	// for line
template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type *
HexagonalField<ValueType>::begin(
	int line
)
{
	return d + line*w;
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type *
HexagonalField<ValueType>::end(
	int line
)
{
	return d + (line+1)*w;
}



template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const *
HexagonalField<ValueType>::begin(
	int line
) const
{
	return d + line*w;
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const *
HexagonalField<ValueType>::end(
	int line
) const
{
	return d + (line+1)*w;
}





	// class-iterator
		// simple
template<typename ValueType>
inline typename HexagonalField<ValueType>::iterator_type
HexagonalField<ValueType>::iterator(
	int left, int top,
	int width, int height
)
{
	return iterator_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::iterator_type const &
HexagonalField<ValueType>::iterend() const
{
	return iterator_type::enditer();
}


		// simple const
template<typename ValueType>
inline typename HexagonalField<ValueType>::const_iterator_type
HexagonalField<ValueType>::citerator(
	int left, int top,
	int width, int height
) const
{
	return const_iterator_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::const_iterator_type const &
HexagonalField<ValueType>::citerend() const
{
	return const_iterator_type::enditer();
}



		// tape
template<typename ValueType>
inline typename HexagonalField<ValueType>::iterator_tape_type
HexagonalField<ValueType>::iteratort(
	int left, int top,
	int width, int height
)
{
	return iterator_tape_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::iterator_tape_type const &
HexagonalField<ValueType>::iterendt() const
{
	return iterator_tape_type::enditer();
}


		// tape const
template<typename ValueType>
inline typename HexagonalField<ValueType>::const_iterator_tape_type
HexagonalField<ValueType>::citeratort(
	int left, int top,
	int width, int height
) const
{
	return const_iterator_tape_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::const_iterator_tape_type const &
HexagonalField<ValueType>::citerendt() const
{
	return const_iterator_tape_type::enditerc();
}





// print
template<typename ValueType>
template<class Ostream>
Ostream &HexagonalField<ValueType>::print( Ostream &os ) const
{
	for(int y = 0; y < h; ++y)
	{
		if(y%2)
			os << "   ";
		for(int x = y%2; x < w*2; x += 2)
		{
			clever::print(os, at(x, y)) << "     ";
		}
		os << "\n\n";
	}
	return os;
}







// iterator-class
// copy
template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::Iterator(
	Iterator<C, TM> const &tocp
):
	left(tocp.left), top(tocp.top),
	width(tocp.width), height(tocp.height),
	fw(tocp.fw), fh(tocp.fh),
	x(tocp.x), y(tocp.y),
	d(tocp.d), fd(tocp.fd) {}

template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode> &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator=(
	Iterator<C, TM> const &rhs
)
{
	left = rhs.left;
	top = rhs.top;
	width = rhs.width;
	height = rhs.height;
	fw = rhs.fw;
	fh = rhs.fh;
	x = rhs.x;
	y = rhs.y;
	d = rhs.d;
	fd = rhs.fd;
	return *this;
}





// move
template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode> &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator++()
{
	plusplus(TapeMode());
	return *this;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator++(int)
{
	auto athis = *this;
	operator++();
	return athis;
}



template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode> &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator--()
{
	minusminus(TapeMode());
	return *this;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator--(int)
{
	auto cp = *this;
	operator--();
	return cp;
}





// at
template<typename ValueType>
template<class IsConst, class TapeMode>
typename HexagonalField<ValueType>::template Iterator<IsConst, TapeMode>::value_type &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator*() const
{
	return *d;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
typename HexagonalField<ValueType>::template Iterator<IsConst, TapeMode>::value_type &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator->() const
{
	return *d;
}



template<typename ValueType>
template<class IsConst, class TapeMode>
inline typename HexagonalField<ValueType>::template Iterator<IsConst, TapeMode>::value_type *
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::base() const
{
	return d;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline PointI HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::point() const
{
	return { x, y };
}





// get info
	// compare
template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
bool HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator==(
	 Iterator<C, TM> const &rhs
) const
{
	if(d)
		return rhs.d ?
			x == rhs.x && y == rhs.y :
			isend();
	return rhs.d ? 
		rhs.isend() :
		true;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
inline bool HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::operator!=(
	Iterator<C, TM> const &rhs
) const
{
	return !operator==(rhs);
}



	// end
template<typename ValueType>
template<class IsConst, class TapeMode>
inline bool HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::isend() const
{
	return y == top+height;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline HexagonalField<ValueType>::Iterator<IsConst, TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::iterend() const
{
	auto it = *this;
	it.y = top+height;
	it.x = left - (top%2 ? 1 : 0) + (it.y%2 ? 1 : 0);
	return it;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline HexagonalField<ValueType>::Iterator<IsConst, TapeMode> const &
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::iterendc() const
{
	static Iterator const singleton = create_iterend();
	return singleton;
}







// private
	// static
template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>
HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::create_iterend()
{
	Iterator iter;
	iter.d = nullptr;
	return iter;
}





	// constructor
template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::template Iterator<IsConst, TapeMode>::Iterator(): d(nullptr) {}

template<typename ValueType>
template<class IsConst, class TapeMode>
HexagonalField<ValueType>::template Iterator<IsConst, TapeMode>::Iterator(
	field_type &field,
	int left, int top,
	int width, int height
):
	left(left), top(top),
	width( width < 0 ? field.w-left : width ),
	height( height < 0 ? field.h-top : height ),
	fw(field.w), fh(field.h),
	x(left), y(top),
	d(&field.att(left, top)), fd(field.d) {}



	// move
template<typename ValueType>
template<class IsConst, class TapeMode>
inline void HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::plusplus(Simple)
{
	x += 2;
	if( x/2 == left/2+width )
	{
		++y;
		x = left/2*2 + y%2;
		d += fw-width+1;
	}
	else
		++d;

	return;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline void HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::plusplus(TapeAt)
{
	x += 2;
	if( (x - (y%2 ? 1 : 0))/2 == (left - (top%2 ? 1 : 0))/2 + width )
	{
		++y;
		x = left - (top%2 ? 1 : 0) + (y%2 ? 1 : 0);
	}
	d = fd + ( x < 0 ?
		2*fw-1 - (-x-1)%(2*fw) :
		x % (2*fw)
	)/2 + tape(y, fh)*fw;


	return;
}



template<typename ValueType>
template<class IsConst, class TapeMode>
inline void HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::minusminus(Simple)
{
	x -= 2;
	if( (x - y%2)/2 == left/2-1 )
	{
		--y;
		x = left - top%2 + y%2 + (width - 1)*2;
	}
	d = fd + x/2 + y*fw;

	return;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline void HexagonalField<ValueType>::Iterator<IsConst, TapeMode>::minusminus(TapeAt)
{
	x -= 2;
	if( (x - (y%2 ? 1 : 0))/2 == (left - (top%2 ? 1 : 0))/2 - 1 )
	{
		--y;
		x = left - (top%2 ? 1 : 0) + (y%2 ? 1 : 0) + (width - 1)*2;
	}
	d = fd + ( x < 0 ?
		2*fw-1 - (-x-1)%(2*fw) :
		x % (2*fw)
	)/2 + tape(y, fh)*fw;

	return;
}







// end
