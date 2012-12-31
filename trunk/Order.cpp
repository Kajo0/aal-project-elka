// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <cstdio>
#include "Order.h"

namespace aal {
	int Order::i = 0;

	Order::Order(int begin, int end, int day, const char *id)/*: begin_(begin), end_(end), id_(id)*/ {
		//std::cout<<"Order()\n";
		begin_ = begin;
		end_ = end;
		id_ = id;
		
		begin_ += ((day - 1) * 24);
		end_ += ((day - 1) * 24);

		if (end_ < begin_) {
			int tmp = begin_;
			begin_ = end_;
			end_ = tmp;
		}

		if (std::string(id).length() == 0) {
			char c[10];
			sprintf(c, "%d", Order::i++);
			id_ = c;
		}
	}

	Order::~Order() {
		//std::cout<<"~Order()\n";
	}

	std::string Order::id() {
		return id_;
	}

	int Order::begin() {
		return begin_;
	}

	int Order::end() {
		return end_;
	}

	int Order::interval() const {
		return end_ - begin_;
	}

	bool Order::operator==(const Order &other) {
		return id_ == other.id_;
	}

	std::ostream& operator<<(std::ostream &os, const Order &order) {
		os<<"/"<<order.id_<<"/\t";
		os<<order.begin_;
		os<<" - ";
		os<<order.end_;
		return os;
	}
}
