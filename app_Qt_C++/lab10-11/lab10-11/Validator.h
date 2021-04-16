#pragma once
#include <string>
#include "Disciplina.h"
using std::string;

class ValidException {
	string msg;
public:
	ValidException(string s) : msg{ s } {};
	string getMessage();
};

class Validator {
public:
	void valideaza(Disciplina d);
};