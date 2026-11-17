#include "Bank_test.hpp"
#include "Bank.hpp"
#include <sstream>
#include <stdexcept>

void Bank_test::runBankTests()
{
    testCreateAccount();
    testDeleteAccount();
    testDeposit();
    testDepositZero();
    testDepositNegative();
    testDepositTooSmall();
    testWithdraw();
    testWithdrawZero();
    testWithdrawNegative();
    testWithdrawInsufficientFunds();
    testLoan();
    testLoanZero();
    testLoanNegative();
    testLoanInsufficientLiquidity();
    testLoanTooSmall();
    testRepay();
    testRepayZero();
    testRepayNegative();
    testRepayExceedsLoan();
    testRepayInsufficientFunds();
}

void Bank_test::expectEqual(const char *label, int expect, int actual)
{
    if (expect == actual)
        return;
    std::ostringstream oss;
    oss << label << ": expect " << expect << ", actual " << actual;
    throw std::runtime_error(oss.str());
}

// Checks the account and the bank in one call. Used after a refused operation to make sure nothing was modified.
void Bank_test::expectState(const char *label, const Bank &bank, size_t id, int balance, int loan, int liquidity)
{
    std::string prefix(label);

    expectEqual((prefix + " (balance)").c_str(), balance, bank[id].getBalance());
    expectEqual((prefix + " (loan)").c_str(), loan, bank[id].getLoan());
    expectEqual((prefix + " (liquidity)").c_str(), liquidity, bank.getLiquidity());
}

void Bank_test::testCreateAccount()
{
    Bank bank;
    size_t a = bank.createAccount();
    size_t b = bank.createAccount();

    if (a == b)
        throw std::runtime_error("createAccount: ids must be unique");
    expectEqual("createAccount: getId matches", static_cast<int>(a), static_cast<int>(bank[a].getId()));
    expectEqual("createAccount: initial balance", 0, bank[a].getBalance());
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
    expectEqual("deposit: balance minus 5% fee", 1900, bank[id].getBalance());
    expectEqual("deposit: fee goes to bank", 100, bank.getLiquidity());
}

void Bank_test::testDepositZero()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.deposit(id, 0);
    } catch (const std::invalid_argument&) {
        expectState("deposit 0: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("deposit: success deposit when amount is 0");
}

void Bank_test::testDepositNegative()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.deposit(id, -1);
    } catch (const std::invalid_argument&) {
        expectState("deposit negative: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("deposit: success deposit when amount is negative");
}


void Bank_test::testDepositTooSmall()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.deposit(id, 19); // 19 * 5% < 1
    } catch (const Bank::DepositTooSmall&) {
        expectState("deposit too small: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("deposit: success deposit when fee is 0");
}

void Bank_test::testWithdraw()
{
    Bank bank;
    size_t id = bank.createAccount();

    bank.deposit(id, 2000);
    bank.withdraw(id, 1900); // 1900 = 2000 - fee
    expectEqual("withdraw: balance is emptied", 0, bank[id].getBalance());
    expectEqual("withdraw: liquidity is unchanged", 100, bank.getLiquidity());
}

void Bank_test::testWithdrawZero()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.withdraw(id, 0);
    } catch (const std::invalid_argument&) {
        expectState("withdraw 0: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("withdraw: success withdraw when amount is 0");
}

void Bank_test::testWithdrawNegative()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.withdraw(id, -1);
    } catch (const std::invalid_argument&) {
        expectState("withdraw negative: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("withdraw: success withdraw when amount is negative");
}

void Bank_test::testWithdrawInsufficientFunds()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.withdraw(id, 1); //withdraw from an empty account
    } catch (const Bank::InsufficientFunds&) {
        expectState("withdraw insufficient funds: state unchanged", bank, id, 0, 0, 0);
        return;
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
    int beforeBalance = bank[id].getBalance();
    int beforeLiquidity = bank.getLiquidity();
    bank.loan(id, 2000);

    expectEqual("loan: payout comes out of liquidity", beforeLiquidity - 1900, bank.getLiquidity());
    expectEqual("loan: client owes the full amount", 2000, bank[id].getLoan());
    expectEqual("loan: client pays the fee once", beforeBalance + 1900, bank[id].getBalance());
}

