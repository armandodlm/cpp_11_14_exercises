#ifndef FACTORY_H
#define FACTORY_H

#include <memory>

enum class InvestmentType;

namespace UniquePointerTest
{

class Factory
{
public:
    std::unique_ptr<Investment> getInvestment(InvestmentType type);   
};

}
#endif
