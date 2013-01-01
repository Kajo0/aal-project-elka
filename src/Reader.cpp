// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <fstream>
#include <sstream>
#include "Reader.h"
using namespace std;

namespace aal {
	Reader::Reader() {
		//std::cout<<"Reader()\n";
	}

	Reader::~Reader() {
		//std::cout<<"~Reader()\n";
	}

	std::pair<std::vector<Order*>, std::vector<Classroom*> > Reader::readFrom(std::istream *input) {
		std::vector<Classroom*> classrooms;
		std::vector<Order*> orders;

		string stringLine;
		stringstream ssLine;
		char cLine[50];

		std::string str;
		int day, begin, end;

		while (input->getline(cLine, 50)) {
			stringLine = cLine;
			ssLine.str("");
			ssLine.write(cLine, 50);

			int lTabs = 0;
			int lPos = 0;
			while ((lPos = stringLine.find(" ", lPos)) != -1) {
				lPos++;
				lTabs++;
			}

			if (stringLine.length() == 0)
				break;

			// Classrooms
			if (lTabs == 0) {
				classrooms.push_back(new Classroom(stringLine.c_str()));
			} // Orders
			else if (lTabs == 2) {
				ssLine>>day;
				ssLine>>begin;
				ssLine>>end;
				orders.push_back(new Order(begin, end, day));
			}
			else if (lTabs == 3) {
				ssLine>>day;
				ssLine>>begin;
				ssLine>>end;
				int d = 1 + 1;
				d += (begin / 10 == 0 ? 1 : 2) + 1;
				d += (end / 10 == 0 ? 1 : 2) + 1;
				str = stringLine.substr(d);
				orders.push_back(new Order(begin, end, day, str.c_str()));
			}
		}

		return std::make_pair(orders, classrooms);
	}
}
