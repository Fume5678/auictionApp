#include <fstream>
#include <algorithm>
#include <iostream>
#include <exception>
#include "TraderRepository.h"
#include "Item.h"
#include "Trader.h"

using namespace nlohmann;

void TraderRepository::saveItem(std::string traderName, Item item)
{
    readBd();
    try {
        json traderBag;
        for (auto& tr : j["traders"]) {
            if (tr["name"] == traderName) {
                json newItem;
                newItem["name"] = item.getName();
                newItem["boughtCost"] = item.getCost();

                tr["bag"].push_back(newItem);
            }
        }
    }
    catch (std::exception &e) {
        std::cout << "ERROR::TraderRepository: Failed save item" << std::endl;
        throw std::invalid_argument(e.what());
    }
    writeBd();
    
}

void TraderRepository::saveTrader(Trader* trader)
{
    readBd();
    json traders = j["traders"];

    for (auto tr : traders) {
        if (tr["name"] == trader->getName()) {
            throw std::exception("Trader name must be unique");
        }
    }

    json newTrader;
    newTrader["name"] = trader->getName();
    newTrader["cache"] = trader->getCache();
    newTrader["bag"] = json::array();

    traders.push_back(newTrader);

    j["traders"] = traders;
    
    writeBd();
}

void TraderRepository::removeItem(std::string traderName, std::string itemName)
{
    readBd();
    try {
        json traderBag = j["traders"][traderName]["bag"];
        
        for (int i = 0; i < traderBag; ++i) {
            if (traderBag[i]["name"] == itemName) {
                traderBag.erase(i);
            }
        }

        j["traders"][traderName]["bag"] = traderBag;
    }
    catch (std::exception& e) {
        std::cout << "ERROR::TraderRepository: Failed save item" << std::endl;
        throw std::invalid_argument(e.what());
    }
    writeBd();
}

void TraderRepository::removeUserByUsername(std::string traderName)
{
    readBd();
    try {
        json newTraders;

        for (auto tr : j["traders"]) {
            if (tr["name"] != traderName) {
                newTraders.push_back(tr);
            }
        }
        j["traders"] = newTraders;
    }
    catch (std::exception& e) {
        std::cout << "ERROR::TraderRepository: Failed remove user by username" << std::endl;
        throw std::invalid_argument(e.what());
    }
    writeBd();
}

std::vector<Item> TraderRepository::findAllItemsByTraderName(std::string traderName)
{
    readBd();
    try {
        json traderBag = j["traders"][traderName]["bag"];
        std::vector<Item> items;

        
        for (auto jitem : traderBag) {
            std::string name = jitem["name"];
            double cost = jitem["boughtCost"];
            Item item(name, cost);
            items.push_back(item);
        }

        return items;
    }
    catch (std::exception& e) {
        std::cout << "ERROR::TraderRepository: Failed find all item by trade name" << std::endl;
        throw std::invalid_argument(e.what());
    }

}

Trader* TraderRepository::findUserByTraderName(std::string traderName)
{
    readBd();
    try {
        json jtrader = j["traders"][traderName];
        Trader* trader = new Trader;

        trader->setName(jtrader["name"]);
        trader->setCache(jtrader["cache"]);
        
        json traderBag = jtrader["bag"];
        for (auto jitem : traderBag) {
            std::string name = jitem["name"];
            double cost = jitem["boughtCost"];
            Item item(name, cost);
            trader->addItem(item);
        }

        return trader;
    }
    catch (std::exception& e) {
        std::cout << "ERROR::TraderRepository: Failed find user by trader name" << std::endl;
        throw std::invalid_argument(e.what());
    }
}

std::vector<Trader*> TraderRepository::findAllUser()
{
    readBd();
    try {
        json jtraders = j["traders"];
        std::vector<Trader*> traders;

        for (auto jtrader : jtraders) {
            

            std::string name = jtrader["name"];
            double cache = jtrader["cache"];

            Trader* newTrader = new Trader;
            newTrader->setName(name);
            newTrader->setCache(cache);

            json traderBag = jtrader["bag"];
            for (auto jitem : traderBag) {
                std::string name = jitem["name"];
                double cost = jitem["boughtCost"];
                Item item(name, cost);
                newTrader->addItem(item);
            }
            traders.push_back(newTrader);
        }

        return traders;
    }
    catch (std::exception& e) {
        std::cout << "ERROR::TraderRepository: Failed find all user: " << e.what() << std::endl;
    }
}

void TraderRepository::writeBd()
{
    try {
        // Open file
        std::ofstream fout(dbPath);
        if (!fout.is_open()) {
            throw std::ifstream::failure("Failed open " + dbPath);
        }

        fout << j;
        fout.close();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::StorageController: " << e.what() << std::endl;
        throw std::runtime_error(e.what());
    }
    catch (std::exception& e) {
        std::cout << "ERROR::StorageController: " << e.what() << std::endl;
        throw std::runtime_error("Failed to read Bd");
    }
}

void TraderRepository::readBd()
{
    try {
        // Open file
        std::ifstream fin(dbPath);
        if (!fin.is_open()) {
            throw std::ifstream::failure("Failed open " + dbPath);
        }

        // Json read
        fin >> j;
        fin.close();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::StorageController: " << e.what() << std::endl;
        throw std::runtime_error(e.what());
    }
    catch (std::exception& e) {
        std::cout << "ERROR::StorageController: " << e.what() << std::endl;
        throw std::runtime_error("Failed to read Bd");
    }
}
