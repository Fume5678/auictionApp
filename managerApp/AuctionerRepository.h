#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"

const std::string dbPath = "../database/database.json";

class Item;

class AuctionerRepository {
public:
    void              save(Item item);
    void              remove(std::string name);
    std::vector<Item> findAllItems();

private:
    nlohmann::json    j;
    std::vector<Item> items;
    void              writeBd();
    void              readBd();
};
