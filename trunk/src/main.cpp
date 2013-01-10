// Mikolaj Markiewicz
// Problem: Rezerwacja sal wykladowych

#include <iostream>
#include <cstdlib>
#include "Timer.h"
#include "Model.h"
#include "Result.h"
#include "FirstAlgorithm.h"
#include "SecondAlgorithm.h"
#include "ThirdAlgorithm.h"
#include "FourthAlgorithm.h"
using namespace std;

/**
 * Write to stdout information about app usage
 *
 * @param prog App name
 */
void properRun(const char* prog) {
	cout<<"Poprawne wywolanie programu:\n";
	cout<<"\t"<<prog<<" -d plik\n";
	cout<<"\t"<<prog<<" -d < plik\n";
	cout<<"\t"<<prog<<" -g rozmiar_problemu\n";
	cout<<"\t"<<prog<<" -t rozmiar_problemu_od ile_wiecej_problemow skok_rozmiaru algorytm [liczba_probek_na_rozmiar_problemu]\n";
	cout<<"\n";
	cout<<"\t- algorytm : {1,2,3,4}\n\n";
	cout<<"\t- Plik formatowany (kolejnosc linii dowolna, nazwy odpowiendnich id inne):\n";
	cout<<"{nazwa_sali}\n{nazwa_sali_1}\n...\n{dzien/1.."<<aal::Model::DAYS_PER_WEEK<<"/} {godzina_od} {godzina_do} [{nazwa_wykladu}]\n...\n\n";
	exit(1);
}

/**
 * Main function
 */
