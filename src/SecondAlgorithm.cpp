// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <algorithm>
#include <cmath>
#include "SecondAlgorithm.h"
#include "Generator.h"

namespace aal {

	/**
	 * Order comparator,
	 * just because C++0x and my g++, no struct etc.
	 *
	 * @param first First Order object
	 * @param second Second Order object
	 * @return true if first ends before second, false otherwise
	 */
	bool secondAlgorithmOrderCmp(Order *first, Order *second) {
		return (first->end() < second->end());
	}

	SecondAlgorithm::SecondAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders): Algorithm(classrooms, orders) {
		//std::cout<<"SecondAlgorithm()\n";
	}

	SecondAlgorithm::~SecondAlgorithm() {
		//std::cout<<"~SecondAlgorithm()\n";
	}

	double SecondAlgorithm::getTn(const unsigned int problem_size) {
		Generator gen;
		std::pair<int, int> nk = gen.getProblemNK(problem_size);
		int n = nk.first;
		int k = nk.second;

		// T(n) = n * log(n) + n * k;
		double res1 = n * log(n);
		double res2 = n * k;

		return (res1 < res2 ? res2 : res1);
	}

	Result SecondAlgorithm::run() {

		/*
		 * Sort by earliest end time
		 */
		std::sort(orders_.begin(), orders_.end(), secondAlgorithmOrderCmp);

		/**
		 * Go through order
		 */
		for (std::vector<Order*>::const_iterator it = orders_.begin(); it != orders_.end(); ++it) {

			/**
			 * Try to put order in first possible classroom
			 */
			for (std::map<std::string, Classroom*>::iterator i = result_.schedule().begin(); i != result_.schedule().end(); ++i) {

				std::list<Order*> tmp = i->second->scheduleList();

				/*
				 * If empty schedule put there or
				 * if last put order ends before considered
				 * order also put because it's sorted by end time
				 * and break classroom loop => try to put next order the same way
				 */
				if (!tmp.size() || tmp.back()->end() <= (*it)->begin()) {
					result_.addOrder(i->first, *it);
					break;
				}
			}
		}

		return result_;
	}
}