void Bank_test::testLoanZero()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.loan(id, 0);
    } catch (const std::invalid_argument&) {
        expectState("loan 0: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("loan: success loan when amount is 0");
}

void Bank_test::testLoanNegative()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.loan(id, -1);
    } catch (const std::invalid_argument&) {
        expectState("loan negative: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("loan: success loan when amount is negative");
}

void Bank_test::testLoanInsufficientLiquidity()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.loan(id, 2000);
    } catch (const Bank::InsufficientLiquidity&) {
        expectState("loan insufficient liquidity: state unchanged", bank, id, 0, 0, 0);
        return;
    }
   throw std::runtime_error("loan: expected InsufficientLiquidity");
}

void Bank_test::testLoanTooSmall()
{
    Bank bank;
    size_t id = bank.createAccount();

    size_t depositor = bank.createAccount();
    bank.deposit(depositor, 40000);

    try {
        bank.loan(id, 19);
    } catch (const Bank::LoanTooSmall&) {
        expectState("loan too small: state unchanged", bank, id, 0, 0, 2000); // liquidity 2000 = fee of the 40000 deposit
        return;
    }
   throw std::runtime_error("loan: expected LoanTooSmall");
}

void Bank_test::testRepay()
{
    Bank bank;
    size_t depositor = bank.createAccount();
    size_t id = bank.createAccount();

    bank.deposit(depositor, 40000);
    bank.deposit(id, 2000);

    int beforeLiquidity = bank.getLiquidity();
    bank.loan(id, 2000); // 残高 3800、借金 2000
    int beforeBalance = bank[id].getBalance();
    bank.repay(id, 2000); // 残高 1800、借金 0

    expectEqual("repay: repayment comes out of balance", beforeBalance - 2000, bank[id].getBalance());
    expectEqual("repay: debt is cleared", 0, bank[id].getLoan());
    expectEqual("repay: bank earns the fee", beforeLiquidity + 100, bank.getLiquidity());
}

void Bank_test::testRepayZero()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.repay(id, 0);
    } catch (const std::invalid_argument&) {
        expectState("repay 0: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("repay: success repay when amount is 0");
}

void Bank_test::testRepayNegative()
{
    Bank bank;
    size_t id = bank.createAccount();

    try {
        bank.repay(id, -1);
    } catch (const std::invalid_argument&) {
        expectState("repay negative: state unchanged", bank, id, 0, 0, 0);
        return;
    }
    throw std::runtime_error("repay: success repay when amount is negative");
}

void Bank_test::testRepayExceedsLoan()
{
    Bank bank;
    size_t depositor = bank.createAccount();
    size_t id = bank.createAccount();

    bank.deposit(depositor, 40000);
    bank.deposit(id, 2000);
    bank.loan(id, 2000);

    try {
        bank.repay(id, 2001);
    } catch (const Bank::RepaymentExceedsLoan&) {
        expectState("repay exceeds loan: state unchanged", bank, id, 3800, 2000, 200); // 残高 1900 + 1900、liquidity 2100 - 1900
        return;
    }
    throw std::runtime_error("repay: expected RepaymentExceedsLoan");
}

void Bank_test::testRepayInsufficientFunds()
{
    Bank bank;
    size_t depositor = bank.createAccount();
    size_t id = bank.createAccount();

    bank.deposit(depositor, 40000);
    bank.loan(id, 2000);
    try {
        bank.repay(id, 2000);
    } catch (const Bank::InsufficientFunds&) {
        expectState("repay insufficient funds: state unchanged", bank, id, 1900, 2000, 100); // 残高 1900 = 融資の受取額、liquidity 2000 - 1900
        return;
    }
   throw std::runtime_error("repay: expected InsufficientFunds");
}
