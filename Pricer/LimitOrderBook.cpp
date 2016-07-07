#include <iostream>
#include <memory>
#include <exception>
#include <sstream>
#include <algorithm>

#include "LimitOrderBook.h"

namespace Pricer 
{

using std::cout;
using std::endl;

LimitOrderBook::LimitOrderBook(unsigned int target_size): m_target_size( target_size ),
                                                          m_latest_expense( 0 ),
                                                          m_latest_earnings( 0 )
{
}


LimitOrderBook::~LimitOrderBook()
{
}


/*
    insertOrder
        Private function that places the pointer of the market order inside the appropriate set
        (ask set, or bid set) and an unordered map for quick access

        type  - character, S or B used to determine the right set to store the order in
        order - The shared pointer to the order to be stored 
*/

void LimitOrderBook::insertOrder(char type, std::shared_ptr<Pricer::MarketOrder> order)
{
        auto insert_result = m_active_orders.insert(std::make_pair( order->ID(), order ));

        if( insert_result.second && type == Pricer::BID_TYPE )
        {
            m_bidOrders.insert( order );
            m_available_bids += order->Size();

        }else if(insert_result.second && type == Pricer::ASK_TYPE){

            m_askOrders.insert( order );
            m_available_asks += order->Size();

        }
}

/*
    satisfyMaximizedOrder

        Private function that iterates over an ordered set (max item first)
        and calculates the total of selling shares_needed
        
        shares_needed - number of shares to look for in the set
        
        returns the estimated earnings from selling shares_needed
*/
double LimitOrderBook::satisfyMaximizedOrder(unsigned int shares_needed)
{

    double cumulative_total = 0;

    if( shares_needed <= m_available_bids )
    {
        auto set_iter = m_bidOrders.begin(); 
        unsigned int current_size = 0;

        while(shares_needed > 0)
        {
            current_size = (*set_iter)->Size();
            if(current_size > shares_needed)
            {
                cumulative_total += shares_needed * (*set_iter)->Price();
                break;
            }else
            {
                cumulative_total += current_size * (*set_iter)->Price();
                shares_needed -= current_size;

                set_iter++;
                
                if( set_iter == m_bidOrders.end() ) break;

            }
        }
    }       

    return cumulative_total;
}


/*
    AddBidOrderToBook

    Public function that places a bid order in the bid set and finds a maximized 
    sell matching the number of shares in target-size   

    returns the maximized cumulative total of the sell
*/
double LimitOrderBook::AddBidOrderToBook(std::shared_ptr<Pricer::MarketOrder> order)
{
    unsigned int would_be_count = m_available_bids + order->Size();
    double cumulative_total = 0;
    
    insertOrder( Pricer::BID_TYPE, order);

    if( would_be_count >= m_target_size )
    {   
        cumulative_total = satisfyMaximizedOrder(m_target_size);
    }else
    {
        cumulative_total = 0;
    }

    m_latest_earnings = cumulative_total;

    return cumulative_total;
}

/*
   satisfyMinimizedOrder 

        Private function that iterates over an ordered set (min item first)
        and calculates the total of selling shares_needed
        
        shares_needed - number of shares to look for in the set
        
        returns the estimated earnings from buying shares_needed
*/
double LimitOrderBook::satisfyMinimizedOrder(unsigned int shares_needed)
{
    double cumulative_total = 0;

    if( shares_needed <= m_available_asks)
    {

        auto set_iter = m_askOrders.begin(); 
        unsigned int current_size = 0;

        while(shares_needed > 0)
        {
            current_size = (*set_iter)->Size();
            if(current_size > shares_needed)
            {
                cumulative_total += shares_needed * (*set_iter)->Price();
                break;
            }else
            {
                cumulative_total += current_size * (*set_iter)->Price();
                shares_needed -= current_size;

                set_iter++;

                if( set_iter == m_askOrders.end() ) break;
            }
        }
    }

    return cumulative_total;
}


/*
    AddAskOrderToBook

    This function places a ask order in the ask set and finds finds a minimized 
    buy matching the number of shares in target-size   

    returns the minimized cumulative total of the sell

*/
double LimitOrderBook::AddAskOrderToBook(std::shared_ptr<MarketOrder> order)
{
    unsigned int would_be_count = m_available_asks + order->Size();
    double cumulative_total = 0;

    insertOrder( Pricer::ASK_TYPE , order);

    if( would_be_count >= m_target_size )
    {
        cumulative_total = satisfyMinimizedOrder(m_target_size);
    } else
    {
        cumulative_total = 0;
    }

    m_latest_expense = cumulative_total;

    return cumulative_total;
}


/*
    ReduceBidOrderFromBook
    
    This function finds the order in the unordered map holding all the orders
    and reduces its size. 
    If the amount to reduce by is greater than the size of the order, then the
    order is also found in the bid set and both entries (map and set) are deleted.
    After the changes are made, the maximized sell is calculated and returned.

    If for some reason the ID is not present in any of the containers, 
    we simply return 0 for earnings

        id     - The ID of the order to reduce
        amount - The amount to reduce the order by

    returns the earnings of a maximized sell

*/
double LimitOrderBook::ReduceBidOrderFromBook(std::string id, unsigned int amount)
{
    double cumulative_total = 0;

    try
    {
        auto val = m_active_orders.at(id);

        if(amount >= val->Size() )
        {
            m_available_bids -= val->Size();
            m_active_orders.erase(val->ID());

            auto order_in_set = m_bidOrders.find(val);
        
            // In case the result of "find" is a different item, iterate until we 
            // find an item that matches the ID
            while( (*order_in_set)->ID() != id && order_in_set != m_bidOrders.end())
            {
                order_in_set++;
            }
            if( order_in_set != m_bidOrders.end() )
            {
                m_bidOrders.erase(order_in_set);   
            }
        }else
        {
            val->ReduceOrder( amount );
            m_available_bids -= amount;
        }
        
        cumulative_total = satisfyMaximizedOrder(m_target_size);
        m_latest_earnings = cumulative_total;
    

    } catch(std::exception &e)
    {
    }

    return cumulative_total;
}

/*
    ReduceAskOrderFromBook

    This function finds the order in the active_orders map.
    If the amount to reduce by is greater than the size of the order, then the
    order is also found in the ask set and both entries (map and set) are deleted.
    After the changes are made, the minimized buy is calculated and returned.

    If for some reason the ID is not present in any of the containers, 
    we simply return 0 for expenses 

        id     - The ID of the order to reduce
        amount - The amount to reduce the order by

    returns the expense of a minimized buy 

*/
double LimitOrderBook::ReduceAskOrderFromBook(std::string id, unsigned int amount)
{
    double cumulative_total = 0;

    try
    {
        auto val = m_active_orders.at(id);

        if(amount >= val->Size() )
        {
            m_available_asks -= val->Size();
            m_active_orders.erase(val->ID());

            auto order_in_set = m_askOrders.find(val);

            // In case the result of "find" is a different item, iterate until we 
            // find an item that matches the ID
            while( (*order_in_set)->ID() != id && order_in_set != m_askOrders.end())
            {
                order_in_set++;
            }
            if( order_in_set != m_askOrders.end() )
            {
                m_askOrders.erase(order_in_set);   
            }

        }else
        {
            val->ReduceOrder( amount );
            m_available_asks -= amount;
        }
        
        cumulative_total = satisfyMinimizedOrder(m_target_size);
        m_latest_expense = cumulative_total;


    } catch(std::exception &e)
    {
    }
    
    return cumulative_total;
}

/*
    LatestEarnings
    
    Public function that returns the earnings from the last recorded sell
*/
double LimitOrderBook::LatestEarnings()
{
    return m_latest_earnings;
}

/*
   LatestExpense 
    
    Public function that returns the expense from the last recorded buy 
*/
double LimitOrderBook::LatestExpense()
{
    return m_latest_expense;
}

/*
    GetOrderTypeFromID
        
    Using the ID we access the order and return the type of the order
    
    returns B if it's a BID or S if it's an ASK
*/
char LimitOrderBook::GetOrderTypeFromID(std::string order_id)
{
    char type = Pricer::UNKONWN_TYPE;
    try
    {
        auto val = m_active_orders.at(order_id);
        type = val->OrderType();
        
    }catch( std::exception &e )
    {
    }
    return type;
}

}
