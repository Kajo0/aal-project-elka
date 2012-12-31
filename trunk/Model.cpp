// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Model.h"
#include "Reader.h"
#include "Generator.h"

namespace aal {

	const int Model::MAX_ORDER_LENGTH = 5;
	const int Model::DAYS_PER_WEEK = 5;

	Model::Model(): ordersDuration_(0) {
		srand(time(0));
		//std::cout<<"Model()\n";
	}

	Model::~Model() {
		//std::cout<<"~Model()\n";
		clearData();
	}

	void Model::clearData() {
		for(std::vector<Classroom*>::const_iterator it = classrooms_.begin(); it < classrooms_.end(); ++it)
			delete *it;
		for(std::vector<Order*>::const_iterator it = orders_.begin(); it < orders_.end(); ++it)
			delete *it;

		classrooms_.clear();
		orders_.clear();
	}

	void Model::readData() {
		Reader r;
		std::pair<std::vector<Order*>, std::vector<Classroom*> > result = r.readFrom(&std::cin);

		orders_ = result.first;
		classrooms_ = result.second;

		calculateMaxOccupancy();
	}

	void Model::readData(const char* path) {
		Reader r;
		std::ifstream *in = new std::ifstream();

		in->open(path);
		std::pair<std::vector<Order*>, std::vector<Classroom*> > result = r.readFrom(in);
		in->close();

		delete in;

		orders_ = result.first;
		classrooms_ = result.second;

		calculateMaxOccupancy();
	}

	void Model::calculateMaxOccupancy() {
		ordersDuration_ = 0;

		for (std::vector<Order*>::const_iterator it = orders_.begin(); it != orders_.end(); ++it)
			ordersDuration_ += (*it)->interval();
	}

	int Model::ordersDuration() {
		return ordersDuration_;
	}

	void Model::str() {
		std::cout<<"\n\n";

		for (std::vector<Classroom*>::const_iterator it = classrooms_.begin(); it != classrooms_.end(); ++it)
			std::cout<<**it<<"\n";

		std::cout<<"\n";
		
		for (std::vector<Order*>::const_iterator it = orders_.begin(); it != orders_.end(); ++it)
			std::cout<<**it<<"\n";
		
		std::cout<<"\n Sum of orders duration:\t"<<ordersDuration_<<"\n";
		std::cout<<" Max classrooms/days occupancy:\t"<<classrooms_.size() * DAYS_PER_WEEK * 24<<"\n\n";
	}

	std::vector<Classroom*>& Model::classrooms() {
		return classrooms_;
	}
	
	std::vector<Order*>& Model::orders() {
		return orders_;
	}

	void Model::generateData(int problem_size) {
		clearData();

		Generator gen;
		std::pair<std::vector<Order*>, std::vector<Classroom*> > result = gen.generateData(problem_size);
		orders_ = result.first;
		classrooms_ = result.second;

		calculateMaxOccupancy();
	}
}
