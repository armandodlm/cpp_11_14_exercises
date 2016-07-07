#include "MarketOrder.h"
#include <iostream>


namespace Pricer
{

MarketOrder::MarketOrder(std::string id,
                         unsigned long int timestamp,
                         double            price,
                         unsigned int      size,
                         char              type):
                         m_order_id( id ),
                         m_timestamp( timestamp ),
                         m_price_limit( price ),
                         m_size_order( size ),
                         m_order_type( type )
{
}

MarketOrder::~MarketOrder()
{
}

/*
    ReduceOrder

    This function reduces the order size by amount
    If the amount is greater than the original size,
    the size is zeroed out
    
*/
void MarketOrder::ReduceOrder( unsigned int amount )
{
    if( amount > m_size_order )
        m_size_order = 0;
    else
        m_size_order -= amount;
    
}

/*
    Size
    
    Public accessor for the order size
*/
unsigned int MarketOrder::Size() const
{
    return m_size_order;
}

/*
    TimeStamp

    Public accessor for the time stamp value
    
*/
unsigned long MarketOrder::TimeStamp() const
{
    return m_timestamp;
}

/*
    Price

    Public accessor for the price of a share in this order

*/
double MarketOrder::Price() const
{
    return m_price_limit;
}

/*
    ID
    
    Public accessor for the id of the order
*/
std::string MarketOrder::ID() const
{
    return m_order_id;
}

/*
    OrderType
    
    Public accessor for the order type (Bid or Ask)
*/
char MarketOrder::OrderType() const
{
    return m_order_type;
}

}
