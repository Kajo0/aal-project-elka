// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include "Classroom.h"

namespace aal {
	Classroom::Classroom(const char *id): id_(id), occupancy_(0) {
		//std::cout<<"Classroom()\n";
	}

	Classroom::Classroom(const Classroom &other) {
		id_ = other.id_;
		occupancy_ = other.occupancy_;
		scheduleList_ = std::list<Order*>(other.scheduleList_);
	}

	Classroom::~Classroom() {
		//std::cout<<"~Classroom()\n";
	}

	std::list<Order*>& Classroom::scheduleList() {
		return scheduleList_;
	}

	int Classroom::occupancy() {
		return occupancy_;
	}

	std::string Classroom::id() {
		return id_;
	}

	void Classroom::addOrder(Order *order) {
		scheduleList_.push_back(order);
		occupancy_ += order->interval();
	}

	std::list<std::string> Classroom::ordersIds() {
		std::list<std::string> tmp;

		for (std::list<Order*>::const_iterator it = scheduleList_.begin(); it != scheduleList_.end(); ++it)
			tmp.push_back((*it)->id());

		return tmp;
	}
	
	std::ostream& operator<<(std::ostream &os, const Classroom &classroom) {
		os<<classroom.id_;

		return os;
	}
}
