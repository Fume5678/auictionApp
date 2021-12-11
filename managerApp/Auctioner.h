#pragma once

#include <iostream>


class AuctionerRepository;
class Item;

class Auctioner
{
public:
	Auctioner();
	Auctioner(std::string name);
	~Auctioner();
	
	void addItem(Item name);
	void addItem(std::string name, int cost);
	void removeItem(std::string name);
	void showItems();
	
private:
	AuctionerRepository* auctionerRepository;
	std::string name;
};

