#ifndef MARKET_ORDER_H
#define MARKET_ORDER_H

#include <string>
namespace Pricer
{

const char BID_TYPE = 'B';
const char ASK_TYPE = 'S';
const char SELL_CHAR = 'S';
const char BUY_CHAR = 'B';
const char ADD_TYPE = 'A';
const char REDUCE_TYPE = 'R';
const char UNKONWN_TYPE = 'U';

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
