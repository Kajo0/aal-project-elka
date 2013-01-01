// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Classroom.h"
#include "Order.h"

namespace aal {
	/**
	 * Class responsible for storing calculation model data
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Model {
		public:
			/** Maximum length of order in generation */
			static const int MAX_ORDER_LENGTH;

			/** Amount of days to which orders are generating */
			static const int DAYS_PER_WEEK;

		private:
			/** Generated or read classrooms */
			std::vector<Classroom*> classrooms_;

			/** Generated or read orders */
			std::vector<Order*> orders_;

			/** Sum of model orders intervals */
			int ordersDuration_;

		public:
			/**
			 * C-tor
			 */
			Model();

			/**
			 * D-tor
			 */
			virtual ~Model();

			/**
			 * Read data from stdin
			 */
			void readData();

			/**
			 * Read data from file
			 */
			void readData(const char* path);

			/**
			 * Write classrooms and orders into stdout
			 */
			void str();

			/**
			 * Get classrooms from models
			 *
			 * @return Vector of classrooms
			 */
			std::vector<Classroom*>& classrooms();

			/**
			 * Get orders from model
			 *
			 * @return Vector of orders
			 */
			std::vector<Order*>& orders();

			/**
			 * Generate data into classrooms and orders appropriate to given problem size
			 *
			 * @param problem_size Size of problem
			 */
			void generateData(int problem_size);

			/**
			 * Calculate sum of orders intervals
			 */
			void calculateMaxOccupancy();

			/**
			 * Get sum of orders intervals
			 *
			 * @return Orders duration time
			 */
			int ordersDuration();

		private:
			/**
			 * Clear classrooms and orders from model
			 */
			void clearData();
	};
}

#endif
