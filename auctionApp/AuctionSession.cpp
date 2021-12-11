#include "AuctionSession.h"
#include "TraderRepository.h"
#include "AuctionerRepository.h"
#include "Item.h"
#include "Trader.h"
#include <map>

AuctionSession::AuctionSession()
{
	traderRepository = new TraderRepository;
	auctionerRepository = new AuctionerRepository;
}

void AuctionSession::showAllItems()
{
	items = auctionerRepository->findAllItems();
	std::cout << ">>> All items of current auction:\n";
	for (auto item : items) {
		std::cout << "   -Name: " << item.getName() << "\n    Cost: " << item.getCost() << "!\n";
	}
}

void AuctionSession::runAuction()
{
	items = auctionerRepository->findAllItems();
	traders = traderRepository->findAllUser();
	while (!items.empty()) {
		std::cout << "\n>>> A lot is being played: " << items.front().getName() << ". Start cost: " << items.front().getCost() << "!";
		runRound();
		items.erase(items.begin());
	}
	std::cout << ">>> Auction is end\n";
}

void AuctionSession::runRound()
{
	Item item = items.front();
	//std::map<Trader*, double> bets;
	std::pair<Trader*, double> maxBet = {nullptr, item.getCost()};

	for (auto trader : traders) {
		std::cout << std::endl << trader->getName() << "(" << trader->getCache() << ")" << " makes a bet (-1 for skip)\n$ ";
		double bet = 0;

		while (std::cin >> bet) {
			if (bet > trader->getCache()) {
				std::cout << "Failed: Bet is grater trader cache\n";
				continue;
			}
			break;
		}
		if (bet > maxBet.second) {
			maxBet.first = trader;
			maxBet.second = bet;
		}
	}

	if (maxBet.first != nullptr) {
		maxBet.first->addItem(item);
		maxBet.first->setCache(maxBet.first->getCache() - maxBet.second);
		try {
			item.setCost(maxBet.second);
			traderRepository->saveItem(maxBet.first->getName(), item);
			auctionerRepository->removeItem(item.getName());
		}
		catch (std::exception& e) {
			std::cout << "ERROR::Run Round: Failed to save: " << e.what();
		}
		std::cout << "\n>>> " << maxBet.first->getName() << " is won " << item.getName() << "!\n";
	}
	else {
		std::cout << "\n>>> No one is won " << item.getName() << "!\n";
	}

}

AuctionSession::~AuctionSession()
{
	delete traderRepository;
	delete auctionerRepository;

	while (!traders.empty()) {
		auto tmp = traders.back();
		traders.pop_back();
		delete tmp;
	}
}
