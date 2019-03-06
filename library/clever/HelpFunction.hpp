#ifndef CLEVER_HELP_FUNCTION_HPP
#define CLEVER_HELP_FUNCTION_HPP

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





}





#endif
