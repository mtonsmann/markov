#ifndef MODEL_H
#define MODEL_H

#include <string>

class brute_model {
public:
	brute_model(std::string s, int k);
	std::string generate(int size);

private:
	std::string data;
	int order;
};

#endif

