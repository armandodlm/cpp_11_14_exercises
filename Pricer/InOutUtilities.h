#ifndef INOUT_UTILS_H
#define INOUT_UTILS_H

#include <exception>
#include <iostream>

namespace Pricer
{

    bool ParseInput( std::string order_str,
                     unsigned long &time_stamp,
                     char &order_type,
                     std::string &order_id,
                     char &bid_or_ask,
                     double &order_price,
                     unsigned int &order_size)
    {
        size_t str_first_index;
        size_t continue_from_index;
        bool parsed_successfully = false;
        
        try
        {

            // timestamp is the first element in the screen
            time_stamp = std::stol( order_str, &continue_from_index ); 
            
            // continue_from_index now points to the space after the time_stamp
            // skip the space and read the A/R
            order_type = order_str.at( continue_from_index + 1 );
            
            // Skip the space, the A/R and the space after
            // str_first_index now points to the first index of the id
            str_first_index = continue_from_index + 3;  
            
            // Find the space after the id
            continue_from_index = order_str.find_first_of(" ",str_first_index);
            
            // Get the id between str_first_index and the index of the space after the id
            order_id = order_str.substr(str_first_index, continue_from_index - str_first_index);

            if( order_type == Pricer::ADD_TYPE ){

                // Character after the space after the id is the B/S char 
                bid_or_ask = order_str.at(continue_from_index + 1);
                
                // remove the chars up to the price 
                order_str.erase(0,continue_from_index+3);

                // Use stod to read and convert the price to a double
                order_price = std::stod( order_str, &str_first_index);
                // Use stoi to read the size (as an integer)
                order_size = std::stoi(order_str.substr(str_first_index));

            }else
            {
                // Just read the 
                order_size = std::stoi(order_str.substr(continue_from_index));
            }
            
            parsed_successfully = true;

        } catch(std::exception &e)
        {
            std::cerr << "WARNING: Order format is not valid" << std::endl;
            parsed_successfully = false;
        }

        return parsed_successfully;
    }
}
#endif
