// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <list>
#include "Order.h"

namespace aal {
	/**
	 * Class responsible for storing orders as schedule and their duration
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Classroom {
			/** Classroom id / name */
			std::string id_;

			/** List of orders put in this classroom */
			std::list<Order*> scheduleList_;

			/** Classroom time occupancy by actual orders set */
			int occupancy_;

		public:
			/**
			 * C-tor
			 *
			 * @param id Id / name of classroom
			 */
			Classroom(const char *id);

			/**
			 * Copying C-tor
			 * Copy fields values and list of scheduled orders
			 *
			 * @param other Another alassroom object
			 */
			Classroom(const Classroom &other);

			/**
			 * D-tor
			 */
			virtual ~Classroom();

			/**
			 * Get list of scheduled orders in this classroom
			 *
			 * @return List of scheduled orders
			 */
			std::list<Order*>& scheduleList();

			/**
			 * Get actual classroom occupancy by scheduled orders
			 *
			 * @return Classroom occupancy time
			 */
			int occupancy();

			/**
			 * Get classroom id
			 *
			 * @return Classroom id
			 */
			std::string id();

			/**
			 * Add order to classroom, just put without check overlapping
			 * also update classroom occupancy by adding order occupancy
			 *
			 * @param order Order to add
			 */
			void addOrder(Order *order);

			/**
			 * Get ids of scheduled orders in this classroom
			 *
			 * @return List of scheduled orders ids
			 * @deprecated Used by less effective vector erase function
			 */
			std::list<std::string> ordersIds();
			
			/**
			 * Just 4 debug, stream classroom id and scheduled orders
			 */
			friend std::ostream& operator<<(std::ostream &os, const Classroom &classroom);
	};
}

#endif
