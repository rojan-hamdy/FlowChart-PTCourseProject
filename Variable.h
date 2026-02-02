#pragma once
#include <iostream>
using namespace std;
class Variable
{
private:
	double value;
	string name;
	bool initialized;
public:
	Variable(double value = 0, string name = "", bool init = false);
	double getvalue() const;
	void setvalue(double v);
	string getname() const;
	void setname(string str);
	bool isinitialized() const;
	void setinitialized(bool b);
};