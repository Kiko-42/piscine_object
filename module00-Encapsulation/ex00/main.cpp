#include "Bank.hpp"
#include "Bank_test.hpp"

int main()
{
    //TODO: demo
    try {
        Bank_test::runBankTests();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return(1);
    }

	return (0);
}
