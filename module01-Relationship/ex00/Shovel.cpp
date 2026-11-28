
#include "Shovel.hpp"
#include <iostream>

void Shovel::use()
{
    numberOfUses++;
    std::cout << "shovel used" << std::endl;
}

