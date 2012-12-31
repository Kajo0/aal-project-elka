// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include "Order.h"
#include "Classroom.h"

namespace aal {
	/**
	 * Class responsible for generate data for specified problem size
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Generator {
		public:
			/**
			 * C-tor
			 */
			Generator();

			/**
			 * D-tor
			 */
			virtual ~Generator();

			/**
			 * Generate classrooms and orders appropriate to given problem size
			 *
			 * @param problem_size Size of problem to generate data by
			 * @return Pair of generated vector of Orders and vector of classrooms
			 */
			std::pair<std::vector<Order*>, std::vector<Classroom*> > generateData(const unsigned int problem_size);

			/**
			 * Get amount of orders, and classrooms equivalent to problem size
			 *
			 * @param problem_size Problem size to get values by
			 * @return Pair (n, k) of amount of orders and amount of classrooms
			 */
			std::pair<int, int> getProblemNK(const unsigned int problem_size);
	};
}

#endif
