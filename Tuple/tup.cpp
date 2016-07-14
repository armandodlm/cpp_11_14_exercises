#include <tuple>
#include <iostream>

using namespace std;

int main()
{
    using t3 = std::tuple<int,int,int>;
    
    t3 a(1,2,3);
    
    cout << "First tuple contains " << get<0>(a) << " " << get<1>(a) << " " << get<2>(a) << '\n';
}
