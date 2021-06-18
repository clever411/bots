#ifndef CLEVER_PARALLEL_WORK_HPP
#define CLEVER_PARALLEL_WORK_HPP





namespace clever
{





template<int THREAD_N>
class ParallelWork
{
public:
	static constexpr int const THREAD_COUNT = THREAD_N;



	// the work
	std::function<void(int)> fun; // int — number of thread



	// methods
	ParallelWork()
	{
		for(int i = 0; i < THREAD_COUNT; ++i)
			threads[i] = std::thread(
				&ParallelWork::thread_function, this, i
			);
		return;
	}

	~ParallelWork()
	{
		exit = true;
		{
			std::lock_guard<std::mutex> guard(begmut);
			beg = true;
		}

		begcondvar.notify_all();
		for(int i = 0; i < THREAD_COUNT; ++i)
			threads[i].join();
		return;
	}



	inline void work()
	{
		operator();
		return;
	}

	void operator()()
	{
		{
			std::lock_guard<std::mutex> guard(begmut);
			beg = true;
		}
		begcondvar.notify_all();


		// wait for thread reach end
		{
			std::unique_lock<std::mutex> guard(onendmut);
			onendcondvar.wait( guard, [&]() { return onend == THREAD_COUNT; } );
		}
		onbeg = 0;
		beg = false;
		{
			std::lock_guard<std::mutex> guard(endmut);
			end = true;
		}
		endcondvar.notify_all();


		// wait for thread reach beg
		{
			std::unique_lock<std::mutex> guard(onbegmut);
			onbegcondvar.wait( guard, [&]() { return onbeg == THREAD_COUNT; } );
		}
		onend = 0;
		end = false;

		return;
	}
	
	
	
private:
	void thread_function(int thnum)
	{
	again:
		// I am here (on beg)
		{
			std::lock_guard<std::mutex> guard(onbegmut);
			++onbeg;
		}
		onbegcondvar.notify_one();

		// wait for beg
		{
			std::unique_lock<std::mutex> guard(begmut);
			begcondvar.wait( guard, [&]() { return beg; } );
		}


		// work
		if(exit)
			return;
		fun(thnum);


		// I am here (on end)
		{
			std::lock_guard<std::mutex> guard(onendmut);
			++onend;
		}
		onendcondvar.notify_one();

		// wait for end
		{
			std::unique_lock<std::mutex> guard(endmut);
			endcondvar.wait( guard, [&]() { return end; } );
		}


		goto again;
	}



	std::thread threads[THREAD_COUNT];
	std::condition_variable
		begcondvar, endcondvar,
		onbegcondvar, onendcondvar;
	std::mutex begmut, endmut, onbegmut, onendmut;
	bool exit = false;
	bool beg = false, end = false;
	int onbeg = 0, onend = 0;


	
};





}





#endif
