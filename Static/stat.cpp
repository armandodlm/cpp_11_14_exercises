#include <iostream>
using namespace std; // bad, but just for demo


int instancesCount = 0;


class Multifaceted
{
    
public:

    Multifaceted()
    {
        instancesCount++;
        cout << "There are " << instancesCount << " of this class instances \n";
    }

    void functionCall(){
        static int functionCount = 0;
        cout << "Function has been invoked " << ++functionCount << '\n';
    }

    static int theOtherStat;
    static const int FIVE;

};

// A member static in a class must be defined in file scope
int Multifaceted::theOtherStat = 0;
// And a const can have an initializer
const int Multifaceted::FIVE = 5;

int main()
{
    Multifaceted m1;
    Multifaceted m2;
    Multifaceted m3;
    Multifaceted m4;

    m1.functionCall();
    m2.functionCall();
    m3.functionCall();
    m4.functionCall();
    m4.functionCall();
    m2.functionCall();
    m1.functionCall();

    cout << "The other stat is " << m1.theOtherStat << '\n';
    m2.theOtherStat--;
    
    cout << "The other stat is " << m3.theOtherStat << '\n';
    m4.theOtherStat++;

    cout << "The other stat is " << m1.theOtherStat << '\n';

    cout << "Now through the class is " << Multifaceted::theOtherStat << '\n';

    cout << "Finally FIVE is " << Multifaceted::FIVE << '\n';

    return 0;
}
