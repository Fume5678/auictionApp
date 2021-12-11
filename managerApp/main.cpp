// managerApp.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "Auctioner.h"
#include "Item.h"

void printMenu() {
    std::stringstream sstr;
    sstr << "Auctioner menu\n";
    sstr << "[1] \tAdd Item menu\n";
    sstr << "[2] \tRemove item menu\n";
    sstr << "[3] \tShow items\n";
    sstr << "[-1] \tExit\n";
    sstr << "[-2] \tClear\n";
    std::cout << sstr.str();
}

int main() {
    Auctioner auctioner("name1");
    int       cmd = 0;

    printMenu();
    while (cmd != -1) {
        std::cout << "\n>> ";
        std::cin >> cmd;

        switch (cmd) {
            case (1): {
                std::cout << "Enter name and cost of new item (ex: Bucket 123.32): ";
                std::string name;
                double      cost;
                std::cin >> name >> cost;
                Item item{ name, cost };
                auctioner.addItem(item);
                break;
            }
            case (2): {
                std::cout << "Enter name of item: ";
                std::string name; 
                std::cin >> name;
                auctioner.removeItem(name);
                break;
            }
            case (3): {
                auctioner.showItems();
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