#include "Bank.hpp"
#include "Bank_test.hpp"

int main()
{
	Bank bank;

    bank.createAccount(100);
    bank.createAccount(100);

    bank.deposit(0, 400);

	std::cout << " ----- " << std::endl;

	std::cout << "Bank : " << std::endl;
	std::cout << bank << std::endl;

	return (0);
}
