#ifndef CLEVER_IOSTREAM_FUNCTION_HPP
#define CLEVER_IOSTREAM_FUNCTION_HPP

#include <array>
#include <list>
#include <tuple>
#include <utility>
#include <vector>





namespace clever
{







// print functions
	// defult
template<class Ostream, typename T>
inline Ostream &print(Ostream &os, T const &t)
{
	os << t;
	return os;
}



	// for pointer
template<class Ostream, typename T>
inline Ostream &print(Ostream &os, T* t)
{
	os << '&' << *t;
	return os;
}



	// for pair
template<class Ostream, typename T, typename U>
inline Ostream &print(
	Ostream &os, std::pair<T, U> const &pair,
	std::string const &term = ", "
)
{
	print(
		print(
			os << "< ", pair.first
		) << term,
		pair.second
	) << " >";
	return os;
}



	// for vector
template<class Ostream, typename T>
Ostream &print(
	Ostream &os, std::vector<T> const &vec,
	std::string const &term = ", "
)
{
	os << "< ";
	if(!vec.empty()) {
		print(os, vec.front());
		for(auto b = vec.begin()+1, e = vec.end(); b != e; ++b) {
			print(os << term, *b);
		}
	}
	os << " >";
	return os;
}



	// for list
template<class Ostream, typename T>
Ostream &print(
	Ostream &os, std::list<T> const &l,
	std::string const &term = ", "
)
{
	os << "[ ";
	if(!l.empty()) {
		print(os, l.front());
		for(auto b = std::next(l.begin()), e = l.end(); b != e; ++b) {
			print(os << term, *b);
		}
	}
	os << " ]";
	return os;
}



	// for array
template<class Ostream, typename T, size_t N>
Ostream &print(
	Ostream &os, std::array<T, N> const &arr,
	std::string const &term = ", "
)
{
	static_assert(N > 0);

	os << "( " << arr[0];
	for(size_t i = 1; i < N; ++i) {
		print(os << term, arr[i]);
	}
	os << " )";
	return os;
}



	// for array
template<class Ostream, typename T, typename SizeType = int>
Ostream &print(
	Ostream &os, T const *arr, SizeType len,
	std::string const &term = ", "
)
{
	if(!len)
		return os << "(  )";
	T const *end = arr+len;
	os << "( " << *arr;
	while(++arr != end)
		os << term << *arr;
	return os << " )";
}



	// for matrix
template<class Ostream, class Matrix>
Ostream &print_matrix(
	Ostream &os,
	Matrix const &m, unsigned int w, unsigned int h,
	std::string const &elterm = "\t",
	std::string const &lineterm = "\n"
)
{
	for(unsigned int i = 0; i < h; ++i) {
		for(unsigned int j = 0; j < w; ++j) {
			print(os, m[i][j]) << elterm;
		}
		os << lineterm;
	}
	return os;
}





	// for tuples
template<class Ostream, int n, int max, typename...Args>
struct PRINT_TUPLE
{
	static Ostream &print(
		Ostream &os, std::tuple<Args...> const &tuple
	)
	{
		os << std::get<n-1>(tuple) << ", ";
		return PRINT_TUPLE<Ostream, n+1, max, Args...>::print(os, tuple);
	}
};



template<class Ostream, int max, typename...Args>
struct PRINT_TUPLE<Ostream, max, max, Args...>
{
	static Ostream &print(
		Ostream &os, std::tuple<Args...> const &tuple
	)
	{
		return os << std::get<max-1>(tuple);
	}
};



template<class Ostream, typename...Args>
Ostream &print(
	Ostream &os, std::tuple<Args...> const &tuple
)
{
	os << "[ ";
	clever::PRINT_TUPLE<
		Ostream, 1, sizeof...(Args), Args...
	>::print(os, tuple);
	os << " ]";
	return os;
}







// snan functions
	// for vector
template<class Istream, typename T>
Istream &scan(
	Istream &is, std::vector<T> &vec
)
{
	T input;
	while(is >> input)
		vec.push_back(input);
	return is;
}



	// for array
template<class Istream, typename T>
Istream &scan(
	Istream &is, T *arr, int size = -1, int *n = nullptr
)
{
	int i = 0;
	for(; i != size && is >> *arr; ++i, ++arr);
	if(n) *n = i;
	return is;
}


template<class Istream, typename T>
Istream &scan(
	Istream &is, T *arr, T *arrend, int *n = nullptr
)
{
	int an = 0;
	while(arr != arrend && is >> *arr)
	{
		++arr;
		++an;
	}
	if(n) *n = an;
	return is;
}







// write/read functions
template<class Ostream>
inline Ostream &writestr( Ostream &os, std::string const &str )
{
	int size = str.size();
	os.write( (char const *)&size, sizeof size );
	os.write( str.c_str(), sizeof(char)*size );
	return os;
}


template<class Istream>
inline Istream &readstr( Istream &is, std::string &str )
{
	int size = 0;
	is.read( (char *)&size, sizeof size );
	str.resize( size );
	is.read( const_cast<char*>(str.data()), sizeof(char)*size );
	return is;
}







}







// operators
	// vector
template<class Ostream, typename T>
inline Ostream &operator<<(Ostream &os, std::vector<T> const &vec)
{
	return clever::print(os, vec);
}


template<class Istream, typename T>
inline Istream &operator>>(Istream &is, std::vector<T> &vec)
{
	return clever::scan(is, vec);
}






	// other
template<class Ostream, typename T>
inline Ostream &operator<<(Ostream &os, std::list<T> const &l)
{
	return clever::print(os, l);
}



template<class Ostream, typename T, typename U>
inline Ostream &operator<<(Ostream &os, std::pair<T, U> const &pair)
{
	return clever::print(os, pair);
}



template<class Ostream, typename T, size_t N>
inline Ostream &operator<<(Ostream &os, std::array<T, N> const &arr)
{
	return clever::print(os, arr);
}



template<class Ostream, typename...Args>
inline Ostream &operator<<(
	Ostream &os, std::tuple<Args...> const &tuple
)
{
	return clever::print(os, tuple);
}







#endif
