// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include "Algorithm.h"

namespace aal {

	Algorithm::Algorithm(std::vector<Classroom*> classrooms, std::vector<Order*> orders): classrooms_(classrooms), orders_(orders), result_(classrooms) {
		//std::cout<<"Algorithm()\n";
	}

	Algorithm::~Algorithm() {
		//std::cout<<"~Algorithm()\n";
	}
	
	void Algorithm::init(std::vector<Classroom*> classrooms, std::vector<Order*> orders) {
		classrooms_ = classrooms;
		orders_ = orders;
		result_.init(classrooms);
	}
}