int main(int argc, char **argv) {
	/*
	 * To know for what app has been started
	 */
	enum RunAses {DATA, GENERATE, TIME};
	/*
	 * And which algorithm is should be used
	 */
	enum Algorithms {FIRST = 1, SECOND = 2, THIRD = 3, FOURTH = 4};

	/*
	 * Local variables
	 */
	aal::Model m;
	RunAses run_as;
	Algorithms chosen_algorithm;
	int problem_size_from, how_much_more_increases_problem_size, problem_size_increase_amount, samples_amount = 1;

	// If no given parameters or too much
	if (argc < 2 || argc > 7)
		properRun(argv[0]);

	// To compare option
	std::string opt(argv[1]);
	if (opt == "-d") {
		if (argc == 3)
			// Read from file
			m.readData(argv[2]);
		else if (argc == 2)
			// Read from stdin
			m.readData();
		else
			properRun(argv[0]);

		run_as = DATA;
	} else if (opt == "-g") {
		if (argc == 3) {
			problem_size_from = atoi(argv[2]);
			// Generate data
			m.generateData(problem_size_from);
		}
		else
			properRun(argv[0]);

		run_as = GENERATE;
	} else if (opt == "-t") {
		if (argc == 6 || argc == 7) {
			problem_size_from = atoi(argv[2]);
			how_much_more_increases_problem_size = atoi(argv[3]);
			problem_size_increase_amount = atoi(argv[4]);
			chosen_algorithm = Algorithms(atoi(argv[5]));

			if (argc == 7)
				samples_amount = atoi(argv[6]);

			// If invalid values..
			if (problem_size_from < 1 || how_much_more_increases_problem_size < 0 || problem_size_increase_amount < 1 || chosen_algorithm < 1 || chosen_algorithm > 4 || samples_amount < 1)
				properRun(argv[0]);
		}
		else
			properRun(argv[0]);

		run_as = TIME;
	} else
		properRun(argv[0]);

	// If not proper read or generation
	if (run_as != TIME && (m.orders().size() == 0 || m.classrooms().size() == 0))
		properRun(argv[0]);

	// If time try
	if (run_as == TIME) {
		vector<aal::Result> results;
		vector<double> times;
		aal::Algorithm *alg;

		// Choose algorithm
		if (chosen_algorithm == FIRST)
			alg = new aal::FirstAlgorithm(m.classrooms(), m.orders());
		else if (chosen_algorithm == SECOND)
			alg = new aal::SecondAlgorithm(m.classrooms(), m.orders());
		else if (chosen_algorithm == THIRD)
			alg = new aal::ThirdAlgorithm(m.classrooms(), m.orders());
		else if (chosen_algorithm == FOURTH)
			alg = new aal::FourthAlgorithm(m.classrooms(), m.orders());

		// Generate 'table' of results
		for (int i = problem_size_from; i <= problem_size_from + how_much_more_increases_problem_size * problem_size_increase_amount; i += problem_size_increase_amount) {
			std::vector<std::pair<aal::Result, double> > tmp_results;


			std::cout<<"\n("<<((i - problem_size_from) / problem_size_increase_amount + 1)<<"/"<<(how_much_more_increases_problem_size + 1)<<") | "<<samples_amount<<" | "<<flush;
			for (int j = 0; j < samples_amount; ++j) {
				std::cout<<"."<<flush;

				// Generate new data
				m.generateData(i);

				// Initialize algorithm
				alg->init(m.classrooms(), m.orders());

				// Start timer
				aal::Timer::getInstance().start();

				// Run algorithm and get result
				aal::Result r = alg->run();

				// Stop timer
				aal::Timer::getInstance().stop();

				// Store elapsed time
				tmp_results.push_back(std::make_pair(r, aal::Timer::getInstance().end()));
			}

			// Get max time of samples
			double max_time = tmp_results.begin()->second;
			int max_time_result_index = 0;

			for (unsigned int j = 0; j < tmp_results.size(); ++j)
				if (tmp_results[j].second > max_time) {
					max_time = tmp_results[j].second;
					max_time_result_index = j;
				}


			// Store worst elapsed time and its result
			times.push_back(max_time);
			// Store result
			results.push_back(tmp_results[max_time_result_index].first);

			tmp_results.clear();
		}

		/*
		 * Generate 'table'
		 */
		cout<<"\n";
		cout.width(10); cout<<"n"<<" ";
		cout.width(10); cout<<"t(n)[ms]"<<" ";
		cout.width(10); cout<<"q(n)"<<"\n";
		// Choose median value
		int tmp = problem_size_increase_amount * how_much_more_increases_problem_size;
		tmp = (how_much_more_increases_problem_size % 2 != 0 ? tmp - problem_size_increase_amount : tmp);
		int median = (problem_size_from * 2 + tmp) / 2;

		for (unsigned int i = 0; i < results.size(); ++i) {
			// Calculate q(n)
			//			double q = (times[i] * alg->getTn(median) ) / (alg->getTn(i + problem_size_from) * (times[median - problem_size_from] == 0 ? 0.000001 : times[median - problem_size_from]));
			double q = (times[i] * alg->getTn(median) ) / (alg->getTn(i * problem_size_increase_amount + problem_size_from) * (times[(median - problem_size_from) / problem_size_increase_amount] == 0 ? 0.000001 : times[(median - problem_size_from) / problem_size_increase_amount]));

			cout.width(10); cout<<right<<i * problem_size_increase_amount + problem_size_from<<" ";
			cout.width(10); cout<<right<<times[i]<<" ";
			cout.width(10); cout<<right<<q<<"\n";
		}

		// Cleaning
		delete alg;

	} else if (run_as == GENERATE || run_as == DATA) {
		/*
		 * Run algorithms, show results&times and save results into files
		 */

		// First
		aal::FirstAlgorithm first(m.classrooms(), m.orders());

		aal::Timer::getInstance().start();

		aal::Result r1 = first.run();

		aal::Timer::getInstance().stop();

		cout<<"Occupancy: "<<r1.occupancy();
		cout<<"\nTime: "<<aal::Timer::getInstance().end()<<" [ms]\n\n";

		r1.saveToFile("result_1.html");

		// Second
		aal::SecondAlgorithm second(m.classrooms(), m.orders());

		aal::Timer::getInstance().start();

		aal::Result r2 = second.run();

		aal::Timer::getInstance().stop();

		cout<<"Occupancy: "<<r2.occupancy();
		cout<<"\nTime: "<<aal::Timer::getInstance().end()<<" [ms]\n\n";

		r2.saveToFile("result_2.html");

		// If too much data, don not start brute force, only if generate with low problem size
		if (run_as == GENERATE && problem_size_from < 3) {
			aal::ThirdAlgorithm third(m.classrooms(), m.orders());

			aal::Timer::getInstance().start();

			aal::Result r3 = third.run();

			aal::Timer::getInstance().stop();

			cout<<"Occupancy: "<<r3.occupancy();
			cout<<"\nTime: "<<aal::Timer::getInstance().end()<<" [ms]\n\n";

			r3.saveToFile("result_3.html");
		}

		// Fourth
		aal::FourthAlgorithm fourth(m.classrooms(), m.orders());

		aal::Timer::getInstance().start();

		aal::Result r4 = fourth.run();

		aal::Timer::getInstance().stop();

		cout<<"Occupancy: "<<r4.occupancy();
		cout<<"\nTime: "<<aal::Timer::getInstance().end()<<" [ms]\n\n";

		r4.saveToFile("result_4.html");
	}

	cout<<"\n";

	return 0;
}
