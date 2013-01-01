// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef RESULT_H
#define RESULT_H

#include <map>
#include <vector>
#include "Classroom.h"
#include "Order.h"

namespace aal {
	/**
	 * Class responsible for storing results of algorithms calculations
	 * Contains each classroom with created schedules.
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Result {
			/** Map with key as classroom id and value as classrooms */
			std::map<std::string, Classroom*> schedule_;

			/** Sum of classrooms schedules occupancy */
			int occupancy_;

		public:
			/**
			 * C-tor
			 */
			Result();

			/**
			 * C-tor
			 * Copy classrooms object as own instances
			 *
			 * @param classrooms Vector of classrooms
			 */
			Result(std::vector<Classroom*> classrooms);

			/**
			 * Copying C-tor
			 * Copy data but creates it's own classrooms instances
			 *
			 * @param other Other Result object
			 */
			Result(const Result &other);

			/**
			 * D-tor
			 */
			virtual ~Result();

			/**
			 * Initialize result,
			 * clean old classrooms and set occupancy to 0
			 *
			 * @param classrooms Vector of other classrooms
			 */
			void init(std::vector<Classroom*> classrooms);

			/**
			 * Get result schedule
			 *
			 * @return Result classrooms map
			 */
			std::map<std::string, Classroom*>& schedule();

			/**
			 * Get occupancy of orders in each classroom in this result
			 *
			 * @return Sum of scheduled orders times
			 */
			int occupancy();

			/**
			 * Insert classroom into result instead of existing classroom identified by id
			 * Alse update occupancy
			 *
			 * @param classroom Another classroom to replace
			 */
			void insertClassroom(Classroom &classroom);

			/**
			 * Add order into classroom identified by given id
			 * Increase occupancy
			 *
			 * @param id Id of classroom to add order to
			 * @param order Order to add into classroom schedule
			 */
			void addOrder(const std::string id, Order *order);

			/**
			 * Save result to file as HTML tables
			 *
			 * @param path Path to result html file
			 */
			void saveToFile(const char* path);
			
			/**
			 * Just 4 debug to show result
			 */
			friend std::ostream& operator<<(std::ostream &os, const Result &result);

		private:
			/**
			 * Recalculate occupancy from stored classrooms
			 */
			void calculateOccupancy();

			/**
			 * Clean old classrooms instances from result
			 */
			void clean();
	};
}

#endif
