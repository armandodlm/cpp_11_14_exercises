#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <string>

#include "LimitOrderBook.h"
#include "MarketOrder.h"
#include "InOutUtilities.h"

using std::stringstream;
using Pricer::LimitOrderBook;
using Pricer::MarketOrder;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

namespace Pricer
{
    const std::string USAGE_MESSAGE = "usage: pricer target-szie\n\ttarget-size is a positive integer greater than 0";
    

    /* 
     * DeduceOutput     

            exchange_type - S or B     
            book          - Reference to the book object used to get earnings or expenses
            time_stamp    - The time-stamp of the message that prompted output 
            earnings_changed -  Whether the message should contain something or nothing


        Returns a message in the expected output format
     *
     */
    inline std::string DeduceOutput(char exchange_type,
                                    LimitOrderBook &book,
                                    unsigned long time_stamp,
                                    bool earnings_changed)
    {

        std::stringstream add_output;
        double latest_balance = (exchange_type == Pricer::SELL_CHAR ? book.LatestEarnings() : book.LatestExpense() );

        if( earnings_changed )
        {
            add_output << time_stamp << " " << exchange_type << " "; 

            if( latest_balance == 0)
            {
                add_output << "NA"; 
            }else
            {
                add_output << std::setprecision( 2 ) << std::fixed << latest_balance;
            }

        } else
        {
            add_output.str("");
        }

        return add_output.str();
    }

}

int main(int argc, char **args)
{
    if( argc >= 2 )
    {
        // Check cl arguments
        stringstream target_size_str(args[1]);
        unsigned int target_size;
        target_size_str >> target_size;

        if( target_size <= 0 ){
            cerr << Pricer::USAGE_MESSAGE << endl;
            return -1;
        }

        // Variables used for parsing the input msg
        std::string order_message;

        unsigned long time_stamp;
        char add_or_remove;
        char bid_or_ask;
        unsigned int order_size;
        double limit_price;
        std::string order_id;
        bool parsed_successfully = false;


        // Variables used to determine the right output
        double last_expense = 0;
        double last_earnings = 0;
        double new_expense = 0;
        double new_earnings = 0;

        bool earnings_changed = false;
        std::string output;


        LimitOrderBook pricer(target_size);

        while(!std::getline( cin, order_message ).eof())
        {
            // Passing references, values are updated
            parsed_successfully = Pricer::ParseInput(order_message,
                                                     time_stamp,
                                                     add_or_remove,
                                                     order_id,
                                                     bid_or_ask,
                                                     limit_price,
                                                     order_size);
            
            if( !parsed_successfully ) continue;

            if( add_or_remove == Pricer::ADD_TYPE )
            {
                
                // shared pointer because it will be held by a map and a set
                std::shared_ptr<MarketOrder> order_sptr(new MarketOrder(order_id,
                                                                        time_stamp,
                                                                        limit_price,
                                                                        order_size,
                                                                        bid_or_ask) );

                // Bids are stored in one set, asks are stored in a different one
                if( bid_or_ask == Pricer::BID_TYPE )
                {
                    new_earnings = pricer.AddBidOrderToBook(order_sptr);   

                    earnings_changed = new_earnings != last_earnings;

                    output = DeduceOutput(Pricer::SELL_CHAR, 
                                          pricer,
                                          time_stamp,
                                          earnings_changed);

                    last_earnings = new_earnings;
            
                }else
                {
                    new_expense = pricer.AddAskOrderToBook(order_sptr);   
                    earnings_changed = new_expense != last_expense;

                    output = DeduceOutput(Pricer::BUY_CHAR,
                                          pricer,
                                          time_stamp,
                                          earnings_changed);

                    last_expense = new_expense;
                }
                
                if(output.size() > 0) cout << output << endl;
        
            }else
            {
                bid_or_ask = pricer.GetOrderTypeFromID(order_id);

                // Bids and asks live in separate sets
                // The two reduce functions modify each respectively 
                if( bid_or_ask  == Pricer::BID_TYPE )
                {
                    new_earnings = pricer.ReduceBidOrderFromBook(order_id, order_size);   
                    earnings_changed = new_earnings != last_earnings;

                    output = DeduceOutput(Pricer::SELL_CHAR,
                                          pricer,
                                          time_stamp,
                                          earnings_changed);

                    last_earnings = new_earnings;

                }else if( bid_or_ask == Pricer::ASK_TYPE ){

                    new_expense = pricer.ReduceAskOrderFromBook(order_id, order_size);   
                    earnings_changed = new_expense != last_expense;

                    output = DeduceOutput(Pricer::BUY_CHAR,
                                          pricer,
                                          time_stamp,
                                          earnings_changed);

                    last_expense = new_expense;
                }

                if(output.size() > 0) cout << output << endl;
            }
        }

    }else
    {
        cerr << Pricer::USAGE_MESSAGE << endl;
    }
        
    return 0;
}
