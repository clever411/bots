#ifndef CLEVER_MATRIX_HPP
#define CLEVER_MATRIX_HPP





/*
 * 	Класс. Представляет собой двумерную матрицу. Имеет
 * дополнительные функции для удобства. Сначала указывается
 * тип хранимый в матрице, затем количество строк и последним
 * количество столбцов. ЗАМЕТЬТЕ! сначала высота, потом ширина,
 * не наооборот. При доступе к матрице через оператор [a][b]
 * также как и при создании матрицы сначала указывается 
 * строка, затем столбец. СНАЧАЛА Y И ТОЛЬКО ПОТОМ X!!!
 * 	Структура является агрегатом. По умолчанию значения
 * неопределены.
 */

namespace clever
{





template<typename T, size_t H, size_t W>
struct Matrix
{
static_assert(W > 0);
static_assert(H > 0);

	
	// types and constants
	typedef T value_type;
	typedef size_t size_type;

	constexpr static size_type const w = W;
	constexpr static size_type const h = H;
	constexpr static size_type const length = w*h;
	



	// data members
	T d[h][w];





	// at
	value_type *operator[](int n)
	{
		return d[n];
	}

	value_type const *operator[](int n) const
	{
		return d[n];
	}



	// iterators
	value_type *begin()
	{
		return (T*)d;
	}

	value_type *end()
	{
		return (T*)d+w*h;
	}


	value_type const *cend() const
	{
		return (T const *)d+w*h;
	}

	value_type const *cbegin() const
	{
		return (T const *)d;
	}



	// line iterators
	value_type *begin(int line)
	{
		return d[line];
	}

	value_type *end(int line)
	{
		return d[line]+w;
	}


	value_type const *cbegin(int line) const
	{
		return d[line];
	}

	value_type const *cend(int line) const
	{
		return d[line]+w;
	}





	// size
	constexpr static size_type size()
	{
		return length;
	}





};





}





#endif // CLEVER_MATRIX_HPP
