#include "AuctionerRepository.h"
#include "Item.h"
#include <fstream>
#include <algorithm>

using namespace nlohmann;

void AuctionerRepository::save(Item item) {
    readBd();
    auto founded =
        std::find_if(items.begin(), items.end(), [&item](Item a) -> bool {
            return a.getName() == item.getName();
        });

    if (founded != items.end()) {
        items.erase(founded);
    }
    items.push_back(item);
    writeBd();
}

void AuctionerRepository::removeItem(std::string name)
{
	readBd();
	auto founded = std::find_if(items.begin(), items.end(), [&name](Item a)->bool {
		return a.getName() == name;
		});

	if (founded != items.end()) {
		items.erase(founded);
	}
	else {
		throw std::invalid_argument("Item not found");
	}
	writeBd();
}

std::vector<Item> AuctionerRepository::findAllItems()
{
	readBd();
	return items;
}

void AuctionerRepository::writeBd()
{
	try {
		// Open file
		std::ofstream fout(dbPath);
		if (!fout.is_open()) {
			throw std::ifstream::failure("Failed open " + dbPath);
		}

		j["auctioner"]["items"].clear();
		
		// Json parse
		for (auto item : items) {
			json jitem; 
			jitem["name"] = item.getName();
			jitem["startCost"] = item.getCost();
			j["auctioner"]["items"].push_back(jitem);
		}

		fout << j;
		fout.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::AuctionerRepository: " << e.what() << std::endl;
		throw std::runtime_error(e.what());
	}
	catch (std::exception& e) {
		std::cout << "ERROR::AuctionerRepository: " << e.what() << std::endl;
		throw std::runtime_error("Failed to read Bd");
	}
}

void AuctionerRepository::readBd()
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

		// Json parse
		items.clear();
		for (auto item : j["auctioner"]["items"]) {
			json data = item["name"];
			std::string name = data.get<std::string>();
			data = item["startCost"];
			float cost = data.get<double>();
			items.push_back(Item(name, cost));
		}
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::AuctionerRepository: " << e.what() << std::endl;
		throw std::runtime_error(e.what());
	}
	catch(std::exception& e){
		std::cout << "ERROR::AuctionerRepository: " << e.what() << std::endl;
		throw std::runtime_error("Failed to read Bd");
	}
}

