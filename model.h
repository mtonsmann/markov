#ifndef MODEL_H
#define MODEL_H

#include "map.h"
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
	map_model(std:string s, int k);
	std::string generate(int size);

private:
	std::string data;
	int order;
	std::string mapdata;
	Map<std::string, Vector> map;
}

#endif
