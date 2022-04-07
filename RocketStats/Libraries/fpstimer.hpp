#ifndef INCLUDE_FPSTIMER_HPP_
#define INCLUDE_FPSTIMER_HPP_

#include <ctime>

class FPSTimer
{
private:
	bool _wait;
	double _fps;
	double _tick;
	unsigned int _frames;
	timespec _beg, _end;

public:
	FPSTimer(unsigned int fps, bool wait_tick = false)
	{
		_fps = fps;
		_tick = (1. / fps);
		_wait = wait_tick;
		_frames = 0;
		reset();
	}

	double elapsed()
	{
		return (_end.tv_sec - _beg.tv_sec + (_end.tv_nsec - _beg.tv_nsec) / 1000000000.);
	}

	unsigned int frames(bool set = false)
	{
		if (set)
			_frames = int(elapsed() / _tick);

		return _frames;
	}

	unsigned int tick()
	{
		if (_frames > 0)
			_beg = _end;

#ifdef CLOCK_REALTIME
		(void)clock_gettime(CLOCK_REALTIME, &_end);
#else
		(void)timespec_get(&_end, TIME_UTC);
#endif

		if (_wait)
		{
			_beg = _end;
			_wait = false;
		}

		return frames(true);
	}

	void reset()
	{
#ifdef CLOCK_REALTIME
		(void)clock_gettime(CLOCK_REALTIME, &_end);
#else
		(void)timespec_get(&_end, TIME_UTC);
#endif

		_beg = _end;
		_frames = 0;
	}
};

#endif