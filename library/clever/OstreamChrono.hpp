#ifndef CLEVER_OSTREAM_CHRONO_HPP
#define CLEVER_OSTREAM_CHRONO_HPP

#include <chrono>





template<typename Ostream, typename T, intmax_t Num, intmax_t Den>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<Num, Den>> const &dur
)
{
	return os << dur.count() << " of " << Num << "/" << Den;
}



// nanoseconds
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<1, 1000000000>> const &dur
)
{
	return os << dur.count() << " of nanoseconds";
}


// microseconds
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<1, 1000000>> const &dur
)
{
	return os << dur.count() << " of microseconds";
}


// milliseconds
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<1, 1000>> const &dur
)
{
	return os << dur.count() << " of milliseconds";
}


// seconds
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<1>> const &dur
)
{
	return os << dur.count() << " of seconds";
}


// minutes
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<60>> const &dur
)
{
	return os << dur.count() << " of minutes";
}


// hours
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<3600>> const &dur
)
{
	return os << dur.count() << " of hours";
}


// days
template<typename Ostream, typename T>
Ostream &operator<<(
	Ostream &os,
	std::chrono::duration<T, std::ratio<86400>> const &dur
)
{
	return os << dur.count() << " of days";
}





#endif
