#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <map>
#include <stdexcept>

class Bank
{
public:
    class Account
    {
        friend class Bank;
    
        const size_t id;
        int value;
    
        Account(size_t id) : id(id), value(0) {}
    
        friend std::ostream& operator << (std::ostream& p_os, const Account& p_account);
    };
    
    Bank();
    ~Bank();
    
    size_t createAccount();
    void deleteAccount(size_t id);
    void deposit(size_t id, int amount);
    void withdraw(size_t id, int amount);
    
    const Account& operator [] (size_t id) const;
    friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
    
    class DepositTooSmall : public std::runtime_error
    {
    public:
        DepositTooSmall() : std::runtime_error("deposit is too small to charge a fee") {}
    };
    
    class InsufficientFunds : public std::runtime_error
    {
    public:
        InsufficientFunds() : std::runtime_error( "withdrawal amount exceeds account balance") {}
    };
private:
    typedef std::map<size_t, Account *> Accounts;
    static const int DEPOSIT_FEE_DIVISOR = 20; // 5% = 1/20
    
    int liquidity;
    size_t new_id;
    Accounts clientAccounts;
    
    Accounts::iterator getAccount(size_t id);
    Accounts::const_iterator getAccount(size_t id) const;
    
    Bank(const Bank&);
    Bank& operator=(const Bank&);
};

#endif
