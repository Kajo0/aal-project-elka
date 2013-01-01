// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "ThirdAlgorithm.h"
#include "Generator.h"

namespace aal {


	/**
	 * Result comparator,
	 * just because C++0x and my g++, no struct etc.
	 *
	 * @param first First Result object
	 * @param second Second Result object
	 * @return true if first is less occupied that second, false otherwise
	 */
	bool thirdAlgorithmResultCmp(Result &first, Result &second) {
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
	bool thirdAlgorithmOrderCmp(Order *first, Order *second) {
		return (first->end() < second->end());
	}

	ThirdAlgorithm::ThirdAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders): Algorithm(classrooms, orders) {
		//std::cout<<"ThirdAlgorithm()\n";
	}

	ThirdAlgorithm::~ThirdAlgorithm() {
		//std::cout<<"~ThirdAlgorithm()\n";
	}

	void ThirdAlgorithm::init(std::vector<Classroom*> classrooms, std::vector<Order*> orders) {
		Algorithm::init(classrooms, orders);
		results_.clear();
	}

	double ThirdAlgorithm::getTn(const unsigned int problem_size) {
		Generator gen;
		std::pair<int, int> nk = gen.getProblemNK(problem_size);
		int n = nk.first;
		int k = nk.second;

		// T(n, k) = k + n + T(n - 1, k) + T(n, k - 1)

		// res0 = n; res00 = k;
		double res1 = n;// * (n + 1) / 2;
		double res2 = (n - 1) * (2 * k + n) / 2 + (k - 1) * (2 * n + k) / 2;//n * (n - 1) / 2;
		for (int i = 0; i < n; ++i)
			res2 *= k;//TODO I have no idea how complex it is :/

		return (res1 < res2 ? res2 : res1);
	}

	Result ThirdAlgorithm::run() {

		/*
		 * Sort orders by earliest end time
		 */
		std::sort(orders_.begin(), orders_.end(), thirdAlgorithmOrderCmp);

		/*
		 * Do combinations from the beginning
		 */
		combinations(orders_, 0, result_, result_.schedule().size());

		/*
		 * Find max occupied result of generated combinations
		 */
		Result max = *std::max_element(results_.begin(), results_.end(), thirdAlgorithmResultCmp);
//		result_ = max;

		return max;
	}

	void ThirdAlgorithm::combinations(std::vector<Order*> &orders, int ommiter, Result &last_result, int classroom_amount_left) {
		/*
		 * If no classrooms left to schedule, just return
		 */
		if (classroom_amount_left < 1)
			return;

		// Get classroom to schedule
		std::string key = "";
		int cct = 0;
		for (std::map<std::string, Classroom*>::const_iterator it = last_result.schedule().begin(); it != last_result.schedule().end(); ++it)
			if (++cct == classroom_amount_left)
				key = it->first;

		/*
		 * Go through orders from given one
		 */
		for (unsigned int i = ommiter; i < orders.size(); ++i) {
			std::vector<Order*> local_orders(orders);

			// Copy last result
			Result local_result(last_result);

			std::list<Order*> tmp = local_result.schedule()[key]->scheduleList();

			/*
			 * If possible to add order, add
			 * otherwise some combinations go away
			 */
			if (!tmp.size() || tmp.back()->end() <= local_orders[i]->begin()) {
				// Add order to classroom schedule
				local_result.addOrder(key, local_orders[i]);

				// Push generated result
				results_.push_back(local_result);

				/*
				 * Erase used order
				 */
				for (std::vector<Order*>::iterator it = local_orders.begin(); it != local_orders.end(); ++it)
					if ((*it)->id() == local_orders[i]->id()) {
						local_orders.erase(it);
						break;
					}

				/*
				 * Do combination without actual order, from next order..
				 */
				combinations(local_orders, i, local_result, classroom_amount_left);
				/*
				 * ..and into next classroom
				 */
				combinations(local_orders, 0, local_result, classroom_amount_left - 1);
			}
		}
	}
}
