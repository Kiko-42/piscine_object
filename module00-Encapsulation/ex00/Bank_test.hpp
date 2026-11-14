#ifndef BANK_TEST
#define BANK_TEST


class Bank_test
{
public:
    static void runBankTests();
private:
    Bank_test();

    static void expectEqual(const char *label, int expect, int actual);

    static void testDeposit();
    static void testLoan();
};

#endif
