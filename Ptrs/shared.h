#ifndef WIDGET_H
#define WIDGET_H

namespace WIDGET_N
{

class Widget
{

    public:

        ~Widget();//{ cout << "Self-destruct! \n"; }
        
        //Widget(Widget&& lhs) = default;
        //Widget(const Widget& lhs) = default;
        //Widget() = default;
        

        void addNumber(int number);

    private:
        int m_number;
};

} // WIDGET
#endif 
