// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <algorithm>
#include <cmath>
#include "FirstAlgorithm.h"
#include "Generator.h"

namespace aal {

	int FirstAlgorithm::firstAlgorithmfindIndex(std::vector<aal::Order*> orders, int index) {
		int i;
		for (i = 0; i < index; ++i)
			if (orders[i]->end() > orders[index]->begin())
				break;

		return i;
	}

	/**
	 * Result comparator,
	 * just because C++0x and my g++, no struct etc.
	 *
	 * @param first First Result object
	 * @param second Second Result object
	 * @return true if first is less occupied that second, false otherwise
	 */
	bool firstAlgorithmResultCmp(Result &first, Result &second) {
		return (first.occupancy() < second.occupancy());
	}

	/**
	 * Order comparator,
	 * just because C++0x and my g++, no struct etc.
	 *
	 * @param first First Order object
	 * @param second Second Order object
	 * @return true if first ends before second, false otherwise
	 */
	bool firstAlgorithmOrderCmp(Order *first, Order *second) {
		return (first->end() < second->end());
	}
	
	FirstAlgorithm::FirstAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders): Algorithm(classrooms, orders) {
		//std::cout<<"FirstAlgorithm()\n";
	}

	FirstAlgorithm::~FirstAlgorithm() {
		//std::cout<<"~FirstAlgorithm()\n";
	}

	double FirstAlgorithm::getTn(const unsigned int problem_size) {
		Generator gen;
		std::pair<int, int> nk = gen.getProblemNK(problem_size);
		int n = nk.first;
		int k = nk.second;

		// T(n) = n * log(n) + 2 * k * n + 2 * k * n^2
		double res1 = n * log(n);		// probably never
		double res2 = k * n;		// probably never
		double res3 = k * n * n;	// probably always

		return (res1 > res2 ? (res1 > res3 ? res1 : res3) : (res2 > res3 ? res2 : res3));
	}

	Result FirstAlgorithm::run() {

//		Just because no C++0x and my g++
//		struct OrderComparator {
//			bool operator()(Order *first, Order *second) {
//				return (first->end() < second->end());
//			}
//		} order_cmp;

		/*
		 * Sort orders by earliest ending
		 */
		std::sort(orders_.begin(), orders_.end(), firstAlgorithmOrderCmp);

		/*
		 * Get copy of orders pointers to remove from them already used
		 */
		std::vector<Order*> orders = std::vector<Order*>(orders_);

		/*
		 * Go through each classroom
		 */
		for (std::vector<Classroom*>::const_iterator iter = classrooms_.begin(); iter != classrooms_.end(); ++iter) {

			/** Max id of result in considered classroom */
			int max_result = 0;

			/*
			 * Local variables to compare
			 */
			int t1 = 0;
			int t2 = 0;
			int i = 1;

			/** Vector of results for next orders */
			std::vector<Result> results;
			// Push '0' time result to make algorithm easier
			results.push_back(Result(classrooms_));

			/*
			 * Go through left orders
			 */
			for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); ++it, ++i) {

				// Get last best schedule occupancy
				t1 = results[i - 1].schedule()[(*iter)->id()]->occupancy();

				// Get id in vector of earliest algorithm which ends after considered algorithm beginning..
				int a = firstAlgorithmfindIndex(orders, i - 1);
				// ..And add to that schedule occupancy actual order occupancy
				t2 = results[a].schedule()[(*iter)->id()]->occupancy() + (*it)->interval();

				/*
				 * Compare them and choose better
				 */
				if (t1 > t2) {
					// Copy last found best results
					Result result(results[i - 1]);
					// And push actual generated result into vector
					results.push_back(result);
				} else {
					// Get found best result
					Result result(results[a]);
					// Add matching order
					result.addOrder((*iter)->id(), *it);
					// And push result into vector
					results.push_back(result);

					// Set that this result id is the best
					max_result = i;
				}
			}

			// Get max occupied result
			Result max = results[max_result];
			// And insert this scheduled classroom into algorithm result
			result_.insertClassroom(*max.schedule()[(*iter)->id()]);

			// Remove used orders from vector for the next classroom loop
			for (std::list<Order*>::const_iterator it = max.schedule()[(*iter)->id()]->scheduleList().begin(); it != max.schedule()[(*iter)->id()]->scheduleList().end(); ++it)
				orders.erase(std::remove(orders.begin(), orders.end(), *it), orders.end());
		}

		return result_;
	}
}
