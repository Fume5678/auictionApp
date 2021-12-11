#include "Item.h"

Item::Item(std::string name, double cost)
{
	this->name = name;
	this->cost = cost;
}

void Item::setName(std::string name)
{
	this->name = name;
}

void Item::setCost(double val)
{
	this->cost = val;
}

std::string Item::getName()
{
	return name;
}

double Item::getCost()
{
	return cost;
}

double Item::getRoundedCost()
{
	return round(cost * 100)/100;
}

bool operator==(Item a, Item b)
{
	return a.name == b.name;
}
