#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"

class Item;
class Trader;

class TraderRepository {
public:
    void              saveItem(std::string traderName, Item item);
    void              saveTrader(Trader* trader);
    void              removeItem(std::string traderName, std::string itemName);
    void              removeUserByUsername(std::string traderName);
    std::vector<Item> findAllItemsByTraderName(std::string traderName);
    Trader*           findUserByTraderName(std::string traderName);
    std::vector<Trader*> findAllUser();

private:
    const std::string dbPath = "../database/database.json";
    nlohmann::json    j;
    void              writeBd();
    void              readBd();
};
