// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef ORDER_H
#define ORDER_H

#include <string>

namespace aal {
	/**
	 * Class representing order with begin and end time as interval
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Order {
		private:
			/** Static value to generate next ID's if not given */
			static int i;

			/** Order id / name */
			std::string id_;

			/** Begin of order time */
			int begin_;

			/** End of order time */
			int end_;

		public:
			/**
			 * C-tor
			 * If begin > end, replace order of times
			 * Change day and period into hours e.g. day 2 begin 1 end 2 => begin 25 end 26
			 *
			 * @param begin Begin of order
			 * @param end End of order
			 * @param day In which day order is
			 * @param id Id / name of order
			 */
			Order(int begin, int end, int day = 1, const char *id = "");

			/**
			 * D-tor
			 */
			virtual ~Order();

			/**
			 * Get id of order
			 *
			 * @return Id / name of order
			 */
			std::string id();

			/**
			 * Get begin time of order
			 *
			 * @return Begin time of order
			 */
			int begin();

			/**
			 * Get end time of order
			 *
			 * @return End time of order
			 */
			int end();

			/**
			 * Get orders duration time
			 *
			 * @return Interval between begin and end of order
			 */
			int interval() const;

			/**
			 * Check whether ids of orders are equal
			 *
			 * @param other Order to compare
			 * @return true if same id, false otherwise
			 */
			bool operator==(const Order &other);

			/**
			 * Just 4 debug to show order information
			 */
			friend std::ostream& operator<<(std::ostream &os, const Order &order);
	};
}

#endif
