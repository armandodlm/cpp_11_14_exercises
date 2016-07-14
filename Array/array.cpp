#include <array>
#include <iostream>
#include <algorithm>


int main()
{
    std::array<int,5> a{1, 2, 3, 4, 5};

    auto predicate = [](int val){ std::cout << val << '\n';};

    auto lessThan = [](int a, int b) { return a < b; };
    
    std::for_each(a.begin(), a.end(), predicate);
    std::sort(a.begin(), a.end(), lessThan);
    std::for_each(a.begin(), a.end(), predicate);
}
