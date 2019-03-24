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
	y = y < 0 ?
		h-1 - (-y-1)%h :
		y % h;
	x /= 2;
	x = x < 0 ?
		w-1 - (-x-1)%w :
		x % w;
	x = x*2 + (y%2 ? 1 : 0);
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
HexagonalField<ValueType>::tapeAt(
	int x, int y
)
{
	correct(x, y);
	return at(x, y);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::tapeAt(
	int x, int y
) const
{
	correct(x, y);
	return at(x, y);
}



	// tape at for point
template<typename ValueType> template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::tapeAt(
	Point const &p
) const
{
	return tapeAt(p.x, p.y);
}

template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::tapeAt(
	Point const &p
)
{
	return tapeAt(p.x, p.y);
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
HexagonalField<ValueType>::nearTape(
	int x, int y, int dir
)
{
	return tapeAt(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::nearTape(
	int x, int y, int dir
) const
{
	return tapeAt(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}



	// near at for point
template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type &
HexagonalField<ValueType>::nearTape(
	Point const &p, int dir
)
{
	return tapeAt(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}

template<typename ValueType>
template<class Point>
inline typename HexagonalField<ValueType>::value_type const &
HexagonalField<ValueType>::nearTape(
	Point const &p, int dir
) const
{
	return tapeAt(
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







// end
