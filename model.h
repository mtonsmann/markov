#ifndef MODEL_H
#define MODEL_H

#include "map.h"
#include "vector.h"
#include <string>

class brute_model {
public:
	brute_model(std::string s, int k);
	std::string generate(int size);

private:
	std::string data;
	int order;
};

class map_model {
public:
	map_model(std::string s, int k);
	std::string generate(int size);

private:
	std::string data;
	int order;
	std::string mapdata;
	Map<std::string, Vector<char> > map;
};

class word_model {
public:
	word_model(std::string s, int k);
	std::string generate(int size);
	Vector<std::string> subVec(int a, int b);
	Vector<std::string> stov(std::string s);

	// overloads < to allow for maps of Vector<string>
	friend bool operator <(const Vector<std::string> &a; const Vector<std::string> &b);

private:
	int order;
	Vector<std::string> mapdata;
	Vector<std::string> wrap;
	Map<Vector<std::string>, Vector<std::string> > map;
	istringstream iss(char c);
	Vector<std::string> data;
};

#endif
