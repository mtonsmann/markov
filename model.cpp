#include <string>
#include <sstream>
#include <cstdlib>
#include "vector.h"
#include "model.h"

using namespace std;

// Brute force character generator
brute_model::brute_model(string s, int k) {
	data = s;
	order = k;
}

string brute_model::generate(int sz) {

	// copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);

	// pick random k-character substring as initial seed
	int start = rand() % data.length();
	string seed = working_data.substr(start, order);

	Vector<char> list;
	string answer;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		list.clear();
		int pos = working_data.find(seed);
		while (pos != string::npos && pos < data.length()) {
			char c = working_data[pos + order];
			list.add(c);
			pos = working_data.find(seed, pos+1);
		}
		char c = list[rand() % list.size()];
		answer.push_back(c);
		seed = seed.substr(1) + c;
	}

	return answer;
}

// Part I: A smarter approach
// character generator using maps
map_model::map_model(string s, int k) {
	data = s;
	order = k;

	// populates the map with the grams and following chars
	mapdata = data + data.substr(0, order); //wrap-around
	string gram;
	for (int i = 0; i < s.size(); i++) {
		Vector<char> following;
		following.add(data[i+order]);
		gram = data.substr(i, order);

		if (!map.containsKey(gram)) {
			map.put(gram, following);
		} else {
			following = map.get(gram);
			following.add(data[i+order]);
			map.put(gram, following);
		}
		//cout << data.substr(0,i) << endl;
		//cout << "gram:" << gram << "_i:" << i << "_i+order:" << i+order << "_i to i+1"<< endl;
		//cout << map.toString() << endl << endl;
	}
}

string map_model::generate(int sz) {

	// copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);

	// pick random k-character substring as initial seed
	int start = rand() % data.length();
	string seed = working_data.substr(start, order);

	string answer;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		// sets next to random char returned from map
		char next = map.get(seed)[rand() % map.get(seed).size()];
		answer += next;
		seed = seed.substr(1) + next;
	}
	return answer;
}
