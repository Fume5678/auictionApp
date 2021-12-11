#include "Auctioner.h"
#include "AuctionerRepository.h"
#include "Item.h"
#include <exception>

Auctioner::Auctioner()
{
	this->name = "Auctioner";
	auctionerRepository = new AuctionerRepository;
}

Auctioner::Auctioner(std::string name)
{
	this->name = name;
	auctionerRepository = new AuctionerRepository;
}

void Auctioner::addItem(Item item)
{
	try {
		auctionerRepository->save(item);
		std::cout << "INFO::Auctioner:: item saved " << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR::Auctioner::Failed to save item: " << e.what() << std::endl;
	}
}

void Auctioner::addItem(std::string name, int cost)
{
	Item item(name, cost);

	try {
		auctionerRepository->save(item);
		std::cout << "INFO::Auctioner:: item saved " << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR::Auctioner::failed to save item: " << e.what() << std::endl;
	}

}

void Auctioner::removeItem(std::string name)
{
	try {
		auctionerRepository->remove(name);
		std::cout << "INFO::Auctioner:: item removed" << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << "ERROR::Auctioner: " << e.what() << std::endl;
	}
}

void Auctioner::showItems()
{
	std::vector<Item> items = auctionerRepository->findAllItems();
	for (auto item : items) {
		std::cout << "  - Name: " << item.getName() << "\n    Cost: " << item.getRoundedCost() << std::endl;
	}
}

Auctioner::~Auctioner()
{
	delete auctionerRepository;
}
