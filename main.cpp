#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "model.h"

using namespace std;

void init_random() {
	// use this to get the same random sequence every time
//	srand(1234);

	// use this to get a different random sequence every time
	time_t t = time(NULL);
	srand(t);
}

int main(int argc, char* argv[]) {
	string infile;
	int k;
	int sz;
	string model_type;

	// allow command line "markov filename k sz model", or partial
	// command line, prompting for missing items
	if (argc > 1) infile = string(argv[1]);
	else {
		cout << "Enter a filename: ";
		cin >> infile;
	}

	if (argc > 2) k = atoi(argv[2]);
	else {
		cout << "Enter Markov model order (k): ";
		cin >> k;
	}

	if (argc > 3) sz = atoi(argv[3]);
	else {
		cout << "Enter size of output text: ";
		cin >> sz;
	}

	if (argc > 4) model_type = string(argv[4]);
	else {
		cout << "Enter method (brute, map, word): ";
		cin >> model_type;
	}


	// get text from input file
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << infile << "\"!" << endl;
		return -1;
	}
	// get all strings; extra whitespace will be ignored
	ostringstream text;
	while (!fin.eof()) {
		string s;
		fin >> s;
		text << s << ' ';
	}
	fin.close();

	// initialize random number generator
	init_random();

	// create model and output result
	cout << "RESULT:" << endl;
	if (model_type == "brute") {
		brute_model model(text.str(), k);

		clock_t t1, t2;
		t1 = clock();
		string result = model.generate(sz);
		t2 = clock();
		cout << result << endl;
		cout << "Generated " << sz << " characters in " << (t2 - t1)/double(CLOCKS_PER_SEC) << " seconds." << endl;

	} else if (model_type == "map") {
		map_model map_model(text.str(), k);

		clock_t t1, t2;
		t1 = clock();
		string result = map_model.generate(sz);
		t2 = clock();
		cout << result << endl;
		cout << "Generated " << sz << " characters in " << (t2 - t1)/double(CLOCKS_PER_SEC) << " seconds." << endl;

	} else {
		cout << "That model is not yet implemented, sorry." << endl;
		return -1;
	}

	return 0;
}
