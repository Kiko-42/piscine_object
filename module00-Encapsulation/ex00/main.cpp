#include "Bank.hpp"
#include "Bank_test.hpp"

int main()
{
    // DEMO
    try {
        Bank bank;
        size_t accountA = bank.createAccount();
        std::cout << bank << std::endl;

        bank.deposit(accountA, 4000);
        std::cout << "deposit: 4000" << std::endl;
        std::cout << bank[accountA] << std::endl;
        std::cout << bank << std::endl;

        bank.withdraw(accountA, 500);
        std::cout << "withdraw: 500" << std::endl;
        std::cout << bank << std::endl;

        bank.loan(accountA, 200);
        std::cout << "loan: 200" << std::endl;
        std::cout << bank << std::endl;

        bank.repay(accountA, 200);
        std::cout << "repay: 200" << std::endl;
        std::cout << bank << std::endl;

        try {
            bank.loan(accountA, 99999);
        } catch (const std::exception &e) {
            std::cout << "loan: 99999 -> refused: " << e.what() << std::endl;
            std::cout << std::endl;
        }

        size_t accountB = bank.createAccount();
        std::cout << "add account" << std::endl;
        std::cout << bank << std::endl;


        bank.deleteAccount(accountA);
        std::cout << bank << std::endl;
        bank.deleteAccount(accountB);

        std::cout << bank << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "DEMO Error: " << e.what() << std::endl;
    }

    //UnitTest
    try {
        Bank_test::runBankTests();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return(1);
    }
    std::cout << "Unit Test All GREEN" << std::endl;

	return (0);
}
