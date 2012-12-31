// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "Result.h"

namespace aal {
	/**
	 * Base class for used algorithms
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Algorithm {
		protected:
			/** Classrooms given to algorithm */
			std::vector<Classroom*> classrooms_;

			/** Orders given to algorithm */
			std::vector<Order*> orders_;

			/** Result of the algorithm execution */
			Result result_;

		public:
			/**
			 * C-tor
			 *
			 * @param classrooms Vector of classrooms
			 * @param orders Vector of orders
			 */
			Algorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * D-tor
			 */
			virtual ~Algorithm();

			/**
			 * Algorithm re-initialization
			 *
			 * @param classrooms Another classrooms vector
			 * @param orders Another orders vector
			 */
			virtual void init(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * Algorithm execution
			 *
			 * @return Result of algorithm execution
			 */
			virtual Result run() = 0;

			/**
			 * Get complexity of algorithm calculation for given problem size
			 *
			 * @param problem_size Size of problem
			 * @return Algorithm complexity as number
			 */
			virtual double getTn(const unsigned int problem_size) = 0;
	};
}

#endif
