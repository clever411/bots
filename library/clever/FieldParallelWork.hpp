#ifndef CLEVER_FIELD_PARALLEL_WORK_HPP
#define CLEVER_FIELD_PARALLEL_WORK_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include <clever/Gate.hpp>
#include <clever/ParallelWork.hpp>





namespace clever
{




	
// Пользоваться следующим образом:
// 1. Создать экземпляр (указав кол-во потоков и реализацию для
//    квадратного поля и шестиугольного)
// 2. Установить размеры с помощью метода set(int, int)
// 3. Установить update-функцию 
// 4. Можно вызывать work или operator() — это одно и то же 
//
template<int THREAD_N, class Implement>
class FieldParallelWork
{
public:
	static constexpr int const THREAD_COUNT = THREAD_N;
	typedef Implement implement;



	// open data-members
	std::function<void(int, int)> update;


	FieldParallelWork()
	{
		auto athis = this;
		auto afun = &FieldParallelWork::thread_function;
		worker.fun = [=](int thnum) { (athis->*afun)(thnum); };
		gate.traffic = THREAD_COUNT;
		return;
	}


	void set(int w, int h)
	{
		for(int i = 0; i < 2*THREAD_COUNT; ++i)
		{
			stripes[i] = implement::gen_stripe(
				w, h, THREAD_COUNT, i 
			);
		}
		return;
	}

	inline void work()
	{
		operator();
		return;
	}

	void operator()()
	{
		gate.reset();
		worker();
		return;
	}
	
	
	
private:
	void thread_function(int thnum)
	{
		int x, y;


		// first stripe
		implement::first(x, y, stripes[2*thnum]);
		do
			update(x, y);
		while( implement::next(x, y, stripes[2*thnum]) );


		gate();


		// second stripe
		implement::first(x, y, stripes[2*thnum+1]);
		do
			update(x, y);
		while( implement::next(x, y, stripes[2*thnum+1]) );


		return;
	}



	ParallelWork<THREAD_COUNT> worker;

	typename implement::Stripe stripes[2*THREAD_COUNT];
	Gate gate;

};





struct _SquareFieldParallelWorkImplement
{
	struct Stripe
	{
		int y = -1, w = -1, h = -1;
	};
	


	inline static Stripe gen_stripe(int w, int h, int n, int i)
	{
		int const residue = h % (2*n);
		return { 
			h/(2*n)*i +
				std::min( (i+1)/2, residue ) +
				std::max( 0, std::min(i/2, residue-n) ), // y
			w, // w
			h/(2*n) + ( ( i%2 ? i/2 <
			    residue - n :
			    i/2 < residue ) ? 1 : 0
			) // h
		};
	}

	inline static void first(int &x, int &y, Stripe const &s)
	{
		y = s.y;
		x = 0;
		return;
	}

	inline static bool next(int &x, int &y, Stripe const &s)
	{
		++x;
		if(x < s.w)
			return true;

		++y;
		x = 0;
		if(y < s.y+s.h)
			return true;
		return false;
	}



};



struct _HexagonFieldParallelWorkImplement
{
	struct Stripe
	{
		int y = -1, w = -1, h = -1;
	};



	inline static Stripe gen_stripe(int w, int h, int n, int i)
	{
		int const residue = h % (2*n);
		return { 
			h/(2*n)*i +
				std::min( (i+1)/2, residue ) +
				std::max( 0, std::min(i/2, residue-n) ), // y
			w, // w
			h/(2*n) + ( ( i%2 ? i/2 <
			    residue - n :
			    i/2 < residue ) ? 1 : 0
			) // h
		};
	}

	inline static void first(int &x, int &y, Stripe const &s)
	{
		y = s.y;
		x = y%2;
		return;
	}

	inline static bool next(int &x, int &y, Stripe const &s)
	{
		x += 2;
		if(x/2 < s.w)
			return true;
		++y;
		x = y%2;
		if(y < s.y+s.h)
			return true;
		return false;
	}



};





// typedefs
template<int N>
using SquareFieldParallelWork = FieldParallelWork<N, _SquareFieldParallelWorkImplement>;

template<int N>
using HexagonFieldParallelWork = FieldParallelWork<N, _HexagonFieldParallelWorkImplement>;
	
	
	
	
	
}





#endif
