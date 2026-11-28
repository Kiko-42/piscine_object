#include "Hammer.hpp"
#include <iostream>

void Hammer::use()
{
    numberOfUses++;
    std::cout << "hammer used" << std::endl;
}

