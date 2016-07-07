#ifndef BOOK_PRICER_H
#define BOOK_PRICER_H

#include <string>
#include <unordered_map>
#include <set>
#include <memory>

#include "MarketOrder.h"

namespace Pricer 
{


// Functors used in the insertion process of the sets
struct GreaterThanComparator 
{
    bool operator()(const std::shared_ptr<MarketOrder> &lhs, const std::shared_ptr<MarketOrder> &rhs) const
    {
        return lhs->Price() > rhs->Price();
    }
};

struct LessThanComparator 
{
    bool operator()(const std::shared_ptr<MarketOrder> &lhs, const std::shared_ptr<MarketOrder> &rhs) const
    {
        return lhs->Price() < rhs->Price();
    }
};


class LimitOrderBook
{
    public:
        LimitOrderBook(unsigned int target_size);
        ~LimitOrderBook();

        double AddBidOrderToBook(std::shared_ptr<MarketOrder> order);
        double AddAskOrderToBook(std::shared_ptr<MarketOrder> order);
        double ReduceBidOrderFromBook(std::string id, unsigned int balance);
        double ReduceAskOrderFromBook(std::string id, unsigned int balance);

        double LatestEarnings();
        double LatestExpense();

        char GetOrderTypeFromID(std::string order_id);

    private:

        void insertOrder(char type,
                         std::shared_ptr<MarketOrder> order);

        double satisfyMaximizedOrder(unsigned int how_many);
        double satisfyMinimizedOrder(unsigned int how_many);

        std::multiset<std::shared_ptr<MarketOrder>, LessThanComparator>    m_askOrders;
        std::multiset<std::shared_ptr<MarketOrder>, GreaterThanComparator> m_bidOrders;

        std::unordered_map< std::string, std::shared_ptr<MarketOrder> > m_active_orders; 

        unsigned int m_available_bids;
        unsigned int m_available_asks;

        unsigned int m_target_size;

        double m_latest_expense;
        double m_latest_earnings;
    
};

}
#endif
