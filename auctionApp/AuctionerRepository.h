#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"


class Item;

class AuctionerRepository
{
public:
	void save(Item item);
	void removeItem(std::string name);
	std::vector<Item> findAllItems();
private:
	const std::string dbPath = "../database/database.json";
	nlohmann::json j;
	std::vector<Item> items;
	void writeBd();
	void readBd();
};

