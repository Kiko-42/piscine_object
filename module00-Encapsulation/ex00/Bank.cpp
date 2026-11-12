#include "Bank.hpp"
#include <climits>

Bank::Bank() :
    liquidity(0),
    new_id(0) 
{}

Bank::~Bank()
{
    for (Accounts::iterator it=clientAccounts.begin(); it!=clientAccounts.end();it++)
        delete it->second;
}

const Bank::Account& Bank::operator [] (size_t id) const
{
    return *(getAccount(id)->second);
}

std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.liquidity << std::endl;
    for (Bank::Accounts::const_iterator it=p_bank.clientAccounts.begin(); it!=p_bank.clientAccounts.end();it++)
        p_os << *(it->second) << std::endl;

    return (p_os);
}

std::ostream& operator << (std::ostream& p_os, const Bank::Account& p_account)
{
    p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
    return (p_os);
}

size_t Bank::createAccount()
{
    Account* account = new Account(new_id);
    try {
        clientAccounts[new_id] = account;
    } catch (...) {
        delete account;
        throw;
    }
    
    return new_id++;
}

void Bank::deleteAccount(size_t id)
{
    Accounts::iterator it = getAccount(id);
    delete it->second;
    clientAccounts.erase(it);
}

void Bank::deposit(size_t id, int amount)
{
    if (amount <= 0)
        throw std::invalid_argument("deposit amount must be positive");

    Accounts::iterator it = getAccount(id); // throws if the account is not found
    int fee = amount / DEPOSIT_FEE_DIVISOR;
    int credited = amount - fee;

    if (fee <= 0)
        throw DepositTooSmall();
    if (fee > INT_MAX - liquidity)
        throw std::overflow_error("deposit exceeds the bank's liquidity capacity");
    if (credited > INT_MAX - it->second->value)
        throw std::overflow_error("deposit exceeds the account's balance capacity");

    liquidity += fee;
    it->second->value += credited;
}

void Bank::withdraw(size_t id, int amount)
{
    if (amount <= 0)
        throw std::invalid_argument("withdrawal amount must be positive");

    Accounts::iterator it = getAccount(id);
    if (it->second->value < amount)
        throw InsufficientFunds();

    it->second->value -= amount;
}


Bank::Accounts::iterator Bank::getAccount(size_t id)
{
    Accounts::iterator it = clientAccounts.find(id);
    if (it == clientAccounts.end())
        throw std::out_of_range("no such account");
    return it;
}

Bank::Accounts::const_iterator Bank::getAccount(size_t id) const
{
    Accounts::const_iterator it = clientAccounts.find(id);
    if (it == clientAccounts.end())
        throw std::out_of_range("no such account");
    return it;
}
