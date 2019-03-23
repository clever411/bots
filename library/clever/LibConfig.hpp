#ifndef CLEVER_LIB_CONFIG_HPP
#define CLEVER_LIB_CONFIG_HPP

#include <string>

#include <libconfig.h++>







namespace clever
{







// возвращает nullptr если ничего не найдёт
inline libconfig::Setting *lookup(
	libconfig::Setting &set, char const *name 
) noexcept
{
	try
	{
		return &set.lookup( name );
	}
	catch(...) {}
	return nullptr;
}

inline libconfig::Setting *lookup(
	libconfig::Setting &set, std::string const &name 
) noexcept
{
	try
	{
		return &set.lookup( name );
	}
	catch(...) {}
	return nullptr;
}



inline libconfig::Setting const *lookup(
	libconfig::Setting const &set, char const *name 
) noexcept
{
	try
	{
		return &set.lookup( name );
	}
	catch(...) {}
	return nullptr;
}

inline libconfig::Setting const *lookup(
	libconfig::Setting const &set, std::string const &name 
) noexcept
{
	try
	{
		return &set.lookup( name );
	}
	catch(...) {}
	return nullptr;
}





// если не находит, устанавливает значение по умолчанию
template<typename T>
inline void lookup(
	libconfig::Setting const &set, std::string const &name,
	T &value, T const &defvalue
) noexcept
{
	try {
		value = set.lookup(name);
	}
	catch(...) {
		value = defvalue;
	}
	return;
}



template<>
inline void lookup<std::string>(
	libconfig::Setting const &set, std::string const &name,
	std::string &value, std::string const &defvalue
) noexcept
{
	try {
		value = set.lookup(name).c_str();
	}
	catch(...) {
		value = defvalue;
	}
	return;
}





// устанавливает сразу несколько;
// если чего-то нет, не изменяет значение
inline void lookup_many(
	libconfig::Setting const &set,
	char const **names
) {}

template<typename T, typename... Args>
void lookup_many(
	libconfig::Setting const &set,
	char const **names,
	T &val, Args&... args
)
{
	set.lookupValue( *names, val );
	lookup_many( set, names+1, args... );
	return;
}






void tolower( std::string &s ) noexcept;
char hextodec(char ch) noexcept;
int hextodec( std::string const &s ) noexcept;
uint32_t tocolor( std::string s ) noexcept;







}








#endif
