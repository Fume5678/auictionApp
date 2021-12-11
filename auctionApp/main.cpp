// managerApp.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "AuctionSession.h"
#include "TraderRepository.h"
#include "Trader.h"

void printMenu() {
    std::stringstream sstr;
    sstr << "Auctioner menu\n";
    sstr << "[1] \tStart auction\n";
    sstr << "[2] \tShow items\n";
    sstr << "[3] \tAdd trader\n";
    sstr << "[4] \tRemove trader\n";
    sstr << "[5] \tShow traders\n";
    sstr << "[-1] \tExit\n";
    sstr << "[-2] \tClear\n";
    std::cout << sstr.str();
}

int main() {

    AuctionSession session;
    int cmd = 0;

    printMenu();
    while (cmd != -1) {
        std::cout << "\n$ ";
        std::cin >> cmd;

        switch (cmd) {
            case (1): {
                session.runAuction();
                break;
            }
            case (2): {
                session.showAllItems();
                break;
            }
            case (3): {
                std::string name;
                double cache;
                std::cout << "\nInput username and cache of new trader (ex. Igor 1234): ";
                std::cin >> name >> cache;
                TraderRepository* traderRepository = new TraderRepository;
                Trader* newTrader = new Trader;
                newTrader->setName(name);
                newTrader->setCache(cache);
                try {
                    traderRepository->saveTrader(newTrader);
                    std::cout << "INFO::Trader added";
                }
                catch (std::exception& e) {
                    std::cout << "ERROR::main: Failed to add user: " << e.what() << std::endl;
                }
                delete newTrader;
                delete traderRepository;
                break;
            }
            case (4): {
                TraderRepository* traderRepository = new TraderRepository;
                std::string name;
                double cache;
                std::cout << "\nInput username for remove: ";
                std::cin >> name;
                try {
                    traderRepository->removeUserByUsername(name);
                }
                catch (std::exception& e) {
                    std::cout << "ERROR::main: Failed to remove user: " << e.what() << std::endl;
                }
                delete traderRepository;
                break;
            }
            case (5): {
                TraderRepository* traderRepository = new TraderRepository;
                std::vector<Trader*> traders = traderRepository->findAllUser();
                for (auto tr : traders) {
                    std::cout << "   -Name: " << tr->getName() << "\n    Cache: " << tr->getCache() << "\n    Bag:\n";
                    for (auto item : tr->getBag()) {
                        std::cout << "        Name: " << item.getName() << std::endl;
                    }
                }
                delete traderRepository;
                break;
            }
            case (-1): {
                break;
            }
            case (-2): {
                // Вы вроде говорили, что для мака надо
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                printMenu();
                break;
            }
            default: {
                std::cout << "!Unrecognized command";
            }
        }
    }
}