#ifndef MARKET_ORDER_H
#define MARKET_ORDER_H

#include <string>
namespace Pricer
{

const auto BID_TYPE = 'B';
const auto ASK_TYPE = 'S';
const auto SELL_CHAR = 'S';
const auto BUY_CHAR = 'B';
const auto ADD_TYPE = 'A';
const auto REDUCE_TYPE = 'R';
const auto UNKONWN_TYPE = 'U';

class MarketOrder 
{
    public: 
        MarketOrder(std::string       id,
                    unsigned long int timestamp,
                    double            price,
                    unsigned int      size,
                    char              type);

        ~MarketOrder();


        void ReduceOrder( unsigned int amount );

        unsigned int  Size() const;
        unsigned long TimeStamp() const;
        double        Price() const;
        std::string   ID() const;
        char          OrderType() const;

    private:
        std::string m_order_id;
        unsigned int m_size_order;                                        
        unsigned long int m_timestamp;
        double m_price_limit;
        char m_order_type;
};

}
#endif
