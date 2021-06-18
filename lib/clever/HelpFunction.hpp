#ifndef CLEVER_HELP_FUNCTION_HPP
#define CLEVER_HELP_FUNCTION_HPP


#include <algorithm>
#include <iterator>
#include <string>
#include <vector>





namespace clever
{





// min, max element
template<typename T>
inline auto maxelement(T const &head)
{
	return head;
}

template<typename T, typename...Args>
inline auto maxelement(T const &head, Args const &...args)
{
	auto nextmax = maxelement(args...);
	return nextmax > head ? nextmax : head;
}

template<typename T>
inline auto minelement(T const &head)
{
	return head;
}

template<typename T, typename...Args>
inline auto minelement(T const &head, Args const &...args)
{
	auto nextmin = minelement(args...);
	return nextmin < head ? nextmin : head;
}





// strings
	// cutzero
inline std::string cutzero(std::string const &s)
{
	auto pos = s.find_last_not_of('0');
	if(pos == s.npos)
		return s;
	return s[pos] == '.' ?
		s.substr( 0, pos+2 ) :
		s.substr( 0, pos+1 );
}

inline void cutzero(std::string *s)
{
	auto pos = s->find_last_not_of('0');
	if(pos == s->npos)
		return;
	(*s)[pos] == '.' ?
		s->erase(pos+2) :
		s->erase(pos+1);
	return;
}



	// cut space
inline void cutspace(std::string *s)
{
	*s = s->substr(
		s->find_first_of(" \t\n"),
		s->size() - s->find_first_not_of(" \t\n") + 1
	);
	return;
}

inline std::string cutspace(std::string const &s)
{
	return s.substr(
		s.find_first_not_of(" \t\n"),
		s.size() - s.find_first_not_of(" \t\n") + 1
	);
}



	// fills
inline void fills(std::string *s, int n)
{
	if((int)s->size() >= n)
		return;
	s->reserve(n);
	std::fill_n( std::back_inserter(*s), n-s->size(), ' ' );
	return;
}

inline std::string fills(std::string const &s, int n)
{
	if((int)s.size() >= n)
		return s;
	std::string cp = s;
	cp.reserve(n);
	std::fill_n( std::back_inserter(cp), n-cp.size(), ' ' );
	return cp;
}

inline std::string fills(std::string &&s, int n)
{
	if((int)s.size() >= n)
		return s;
	s.reserve(n);
	std::fill_n( std::back_inserter(s), n-s.size(), ' ' );
	return s;
}



	// other
void genkeys(
	std::vector<std::string> const &names,
	std::vector<std::string> &keys,
	bool letcase = false
);



	// Взято с: https://habr.com/ru/post/318962
std::string format(const char *fmt, ...);



/*
 * Вычленяет объекты из строки
 *   i — int
 *   l - long
 *   u - unsigned int
 *   f - float
 *   d - double
 *   s,w - std::string
 *   a — кладёт всю оставшуюся строку в std::string
 * тип вычленяемого объекта и их порядок получается из fmt;
 * fmt может выглядеть так: "iifs" — тогда сначала считается
 * int, затем ещё раз int, далее float и в конце std::string.
 * Всё это записывается в dat. Для вычленения используется
 * stringstream::operator>>(...)
 */
bool scan(
	std::string const &enter,
	char const *fmt,
	void **dat
);

inline bool scan(
	std::string const &enter,
	char const *fmt,
	std::vector<void *> dat
)
{
	return scan(enter, fmt, dat.data());
}





// other
inline int tape(int i, int max)
{
	return i < 0 ?
		max-1 - (-i-1)%max :
		i % max;
}





}





#endif
