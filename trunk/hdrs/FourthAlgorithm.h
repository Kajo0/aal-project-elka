// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef FOURTH_ALGORITHM_H
#define FOURTH_ALGORITHM_H

#include <list>
#include "Algorithm.h"

namespace aal {
	/**
	 * Class representing Fourth used algorithm.
	 * Based on Divide and Conquer algorithm i think, uses other algorithms
	 * to cope with smaller problems.
	 *
	 * @author Mikolaj Markiewicz
	 */
	class FourthAlgorithm: public Algorithm {
			/** Vector of lists of orders */
			std::vector<std::list<Order*> > vectorList_;

		public:
			/**
			 * C-tor
			 *
			 * @param classrooms Vector of classrooms
			 * @param orders Vector of orders
			 */
			FourthAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders);
			virtual ~FourthAlgorithm();

			/**
			 * Invoke parent init and 'clear' vectorList
			 *
			 * @param classrooms Another classrooms vector
			 * @param orders Another orders vector
			 */
			void init(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * Run Fourth Algorithm
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
