#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <clever/HexagonField.hpp>





inline clever::PointI map(clever::PointI p, int k)
{
	p.y = p.y/k;
	p.x = p.x/(2*k)*2 + p.y%2;
	return p;
}

template<typename T, typename U>
inline void init_mapping(
	clever::HexagonField<T> const &origin,
	clever::HexagonField<U> &mapping,
	int k
)
{
	mapping.init(
		origin.w / k + ( origin.w % k ? 1 : 0 ),
		origin.h / k + ( origin.h % k ? 1 : 0 )
	);
	return;
}

template<typename T, typename U>
inline void set_mapping_density(
	clever::HexagonField<T> const &origin,
	clever::HexagonField<U> &mapping,
	int k
)
{
	for(auto b = mapping.begin(), e = mapping.end(); b != e; ++b)
		b->density = 0;
	for(auto b = origin.begin(), e = origin.end(); b != e; ++b)
		++mapping.at( map( origin.getxy(b), k ) ).density;
	return;
}


template<typename IteratorType, typename ValueType>
inline void summate(IteratorType b, IteratorType e, ValueType &val)
{
	while(b != e)
	{
		val += *b;
		++b;
	}
	return;
}





#endif
