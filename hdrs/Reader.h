// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Order.h"
#include "Classroom.h"

namespace aal {
	/**
	 * Class responsible for reading data from given stream
	 *
	 * @author Mikolaj Markiewicz
	 */
	class Reader {
		public:
			/**
			 * C-tor
			 */
			Reader();

			/**
			 * D-tor
			 */
			virtual ~Reader();

			/**
			 * Read data from given stream
			 * Proper structure of data:<br>
			 * {Id/name of classroom}+<br>
			 * {day of order as 1,2,..} {begin time} {end time} [{Id/name of order}]+
			 *
			 * @param input Input stream
			 * @return Pair of vector of read orders and vector of read classrooms
			 */
			std::pair<std::vector<Order*>, std::vector<Classroom*> > readFrom(std::istream *input);
	};
}

#endif
