#pragma once
#include <vector>
#include <string>
#include "Item.h"

class Item;

class Trader
{
public:
	void setCache(double val);
	void setName(std::string name);
	void addItem(Item item);


	double getCache();
	const std::vector<Item>& getBag();
	std::string getName();
	

private:
	double cache;
	std::string name;
	std::vector<Item> bag;
};

