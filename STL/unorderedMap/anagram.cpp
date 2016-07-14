#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

//using namespace std;

bool areAnagram(std::string word_one, std::string word_two)
{
    std::transform(word_one.begin(), word_one.end(), word_one.begin(), ::tolower );
    std::transform(word_two.begin(), word_two.end(), word_two.begin(), ::tolower );
    
    if( word_one.size() != word_two.size() )
    {   
        std::cout << "They were not the same size..." << std::endl;
        return false;
    }
    else
    {
        // Compare letters

        std::cout << " Same size... " << std::endl;
        
        std::unordered_map<char,int> letters_in_first;
        std::unordered_map<char,int> letters_in_second;
        
        for( int current_char_i = 0; current_char_i != word_one.size(); ++current_char_i)
        {
            auto insert_result = letters_in_first.emplace(word_one[current_char_i], 1);       
            auto insert_result_second = letters_in_second.emplace(word_two[current_char_i], 1);       
            
            if( ! insert_result.second )
            {
                // We did not insert the char as it already existed 
                // increment its count

                std::cout << " W1 Incrementing the count for letter " <<  word_one[current_char_i] << '\n';
                (*insert_result.first).second += 1;

                std::cout << "W1 - " << word_one[current_char_i] << " : " << (insert_result.first)->second << '\n';
                
            }
            else
            {
                std::cout << "W1 - Successfully inserted first " << word_one[current_char_i] << '\n';
            }

            if( ! insert_result_second.second )
            {
                std::cout << " W2 Incrementing the count for letter " <<  word_two[current_char_i] << '\n';
                (*insert_result_second.first).second += 1;
                std::cout << "W2 - " << word_two[current_char_i] << " : " << (insert_result_second.first)->second << '\n';
            }
            else
            {
                std::cout << "W2 - Successfully inserted first " << word_two[current_char_i] << '\n';
            }
        }

        if( letters_in_first.size() != letters_in_second.size() )
        {
            std::cout << "Word maps didn't have the same number of keys :( \n";
            return false;
        }
        else
        {
            // compare the counts of all chars
            
            for( auto letter_w_count : letters_in_first )
            {
                auto letter_in_second = letters_in_second.find( letter_w_count.first );
                if( letter_in_second != letters_in_second.end() )
                {
                    // It was found, compare count
                    if( letter_in_second->second != letter_w_count.second )
                    {
                        return false;
                    }
                    
                }else
                {
                     return false;
                }
            }

        }
        
    }

    return true;
}

int main()
{
    auto are_they =  areAnagram("Mary", "Army");
    
    std::cout << "Army and mary are anagrams? " << are_they << '\n';

    auto are =  areAnagram("a", "a");
    std::cout << "a and a anagrams? " << are << '\n';

    auto eh =  areAnagram("Armando", "Michael");
    std::cout << "armando and michael anagrams? " << eh << '\n';
    return 0;
}
