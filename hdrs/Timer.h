// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef TIMER_H
#define TIMER_H

#include <ctime>

namespace aal {
	/**
	 * Singleton class for capture time of calculation
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Timer {
			/** Captured clock tick */
			clock_t time_;

			/**
			 * Private C-tor
			 */
			Timer();

			/**
			 * Private Copying C-tor
			 */
			Timer(const Timer &other);

			/**
			 * Private Assignment operator
			 */
			Timer& operator=(const Timer &other);

		public:
			/**
			 * D-tor
			 */
			virtual ~Timer();

			/**
			 * Get Singleton instance of timer
			 * Construct if doesn't exist
			 *
			 * @return Timer instance
			 */
			static Timer& getInstance();

			/**
			 * Capture clock tick
			 */
			void start();

			/**
			 * Store time difference
			 */
			void stop();

			/**
			 * Get captured time elapsed between start and stop
			 *
			 * @return Captured time in milliseconds
			 */
			double end();
	};
}

#endif
