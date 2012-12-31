// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include "Result.h"
#include "Model.h"

namespace aal {

	Result::Result(): occupancy_(0) {

	}

	Result::Result(std::vector<Classroom*> classrooms): occupancy_(0) {
		//std::cout<<"Result()\n";
		init(classrooms);
	}

	Result::Result(const Result &other) {
		occupancy_ = other.occupancy_;

		for (std::map<std::string, Classroom*>::const_iterator it = other.schedule_.begin(); it != other.schedule_.end(); ++it)
			schedule_.insert(std::make_pair(it->first, new Classroom(*(it->second))));
	}

	Result::~Result() {
		//std::cout<<"~Result()\n";
		clean();
	}

	void Result::init(std::vector<Classroom*> classrooms) {
		clean();

		occupancy_ = 0;

		for (std::vector<Classroom*>::const_iterator it = classrooms.begin(); it != classrooms.end(); ++it)
			schedule_.insert(std::make_pair((*it)->id(), new Classroom(**it)));
	}

	void Result::clean() {
		for (std::map<std::string, Classroom*>::const_iterator it = schedule_.begin(); it != schedule_.end(); ++it)
			delete it->second;

		schedule_.clear();
	}

	std::map<std::string, Classroom*>& Result::schedule() {
		return schedule_;
	}

	void Result::insertClassroom(Classroom &classroom) {
		occupancy_ -= schedule_[classroom.id()]->occupancy();
		occupancy_ += classroom.occupancy();

		delete schedule_[classroom.id()];
		schedule_[classroom.id()] = new Classroom(classroom);
	}

	void Result::addOrder(const std::string id, Order *order) {
		schedule_[id]->addOrder(order);
		occupancy_ += order->interval();
	}

	int Result::occupancy() {
		if (occupancy_ == 0)
			calculateOccupancy();

		return occupancy_;
	}

	void Result::calculateOccupancy() {
		int occ = 0;

		for (std::map<std::string, Classroom*>::const_iterator it = schedule_.begin(); it != schedule_.end(); ++it)
			occ += it->second->occupancy();

		occupancy_ = occ;
	}

	void Result::saveToFile(const char* path) {
		std::ofstream out;
		out.open(path, std::ios::out);
		int sum_of;

		out<<"<html><head>";
		out<<"<style>h1 { text-align: center; margin: auto; text-shadow: 1px 1px 6px #FFF; } body { background-color: #999; font-family: arial; } tr { height: 1.5em; } table { border-collapse: collapse; border: 1px solid #000; margin: 0.5em; float: left; } th { font-size: 0.9em; font-weight: bold; width: 5em; text-align: center; background-color: #ABC; border: 1px solid #000; padding: 0; } td { text-align: center; font-size: 1.2em; padding: 0; border: 1px dotted #000; background-color: #CDE; } caption { border: 1px solid #000; margin-bottom: -1px; background-color: #DEF; padding: 0.2em; font-size: 2em; } span { display: block; font-size: 0.5em; }</style>";
		out<<"</head><body><h1 id=sum_of>Total classrooms occupancy: </h1>";

		for (std::map<std::string, Classroom*>::const_iterator it = schedule_.begin(); it != schedule_.end(); ++it) {
			sum_of += it->second->occupancy();

			Order* orders[Model::DAYS_PER_WEEK][24];
			for (int y = 0; y < 24; ++y)
				for (int x = 0; x < Model::DAYS_PER_WEEK; ++x)
					orders[x][y] = 0;

			for (std::list<Order*>::const_iterator i = it->second->scheduleList().begin(); i != it->second->scheduleList().end(); ++i) {
				for (int a = (*i)->begin(); a < (*i)->end(); ++a)
					orders[a / 24][a % 24] = *i;
			}

			out<<"<table>";
			out<<"<caption>Classroom "<<it->first<<"<span>Occupied "<<it->second->occupancy()<<" hours</span>"<<"</caption>";
			out<<"<thead></thead><tbody>";

			out<<"<tr>";
			out<<"<th></th>";
			for (int x = 0; x < Model::DAYS_PER_WEEK; ++x)
				out<<"<th> Dzien "<<(x + 1)<<"</th>";
			out<<"</tr>";

			std::vector<std::string> used_order_id;

			for (int y = 0; y < 24; ++y) {
				out<<"<tr>";
				out<<"<th>"<<y<<" - "<<y + 1<<"</th>";

				for (int x = 0; x < Model::DAYS_PER_WEEK; ++x) {
					if (!orders[x][y]) {
						out<<"<td style=\"background-color: #FAA\">&nbsp;</td>";
						continue;
					}

					if (std::find(used_order_id.begin(), used_order_id.end(), orders[x][y]->id()) != used_order_id.end())
						continue;

					out<<"<td rowspan=\""<<orders[x][y]->interval()<<"\">";
					out<<orders[x][y]->id();
					out<<"</td>";

					used_order_id.push_back(orders[x][y]->id());
				}

				out<<"</tr>";
			}

			out<<"</tbody><tfoot></tfoot>";
		}

		out<<"<script>document.getElementById('sum_of').innerHTML += "<<sum_of<<";</script>";
		out<<"</body></html>";

		out.close();
	}

	std::ostream& operator<<(std::ostream &os, const Result &result) {
		for (std::map<std::string, Classroom*>::const_iterator it = result.schedule_.begin(); it != result.schedule_.end(); ++it) {
			os<<"\t";

			os<<it->first<<": "<<it->second->occupancy()<<" ( ";
			
			if (it->second->scheduleList().size())
				for (std::list<Order*>::const_iterator i = it->second->scheduleList().begin(); i != it->second->scheduleList().end(); ++i)
					os<<(**i)<<", ";

			os<<")\n";
		}

		os<<result.occupancy_<<"\n";

		return os;
	}

}
