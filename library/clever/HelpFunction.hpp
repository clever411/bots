#ifndef CLEVER_HELP_FUNCTION_HPP
#define CLEVER_HELP_FUNCTION_HPP

#include <algorithm>
#include <iterator>
#include <string>





namespace clever
{





inline std::string &cutzero(std::string &s)
{
	auto pos = s.find_last_not_of('0');
	if(pos == s.npos)
		return s;
	return s[pos] == '.' ?
		s.erase(pos+2) :
		s.erase(pos+1);
}

inline std::string cutzero(std::string &&s)
{
	auto pos = s.find_last_not_of('0');
	if(pos == s.npos)
		return s;
	return s[pos] == '.' ?
		s.erase(pos+2) :
		s.erase(pos+1);
}

inline std::string &fills(std::string &s, int n)
{
	if(s.size() >= n)
		return s;
	s.reserve(n);
	std::fill_n( std::back_inserter(s), n-s.size(), ' ' );
	return s;
}

inline std::string fills(std::string &&s, int n)
{
	if(s.size() >= n)
		return s;
	s.reserve(n);
	std::fill_n( std::back_inserter(s), n-s.size(), ' ' );
	return s;
}





inline int tape(int i, int max)
{
	return i < 0 ?
		max-1 - (-i-1)%max :
		i % max;
}





}





#endif
