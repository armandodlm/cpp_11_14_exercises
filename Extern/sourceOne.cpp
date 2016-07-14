#include <iostream>
using namespace std; // bad, but using in sample

extern const int i;

int main()
{
    cout << "The value of the extern is: " << i << '\n';
    return 0;
}
