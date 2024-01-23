#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>
namespace sdds {
	class Timer {
	private:
		std::chrono::steady_clock::time_point startTime;
	public:
		void start();
		long long stop();
	};
}
#endif // !SDDS_TIMER_H