// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include "FourthAlgorithm.h"
#include "FirstAlgorithm.h"
#include "SecondAlgorithm.h"
#include "ThirdAlgorithm.h"
#include "Generator.h"
#include "Model.h"

namespace aal {

	/**
	 * Structure for making parts of vector of lists of orders
	 *
	 * @author Mikolaj Markiewicz
	 */
	typedef struct {
		/** Id in part starts */
		int from_;

		/** Id in part ends */
		int to_;

		/** Amount of maximum list of different orders in part */
		unsigned int size_;

		/** List of different orders in part */
		std::vector<Order*> ordersIn_;

		/**
		 * Add unique order into list
		 *
		 * @param order Order to add
		 */
		void addOrder(Order *order) {
			if (!contains(order))
				ordersIn_.push_back(order);
		}

		/**
		 * Check whether order already exists on orders list
		 *
		 * @param order Order to check existence
		 * @return true if exists, false otherwise
		 */
		bool contains(Order *other) {
			for (std::vector<Order*>::const_iterator it = ordersIn_.begin(); it != ordersIn_.end(); ++it)
				if (other->id() == (*it)->id())
					return true;

			return false;
		}
	} PartContainer;

	FourthAlgorithm::FourthAlgorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders): Algorithm(classrooms, orders), vectorList_(Model::DAYS_PER_WEEK * 24) {
		//std::cout<<"FourthAlgorithm()\n";
	}

	FourthAlgorithm::~FourthAlgorithm() {
		//std::cout<<"~FourthAlgorithm()\n";
	}

	void FourthAlgorithm::init(std::vector<Classroom*> classrooms, std::vector<Order*> orders) {
		Algorithm::init(classrooms, orders);
		vectorList_.clear();
		vectorList_ = std::vector<std::list<Order*> >(Model::DAYS_PER_WEEK * 24);
	}

	double FourthAlgorithm::getTn(const unsigned int problem_size) {
		Generator gen;
		std::pair<int, int> nk = gen.getProblemNK(problem_size);
		int n = nk.first;
		int k = nk.second;

		// T(n) = n + c * (n + n * n?) + c * n * k * Talg(n)
		double res1 = n * n;
		double res2 = n * k * n;

		return (res1 < res2 ? res2 : res1);
	}

	Result FourthAlgorithm::run() {

		/*
		 * Fill vector of lists of orders
		 */
		for (std::vector<Order*>::const_iterator it = orders_.begin(); it != orders_.end(); ++it)
			for (int i = (*it)->begin(); i < (*it)->end(); ++i)
				vectorList_[i].push_back(*it);

		/** Local parts list */
		std::list<PartContainer*> parts;
		/** Part pointer, first unused part, will be deleted but its less ifs */
		PartContainer *cnt = new PartContainer();

		/** Used for determine from - to ids */
		int i = 0;
		/*
		 * Go through vector of lists of orders
		 */
		for (std::vector<std::list<Order*> >::const_iterator iter = vectorList_.begin(); iter != vectorList_.end(); ++iter, ++i) {
			/*
			 * Whether is needed new part = old part has been end
			 * New part is needed if nothing or unique non overlap element, has been found
			 */
			bool new_part = true;

			// If empty list, just omit
			if (iter->size() > 0) {
				/*
				 * Check whether new part is unnecessary or needed
				 */
				for (std::list<Order*>::const_iterator it = iter->begin(); it != iter->end(); ++it)
					// If Order already is in last part, do not create new part
					if (cnt->contains((*it))) {
						new_part = false;
						break;
					}

				if (new_part) {
					// Set that last was the one before
					cnt->to_ = i - 1;

					// Create new one, set it as 1 width and push into list of parts
					cnt = new PartContainer();
					cnt->from_ = i;
					cnt->to_ = i;

					parts.push_back(cnt);
				} else {
					cnt->to_ = i;
				}

				// Add unique parts from this list of orders into considered part list
				for (std::list<Order*>::const_iterator it = iter->begin(); it != iter->end(); ++it)
					cnt->addOrder(*it);

				// Update maximum size of overlapping orders
				cnt->size_ = (iter->size() > cnt->size_? iter->size() : cnt->size_);
			}
		}

		Algorithm *alg;

		/*
		 * Go through parts
		 */
		for (std::list<PartContainer*>::const_iterator it = parts.begin(); it != parts.end(); ++it) {

			/*
			 * If maximum size is less than classrooms amount, just how it's going
			 */
			if ((*it)->size_ <= classrooms_.size())
				alg = new SecondAlgorithm(classrooms_, (*it)->ordersIn_);
			/*
			 * If it doesn't and it's not too big problem, use exact algorithm
			 */
			else if ((*it)->ordersIn_.size() < 10 && classrooms_.size() < 5)
				alg = new ThirdAlgorithm(classrooms_, (*it)->ordersIn_);
			/*
			 * Otherwise use algorithm close to optimal
			 */
			else
				alg = new FirstAlgorithm(classrooms_, (*it)->ordersIn_);

			// Generate result of subproblem
			Result r = alg->run();

			/*
			 * Put generated schedules into proper classrooms in finish result
			 */
			for (std::map<std::string, Classroom*>::const_iterator mp = r.schedule().begin(); mp != r.schedule().end(); ++mp)
				for (std::list<Order*>::const_iterator ord = mp->second->scheduleList().begin(); ord != mp->second->scheduleList().end(); ++ord)
					result_.addOrder(mp->first, *ord);

			// Iteration cleaning
			delete alg;
			delete *it;
		}

		return result_;
	}
}
