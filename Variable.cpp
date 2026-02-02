#include "Variable.h"

Variable::Variable(double value, string name, bool init)
	: value(value), name(name), initialized(init)
{
}

double Variable::getvalue() const
{
	return value;
}

void Variable::setvalue(double v)
{
	value = v;
}

string Variable::getname() const
{
	return name;
}

void Variable::setname(string str)
{
	name = str;
}

bool Variable::isinitialized() const
{
	return initialized;
}

void Variable::setinitialized(bool b)
{
	initialized = b;
}
