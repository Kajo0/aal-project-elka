// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <cstdlib>
#include <cstdio>
#include "Generator.h"
#include "Model.h"

namespace aal {
	Generator::Generator() {
		//std::cout<<"Generator()\n";
	}

	Generator::~Generator() {
		//std::cout<<"~Generator()\n";
	}

	std::pair<int, int> Generator::getProblemNK(const unsigned int problem_size) {
		int n = problem_size * 10;
		int k = problem_size / 10;
		k = (k == 0 ? 1 : k);

		return std::make_pair(n, k);
	}

	std::pair<std::vector<Order*>, std::vector<Classroom*> > Generator::generateData(const unsigned int problem_size) {
		std::vector<Order*> orders;
		std::vector<Classroom*> classrooms;

		std::pair<int, int> nk = getProblemNK(problem_size);
		int n = nk.first;
		int k = nk.second;

		for (int i = 0; i < k; ++i) {
			char buf[10];
			sprintf(buf, "%d", i);

			classrooms.push_back(new Classroom(buf));
		}

		int day = 0;
		int t1 = 0;
		int t2 = 0;

		for (int i = 0; i < n; ++i) {
			char buf[10];
			sprintf(buf, "%d", i);

			day = rand() % Model::DAYS_PER_WEEK + 1;
			t1 = rand() % 24;
			t2 = std::min(t1 + rand() % Model::MAX_ORDER_LENGTH + 1, 24);

			orders.push_back(new Order(t1, t2, day, buf));
		}

		return std::make_pair(orders, classrooms);
	}

}
