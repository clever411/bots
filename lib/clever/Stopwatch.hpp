#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP





namespace clever
{



/*
 * Использование происходит так:
 * чтобы начать отсчет, необходимо вызвать функцию start.
 * чтобы получить промежуток времени, для начала необходимо 
 * вызвать функцию stop(), и только потом, можно будет вызывать
 * duration(). Либо можно, не вызывая stop, вызвать update, после
 * этого можно будет использовать duration, но если после stop
 * необходимо вызывать start, то после update — нет.
 */

template<typename Clock>
class Stopwatch
{
public:
	typedef Clock clock_type;
	typedef typename Clock::time_point time_point_type;
	typedef typename Clock::duration duration_type;

	Stopwatch &start()
	{
		starttime_ = clock_type::now();
		return *this;
	}
	Stopwatch &stop()
	{
		duration_ += clock_type::now()-starttime_;
		return *this;
	}
	Stopwatch &update()
	{
		time_point_type now = clock_type::now();
		duration_ += now - starttime_;
		starttime_ = now;
		return *this;
	}
	Stopwatch &reset()
	{
		duration_ = duration_type::zero();
		return *this;
	}

	duration_type const &duration() const
	{
		return duration_;
	}

private:
	time_point_type starttime_ = clock_type::now();
	duration_type duration_ = duration_type::zero();


};




}





#endif
