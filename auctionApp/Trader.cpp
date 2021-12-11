#include "Trader.h"
#include "Item.h"

void Trader::setCache(double val)
{
	this->cache = val;
}

void Trader::setName(std::string name)
{
	this->name = name;
}

void Trader::addItem(Item item)
{
	bag.push_back(item);
}

double Trader::getCache()
{
	return cache;
}

const std::vector<Item>& Trader::getBag()
{
	return bag;
}

std::string Trader::getName()
{
	return name;
}
