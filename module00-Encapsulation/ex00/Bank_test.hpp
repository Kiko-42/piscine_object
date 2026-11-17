#ifndef BANK_TEST
#define BANK_TEST

#include <cstddef>

class Bank;

class Bank_test
{
public:
    static void runBankTests();
private:
    Bank_test();

    static void expectEqual(const char *label, int expect, int actual);
    static void expectState(const char *label, const Bank &bank, size_t id, int balance, int loan, int liquidity);

    static void testCreateAccount();
    static void testDeleteAccount();
    static void testDeposit();
    static void testDepositZero();
    static void testDepositNegative();
    static void testDepositTooSmall();
    static void testWithdraw();
    static void testWithdrawZero();
    static void testWithdrawNegative();
    static void testWithdrawInsufficientFunds();
    static void testLoan();
    static void testLoanZero();
    static void testLoanNegative();
    static void testLoanInsufficientLiquidity();
    static void testLoanTooSmall();
    static void testRepay();
    static void testRepayZero();
    static void testRepayNegative();
    static void testRepayExceedsLoan();
    static void testRepayInsufficientFunds();
};

#endif
