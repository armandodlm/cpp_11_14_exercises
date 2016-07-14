#include <iostream>
using namespace std;

extern const int friendlyVal = 0;

class Conster
{
    public:
        /*
        Conster()
        {       
        } */

        int getValue() const
        {
            return m_value;
        }

        void setValue(int value)
        {
            m_value = value;
        }

    private:
        int m_value;
};

int main()
{
    Conster c{};
    const Conster c2{};

    c.setValue( 20 );
    //c2.setValue( 10 ); // Error!! c2 is a const object

    return 0;  
}
