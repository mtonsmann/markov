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
	std::string subWords(std::string data, int a, int b);

private:
	std::string data;
	int order;
	std::string mapdata;
	Map<std::string, Vector<std::string> > map;
	istringstream iss(char c);
};

#endif
