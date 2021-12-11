#pragma once
#include <string>
#include <cmath>

class Item
{
public:
	Item(std::string name, double cost);

	void setName(std::string name);
	void setCost(double val);

	std::string getName();
	double getCost();
	double getRoundedCost();
	friend bool operator==(Item a, Item b);

private:
	std::string name;
	double cost;
};

