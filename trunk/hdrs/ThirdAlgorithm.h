// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef THIRD_ALGORITHM_H
#define THIRD_ALGORITHM_H

#include <list>
#include "Algorithm.h"

namespace aal {
	/**
	 * Class representing Third used algorithm.
	 * It's based on Permutation of order - classroom assignment possibilities
	 * Sth like Brute Force
	 *
	 * @author Mikolaj Markiewicz
	 */
	class ThirdAlgorithm: public Algorithm {
			/** List of results to keep them all during recurse */
			std::list<Result> results_;

		public:
			/**
			 * C-tor
			 *
			 * @param classrooms Vector of classrooms
			 * @param orders Vector of orders
			 */
			ThirdAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * D-tor
			 */
			virtual ~ThirdAlgorithm();

			/**
			 * Invoke parent init and 'clear' vectorList
			 *
			 * @param classrooms Another classrooms vector
			 * @param orders Another orders vector
			 */
			void init(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * Run Third Algorithm
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

		private:
			/**
			 * Do combinations on given parameters
			 *
			 * @param orders Orders to combine
			 * @param ommiter From which order start
			 * @param last_result Result of previous combination
			 * @param classroom_amount_left How many classrooms left
			 */
			void combinations(std::vector<Order*> &orders, int ommiter, Result &last_result, int classroom_amount_left);
	};
}

#endif
