#pragma once
#include <vector>

class Item;
class AuctionerRepository;
class TraderRepository;
class Trader;

class AuctionSession {
public:
    AuctionSession();
    void showAllItems();
    void runAuction();
    ~AuctionSession();

private:
    void runRound();
    std::vector<Item>    items;
    std::vector<Trader*> traders;
    AuctionerRepository* auctionerRepository;
    TraderRepository*    traderRepository;
};