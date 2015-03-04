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
	//cout << "test 118" << endl;
	words++; //adds final words for missing space
	while (!iss.eof()) {
		string val;
		iss >> val;
		data.add(val);
	}
	//cout << "test 125" << endl;

	// Simulates a wrap around
	mapdata = data;
	wrap = subVec(data, 0, k);
	for (string str : wrap) {
		mapdata.add(str);
	}
	//cout << "test 133" << endl;

	// populates the map with with the grams and following words
	Vector<string> gram;
	for (int i = 0; i < data.size(); i++) {
		Vector<string> following;
		gram = subVec(mapdata, i, i+order);


		following.add(mapdata[i+order]);
		//cout << "test 142" << endl;

		if (!map.containsKey(gram)) {
			cout << gram.toString() << endl;
			cout << "Following: " << following.toString() << endl;
			map[gram] = following;
			cout << "Partial map: " << map.toString() << endl;
			//cout << "test 146" << endl;
		} else {
			//cout << "test 148" << endl;

			// copies current values for key and adds new value
			Vector<string> temp;
			temp = map.get(gram);
			cout << temp.toString() << endl;
			//cout << "test 152" << endl;
			for (int j = 0; j < temp.size(); j++) {
				following.add(temp[j]);
			}
			//cout << "test 154" << endl;
			cout << gram.toString() << endl;
			cout << "Following: " << following.toString() << endl;
			map[gram] =	 following;
		}
	}
	//cout << "test 156" << endl;
}

string word_model::generate(int sz) {
	cout << map.toString() << endl;

	// copy first k words to back to simulate wrap-around
	Vector<string> working_data = data;
	for (string str : wrap) {
		working_data.add(str);
	}
	cout << 172 << endl;

	// pick random k-character substring as initial seed
	int start = rand() % data.size();
	Vector<string> seed = subVec(working_data, start, start + order);
	cout << 177 << endl;
	cout << seed.toString() << endl;

	string answer;
	Vector<string> answerVec;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		// sets next to random string returned from map
		cout << 186 << endl;
		cout << map.get(seed).toString() << endl;
		string next = map.get(seed)[rand() % map.get(seed).size()];
		cout << 188 << endl;
		answerVec.add(next);
		seed.remove(0);
		seed.add(next);
		cout << 189 << endl;
	}
	answer = data[start];
	cout << "test 181" << endl;
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
