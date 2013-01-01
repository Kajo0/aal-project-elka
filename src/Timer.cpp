// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include "Timer.h"

namespace aal {

	Timer::Timer(): time_(0) {
		//std::cout<<"Timer()\n;";
	}

	Timer::Timer(const Timer &other): time_(0) {
	}

	Timer& Timer::operator=(const Timer &other) {
		return *this;
	}

	Timer::~Timer() {
		//std::cout<<"~Timer()\n;";
	}

	Timer& Timer::getInstance() {
		static Timer instance_ = Timer();
		return instance_;
	}

	void Timer::start() {
		time_ = clock();
	}

	void Timer::stop() {
		time_ = clock() - time_;
	}

	double Timer::end() {
		return (((double) time_) / CLOCKS_PER_SEC) * 1000;
	}

}
