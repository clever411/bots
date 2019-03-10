// init
template<typename ValueType>
inline Field<ValueType> &
Field<ValueType>::init()
{
	d = new value_type[w*h];
	return *this;
}

template<typename ValueType>
inline Field<ValueType> &
Field<ValueType>::init(int neww, int newh)
{
	w = neww; h = newh;
	d = new value_type[w*h];
	return *this;
}

template<typename ValueType>
inline Field<ValueType> &
Field<ValueType>::free()
{
	delete[] d;
	return *this;
}







// check vlaid
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


template<typename ValueType>
inline bool Field<ValueType>::isValid(
	std::pair<int, int> const &p
) const
{
	return p.first >= 0 && p.first < w && p.second >= 0 && p.second < h;
}





// correct
template<typename ValueType>
inline void Field<ValueType>::correct(int &x, int &y) const
{
	x = x < 0 ?
		( x%w == 0 ? 0 : x - (x/w - 1)*w ) :
		x % w;
	y = y < 0 ?
		( y%h == 0 ? 0 : y - (y/h - 1)*h ) :
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

template<typename ValueType>
inline void Field<ValueType>::correct(std::pair<int, int> &p) const
{
	p.first = p.first < 0 ?
		( p.first%w == 0 ? 0 : p.first - (p.first/w - 1)*w ) :
		p.first % w;
	p.second = p.second < 0 ?
		( p.second%h == 0 ? 0 : p.second - (p.second/h - 1)*h ) :
		p.second % h;
	return;
}


template<typename ValueType>
void inline Field<ValueType>::get(
	typename Field<ValueType>::value_type const *el, int &x, int &y
) const
{
	int const dis = el-d;
	x = dis%w; y = dis/w;
	return;
}

template<typename ValueType> template<class Point>
void inline Field<ValueType>::get(
	typename Field<ValueType>::value_type const *el, Point &p
) const
{
	int const dis = el-d;
	p.x = dis%w; p.y = dis/w;
	return;
}

template<typename ValueType>
inline void Field<ValueType>::get(
	typename Field<ValueType>::value_type const *el,
	std::pair<int, int> &p
) const
{
	int const dis = el-d;
	p.first = dis%w; p.second = dis/w;
	return;
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



	// for std::pair
template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::at(
	std::pair<int, int> const &p
) const
{
	return d[p.second*w+p.first];
}


template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::at(std::pair<int, int> const &p)
{
	return d[p.second*w+p.first];
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



	// tape at for std::pair
template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::tapeAt(std::pair<int, int> const &p)
{
	return tapeAt(p.first, p.second);
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::tapeAt(std::pair<int, int> const &p) const
{
	return tapeAt(p.first, p.second);
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







// clear & zeroize
template<typename ValueType>
inline void
Field<ValueType>::clear()
{
	clear(value_type());
	return;
}


template<typename ValueType>
inline void
Field<ValueType>::clear(value_type const &value)
{
	for(value_type *b = d, *e = d+w*h; b != e; ++b)
		*b = value;
	return;
}



template<typename ValueType>
inline void
Field<ValueType>::zeroize()
{
	memset(d, 0, sizeof(value_type)*w*h);
	return;
}


template<typename ValueType>
inline void
Field<ValueType>::zeroize(int line)
{
	memset(d+line*w, 0, sizeof(value_type)*w);
	return;
}


template<typename ValueType>
inline void
Field<ValueType>::zeroize(int bline, int n)
{
	memset(d+bline*w, 0, sizeof(value_type)*w*n);
	return;
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



template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::cbegin() const
{
	return d;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::cend() const
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



template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::cbegin(int line)
{
	return d + line*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::cend(int line)
{
	return d + (line+1)*w;
}






// end
