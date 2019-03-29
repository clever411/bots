#ifndef CLEVER_TYPE_HPP
#define CLEVER_TYPE_HPP





namespace clever
{





template<typename T> struct Type
{
	typedef T value;
};



template<bool Cond, typename T, typename U>
struct IF
{
	typedef T value_type;
};

template<typename T, typename U>
struct IF<false, T, U>
{
	typedef U value_type;
};





}





#endif
