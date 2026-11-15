#include "Bank_test.hpp"
#include "Bank.hpp"
#include <sstream>
#include <stdexcept>

void Bank_test::runBankTests()
{
    testCreateAccount();
    testDeleteAccount();
    testDeposit();
    testWithdrawInsufficientFunds();
    testLoan();
}

void Bank_test::expectEqual(const char *label, int expect, int actual)
{
    if (expect == actual)
        return;
    std::ostringstream oss;
    oss << label << ": expect " << expect << ", actual " << actual;
    throw std::runtime_error(oss.str());
}

void Bank_test::testCreateAccount()
{
    Bank bank;
    size_t a = bank.createAccount();
    size_t b = bank.createAccount();

    if (a == b)
        throw std::runtime_error("createAccount: ids must be unique");
    expectEqual("createAccount: getId matches", static_cast<int>(a), static_cast<int>(bank[a].getId()));
    expectEqual("createAccount: initial balance", 0, bank[a].getValue());
    expectEqual("createAccount: initial loan", 0, bank[a].getLoan());

}

void Bank_test::testDeleteAccount()
{
    Bank bank;
    size_t id = bank.createAccount();

    bank.deleteAccount(id);

    try {
        (void)bank[id];
    } catch (const std::out_of_range &e) {
        return;
    }
    throw std::runtime_error("deleteAccount: account is still accessible after delete");
}

void Bank_test::testDeposit()
{
    Bank bank;
    size_t id = bank.createAccount();

    bank.deposit(id, 2000);
    expectEqual("deposit: balance minus 5% fee", 1900, bank[id].getValue());
    expectEqual("deposit: fee goes to bank", 100, bank.getLiquidity());
}


void Bank_test::testWithdrawInsufficientFunds()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.withdraw(id, 1); // 残高 0 から引き出す
    } catch (const Bank::InsufficientFunds&) {
        return; // 期待どおり
    }
   throw std::runtime_error("withdraw: expected InsufficientFunds");
}

void Bank_test::testLoan()
{
    Bank bank;
    size_t depositor = bank.createAccount();
    size_t id = bank.createAccount();

    bank.deposit(depositor, 40000);
    bank.deposit(id, 2000);
    int before = bank[id].getValue();
    bank.loan(id, 2000); // 残高 3800、借金 2000
    bank.repay(id, 2000); // 残高 1800、借金 0

    expectEqual("loan+repay: debt is cleared", 0, bank[id].getLoan());
    expectEqual("loan+repay: client pays the fee once", before - 100, bank[id].getValue());
}
