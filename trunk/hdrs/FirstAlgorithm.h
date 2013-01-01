// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef FIRST_ALGORITHM_H
#define FIRST_ALGORITHM_H

#include <list>
#include "Algorithm.h"

namespace aal {
	/*
	 * Class representing First used algorithm.
	 * It's based on Dynamic Programming.
	 *
	 * @author Mikolaj Markiewicz
	 */
	class FirstAlgorithm: public Algorithm {
		public:
			/**
			 * C-tor
			 *
			 * @param classrooms Vector of classrooms
			 * @param orders Vector of orders
			 */
			FirstAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders);

			/**
			 * D-tor
			 */
			virtual ~FirstAlgorithm();

			/**
			 * Run First Algorithm
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
			 * Get first order which ends after this in given index,
			 * assume that orders are sorted up by order ending
			 *
			 * @param orders Sorted orders list
			 * @param index Index in orders to compare with
			 * @return index of found order or 0 if first order
			 */
			int firstAlgorithmfindIndex(std::vector<aal::Order*> orders, int index);
	};
}

#endif
