// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef SECOND_ALGORITHM_H
#define SECOND_ALGORITHM_H

#include "Algorithm.h"

namespace aal {
	/**
	 * Class representing Second used algorithm.
	 * Based on Greedy algorithm.
	 *
	 * @author Mikolaj Markiewicz
	 */
	class SecondAlgorithm: public Algorithm {
		public:
			/**
			 * C-tor
			 *
			 * @param classrooms Vector of classrooms
			 * @param orders Vector of orders
			 */
			SecondAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * D-tor
			 */
			virtual ~SecondAlgorithm();

			/**
			 * Run Second Algorithm
			 *
			 * @return Result of algorithm execution
			 */
			Result run();

			/**
			 * Get complexity of algorithm calculation for given problem size
			 *
			 * @param problem_size Size of problem
			 * @return Algorithm complexity as number
			 */
			double getTn(const unsigned int problem_size);
	};
}

#endif
