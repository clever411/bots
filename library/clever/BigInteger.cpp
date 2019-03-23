#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>




// structure
constexpr unsigned int const BASE = 10000u;
struct BigInteger
{
	unsigned int size, capacity;
	unsigned short *d;





	// creation&destroy
	// Создает экземпляр с установленной вместимостью
	BigInteger &init( unsigned int cap = 0 )
	{
		capacity = cap;
		size = 0;
		if(capacity)
			d = new unsigned short[capacity];
		else
			d = nullptr;
		return *this;
	}


		// by simple number
	// Создает экземпляр инициализируя обычным числом,
	// добаляя к вместимости addcap
	BigInteger &initbynum(
		unsigned long long num,
		unsigned int addcap = 0
	)
	{
		// capacity
		unsigned int count = 1;
		// unsigned long long temp = num;
		for( unsigned long long temp = num/BASE; temp; temp /= BASE )
			++count;
		capacity = count+addcap;
		d = new unsigned short[ capacity ];

		// readnum
		read(num);

		return *this;
	}

	// Читает обычное число, вместимость должно позволять
	BigInteger &read( unsigned long long num )
	{
		unsigned long long temp;
		unsigned int pos = 0;
		do
		{
			temp = num / BASE;
			d[ pos ] = num - temp*BASE;
			num = temp;
			++pos;
		}
		while(num);
		size = pos;

		return *this;
	}


		// by string
	// Создает экземпляр с помощью строки. Добовляет addcap
	BigInteger &init(char const *num, unsigned int n, unsigned int addcap = 0)
	{
		while( *num == '0' && n != 1 )
		{
			++num;
			--n;
		}

		capacity = n / 4 + 
			( n % 4 == 0 ? 0 : 1 ) + addcap;
		size = 0;
		d = new unsigned short[ capacity ];

		read(num, n);

		return *this;
	}

	// Читает строку, вместимость должно соответствовать
	BigInteger &read(char const *num, unsigned int n)
	{
		while( *num == '0' && n != 1 )
		{
			++num;
			--n;
		}

		auto it = d;
		for( auto b = num+n-1, e = num-1; b > e; --b )
		{
			*it = *b-'0';
			if( --b > e )
			{
				*it += (*b-'0') * 10;
				if( --b > e )
				{
					*it += (*b-'0') * 100;
					if( --b > e )
						*it += (*b-'0') * 1000;
				}
			}
			++it;
		}
		size = it - d;

		return *this;
	}


		// destroy
	inline BigInteger &free()
	{
		delete[] d;
		return *this;
	}





		// other
	inline BigInteger &zeroize()
	{
		memset( d, 0, sizeof *d * capacity );
		return *this;
	}

	BigInteger &reserve( unsigned int cap )
	{
		if(capacity >= cap)
			return *this;

		auto *oldd = d;
		capacity = cap;
		d = new unsigned short[capacity];
		zeroize();
		memcpy( d, oldd, sizeof *d * size );
		delete[] oldd;

		return *this;
	}





	// streams
	template<typename Istream>
	Istream &scan(Istream &is)
	{
		std::string buf;
		is >> buf;
		init(buf.data(), buf.size());
		return is;
	}

	template<typename Ostream>
	Ostream &print( Ostream &os ) const
	{
		if(!size)
			return os;

		auto b = d+size-1, e = d-1;
		os << *b;
		while( --b != e )
		{
			if(*b < 1000)
			{
				os << '0';
				if(*b < 100)
				{
					os << '0';
					if(*b < 10)
					{
						os << '0';
					}
				}
			}
			os << *b;
		}

		return os;
	}



};



template<class Istream>
Istream &operator>>( Istream &is, BigInteger &toscan )
{
	return toscan.scan(is);
}


template<typename Ostream>
Ostream &operator<<( Ostream &os, BigInteger const &toprint )
{
	return toprint.print(os);
}





// можно вызывать addition( a, b, a );
void addition(
	BigInteger const &lhs,
	BigInteger const &rhs,
	BigInteger &target
)
{
	// guarantor lhs.size >= rhs.size
	if(lhs.size < rhs.size)
	{
		addition( rhs, lhs, target );
		return;
	}
	target.reserve( lhs.size+1 );

	
	// process
	unsigned long long temp;
	unsigned int carry = 0;

	for( unsigned int i = 0; i < rhs.size; ++i )
	{
		temp = lhs.d[i] + rhs.d[i] + carry;

		if( temp >= BASE )
		{
			temp -= BASE;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		target.d[i] = temp;
	}

	for( unsigned int i = rhs.size; i < lhs.size; ++i )
	{
		temp = lhs.d[i] + carry;

		if(temp >= BASE)
		{
			temp -= BASE;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		target.d[i] = temp;
	}


	// last carry & size
	if(carry)
	{
		target.d[ lhs.size ] = carry;
		target.size = lhs.size+1;
	}
	else
		target.size = lhs.size;


	return;
}




// можно вызывать substraction( a, b, a );
void substraction(
	BigInteger const &lhs,
	BigInteger const &rhs,
	BigInteger &target
)
{
	target.reserve(lhs.size);

	// process
	long long temp;
	int carry = 0;
	
	for( unsigned int i = 0; i < rhs.size; ++i )
	{
		temp = lhs.d[i] - rhs.d[i] + carry;

		if(temp < 0)
		{
			temp += BASE;
			carry = -1;
		}
		else
		{
			carry = 0;
		}
		target.d[i] = temp;
	}

	for( unsigned int i = rhs.size; i < lhs.size; ++i )
	{
		temp = lhs.d[i] + carry;

		if(temp < 0)
		{
			temp += BASE;
			carry = -1;
		}
		else
		{
			carry = 0;
		}
		target.d[i] = temp;
	}


	// size
	target.size =
		target.d[ lhs.size-1 ] ? lhs.size : lhs.size-1;
	// if(!target.size)
		// target.size = 1;

	return;
}





// нельзя вызывать multiplication( a, b, a );
// Необходимо, чтобы target был обнулен
void multiplication(
	BigInteger const &lhs,
	BigInteger const &rhs,
	BigInteger &target
)
{
	unsigned long long temp;
	unsigned long long carry = 0;

	auto it = target.d;
	for(auto *rb = rhs.d, *re = rhs.d+rhs.size; rb != re; ++rb)
	{
		for(auto *lb = lhs.d, *le = lhs.d+lhs.size; lb != le; ++lb)
		{
			temp = *it + *rb * *lb + carry;
			carry = temp / BASE;
			*it = temp - carry*BASE;
			++it;
		}

		if(carry)
		{
			*it = carry;
			carry = 0;
		}

		it -= lhs.size-1;
	}

	it += lhs.size-1;
	target.size =
		*it ? it-target.d+1 : it-target.d;
	
	return;
}





/*
 * void division(
 *         BigInteger const &lhs,
 *         unsigned short rhs,
 *         BigInteger &target
 * )
 * {
 *         std::vector< unsigned short > result;
 * 
 *         unsigned long long temp = 0;
 *         for(auto *b = lhs.d+lhs.size-1, *e = lhs.d-1; b != e; --b)
 *         {
 *                 temp += *b;
 *                 result.push_back( temp/rhs );
 *                 std::cout << "result.back(): " << result.back() << std::endl;
 * 
 *                 temp = ( *b - rhs*result.back() ) * BASE;
 *         }
 * 
 *         auto
 *                 beg = result.crbegin(),
 *                 end = result.crend();
 *         std::copy(
 *                 beg, end, target.d
 *         );
 *         target.size = result.size();
 * 
 *         return;
 * 
 * }
 */





// end
