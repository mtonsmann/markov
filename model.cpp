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

//Part II: Markov Models for Words
// overloads < allowing use of maps of Vector<strings>
bool operator <(const Vector<std::string> &a, const Vector<std::string> &b) {
	if (a.size() == b.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] < b[i]) {
				return true;
			} else if (a[i] > b[i]) {
				return false;
			}
		}
		return false;
	} else {
		cout << "something is wrong" << endl;
	}
}


//word generator using maps
word_model::word_model(string s, int k) {
	order= k;

	// creates vector "data" from s
	std::istringstream iss (s);
	int words = 0;
	for (char c : s) {
		if (c == ' ') {
			words++;
		}
	}
	words++; //adds final words for missing space
	while (!iss.eof()) {
		string val;
		iss >> val;
		data.add(val);
	}

	// Simulates a wrap around
	mapdata = data;
	wrap = subVec(data, 0, k);
	for (string str : wrap) {
		mapdata.add(str);
	}

	// populates the map with with the grams and following words
	Vector<string> gram;
	for (int i = 0; i < data.size(); i++) {
		Vector<string> following;
		gram = subVec(mapdata, i, i+order);


		following.add(mapdata[i+order]);

		if (!map.containsKey(gram)) {
			map.put(gram, following);

		} else {
			// copies current values for key and adds new value
			Vector<string> temp;
			temp = map.get(gram);
			for (int j = 0; j < temp.size(); j++) {
				following.add(temp[j]);
			}
			map[gram] =	 following;
		}
	}
}

string word_model::generate(int sz) {

	// copy first k words to back to simulate wrap-around
	Vector<string> working_data = data;
	for (string str : wrap) {
		working_data.add(str);
	}

	// pick random k-character substring as initial seed
	int start = rand() % data.size();
	Vector<string> seed = subVec(working_data, start, start + order);

	string answer;
	Vector<string> answerVec;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		// sets next to random string returned from map
		string next = map.get(seed)[rand() % map.get(seed).size()];
		answerVec.add(next);
		seed.remove(0);
		seed.add(next);
	}
	answer = data[start];

	for (int i = 1; i < answerVec.size(); i++) {
		answer += " " + answerVec[i];
	}
	return answer;
}

Vector<string> word_model::subVec(Vector<string> given, int a, int b) {
	Vector<string> vec;
	for (int i = a; i < b; i++) {
		vec.add(given[i]);
	}
	return vec;
}
