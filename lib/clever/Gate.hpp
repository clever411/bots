#ifndef CLEVER_GATE_HPP
#define CLEVER_GATE_HPP

#include <condition_variable>
#include <mutex>
#include <thread>





namespace clever
{





struct Gate
{
	int traffic = 1;

	// Можно вызывать только из главного потока, пртиом лишь
	// тогда, когда все остальные потоки миновали эти врата.
	// Советуется вызывать перед запуском этих потоков
	inline void reset()
	{
		is = 0;
		return;
	}

	// Предназначается для вызова дочерними потоками: дочерний
	// поток ожидает, пока все остальные не доберуться до врат,
	// после чего они все вместе продолжают
	inline void operator()()
	{
		std::unique_lock<std::mutex> guard(mut);
		++is;
		condvar.wait( guard, [&]() { return is == traffic; } );
		condvar.notify_all();
		return;
	}


private:

	int is = 0;
	std::condition_variable condvar;
	std::mutex mut;


};





}





#endif
