// init, free
template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::init()
{
	d = new value_type[w*h];
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::init(
	int neww, int newh
)
{
	w = neww; h = newh;
	d = new value_type[w*h];
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::free()
{
	delete[] d;
	return *this;
}





// clear & zeroize
template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::clear()
{
	clear(value_type());
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::clear(
	value_type const &value
)
{
	for(value_type *b = d, *e = d+w*h; b != e; ++b)
		*b = value;
	return *this;
}



template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize()
{
	memset(d, 0, sizeof(value_type)*w*h);
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize(int line)
{
	memset(d+line*w, 0, sizeof(value_type)*w);
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize(
	int bline, int nline
)
{
	memset(d+bline*w, 0, sizeof(value_type)*w*nline);
	return *this;
}







// check vlaid
	// simple
template<typename ValueType>
inline bool Field<ValueType>::isValid(int x, int y) const
{
	return x >= 0 && x < w && y >= 0 && y < h;
}


template<typename ValueType> template<class Point>
inline bool Field<ValueType>::isValid(
	Point const &p
) const
{
	return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h;
}



	// for near
template<typename ValueType>
inline bool Field<ValueType>::isValid(
	int x, int y, int dir
) const
{
	return isValid(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType> template<class Point>
inline bool Field<ValueType>::isValid(
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
inline void Field<ValueType>::correct(int &x, int &y) const
{
	x = x < 0 ?
		w-1 - (-x-1)%w :
		x % w;
	y = y < 0 ?
		h-1 - (-y-1)%h :
		y % h;
	return;
}

template<typename ValueType> template<class Point>
inline void Field<ValueType>::correct(Point &p) const
{
	p.x = p.x < 0 ?
		( int(p.x)%w == 0 ? 0 : int(p.x) - (int(p.x)/w - 1)*w ) :
		int(p.x) % w;
	p.y = p.y < 0 ?
		( int(p.y)%h == 0 ? 0 : int(p.y) - (int(p.y)/h - 1)*h ) :
		int(p.y) % h;
	return;
}





// get
template<typename ValueType>
inline void Field<ValueType>::get(
	int i, int &x, int &y
) const
{
	x = i%w;
	y = i/w;
	return;
}

template<typename ValueType>
inline void Field<ValueType>::get(
	typename Field<ValueType>::value_type const *p,
	int &x, int &y
) const
{
	x = (p-d)%w;
	y = (p-d)/w;
	return;
}

template<typename ValueType>
inline int Field<ValueType>::get(
	int x, int y
) const
{
	return x + y*w;
}





template<typename ValueType>
inline Point<float> Field<ValueType>::point(
	int x, int y, double a
) const
{
	return { a*x, a*y };
}







// at
	// simple
template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::at(int x, int y)
{
	return d[y*w+x];
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::at(int x, int y) const
{
	return d[y*w+x];
}



	// for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::at(Point const &p) const
{
	return d[p.y*w+p.x];
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type &
Field<ValueType>::at(
	Point const &p
)
{
	return d[p.y*w+p.x];
}





	// tape at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::tapeAt(int x, int y)
{
	correct(x, y);
	return d[y*w+x];
}

	
template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::tapeAt(int x, int y) const
{
	correct(x, y);
	return d[y*w+x];
}



	// tape at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::tapeAt(
	Point const &p
) const
{
	return tapeAt(p.x, p.y);
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type &
Field<ValueType>::tapeAt(
	Point const &p
)
{
	return tapeAt(p.x, p.y);
}



	// near at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type
&Field<ValueType>::near(
	int x, int y, int dir
)
{
	return at( x + OFFSET[dir][0], y + OFFSET[dir][1] );
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::near(
	int x, int y, int dir
) const
{
	return at( x + OFFSET[dir][0], y + OFFSET[dir][1] );
}



	// near at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type
&Field<ValueType>::near(
	Point const &p, int dir
)
{
	return at( p.x + OFFSET[dir][0], p.y + OFFSET[dir][1] );
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::near(
	Point const &p, int dir
) const
{
	return at( p.x + OFFSET[dir][0], p.y + OFFSET[dir][1] );
}

	



	// near tape at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type
&Field<ValueType>::nearTape(
	int x, int y, int dir
)
{
	return tapeAt(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::nearTape(
	int x, int y, int dir
) const
{
	return tapeAt(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}



	// near at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type
&Field<ValueType>::nearTape(
	Point const &p, int dir
)
{
	return tapeAt(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}

template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::nearTape(
	Point const &p, int dir
) const
{
	return tapeAt(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}





	// operator at
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::operator[](int n) const
{
	return d + n*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::operator[](int n) 
{
	return d + n*w;
}







// iterators
	// simple
template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::begin()
{
	return d;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::end()
{
	return d + w*h;
}



	// simple const
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::begin() const
{
	return d;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::end() const
{
	return d + w*h;
}





	// for line
template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::begin(int line)
{
	return d + line*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::end(int line)
{
	return d + (line+1)*w;
}



	// for line const
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::begin(int line) const
{
	return d + line*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::end(int line) const
{
	return d + (line+1)*w;
}







template<typename ValueType> template<class Ostream>
Ostream &Field<ValueType>::print(
	Ostream &os,
	std::string const &elterm,
	std::string const &lnterm
) const
{
	for(int y = 0; y < h; ++y)
	{
		for(int x = 0; x < w; ++x)
		{
			clever::print(os, at(x, y)) << elterm;
		}
		os << lnterm;
	}
	return os;
}







// end
