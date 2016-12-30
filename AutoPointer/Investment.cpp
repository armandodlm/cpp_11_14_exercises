#include "Investment.h"

namespace UniquePointerTest
{

Investment::Investment(int value): m_value( value )
{
}

int Investment::getValue()
{
    return m_value;
}

}
