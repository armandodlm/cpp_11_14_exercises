#include <memory>
#include <iostream>
#include "shared.h"


using namespace std; // bad!!

namespace WIDGET_N
{


Widget::~Widget()
{
 cout << "Self-destruct! \n"; 
}

void Widget::addNumber(int number)
{
    m_number = number;
    cout << "Number " << m_number << " was added \n";
}

} // WIDGET


int main()
{
    auto ptr = shared_ptr<WIDGET_N::Widget>(new WIDGET_N::Widget); 
    auto ptr2 = unique_ptr<WIDGET_N::Widget>(new WIDGET_N::Widget);

    auto ptr3 = make_shared<WIDGET_N::Widget>();
    auto ptr4 = make_unique<WIDGET_N::Widget>();

    auto ptr6 = ptr3;
    auto ptr7 = shared_ptr<WIDGET_N::Widget>(std::move(ptr4));

    //auto ptr5 = make_shared<WIDGET_N::Widget>(ptr2);

    //auto ptr4 = ptr2;

    ptr->addNumber( 5 );

    

    return 0;
}

