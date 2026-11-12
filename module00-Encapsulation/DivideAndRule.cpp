#include <iostream>
#include <map>
#include <stdexcept>
#include <climits>

class Bank
{
private:
    class Account;
public:
	Bank() :
		liquidity(200),
        new_id(0)
	{

	}

    ~Bank()
    {
        for (Accounts::iterator it=clientAccounts.begin(); it!=clientAccounts.end();it++)
            delete it->second;
    }

    size_t createAccount()
    {
        size_t id = new_id++;
        clientAccounts[id] = new Account(id);
        
        return id;
    }

    void deleteAccount(size_t id)
    {
        Accounts::iterator it = getAccount(id);
        delete it->second;
        clientAccounts.erase(it);
    }

    void deposit(size_t id, int amount)
    {
        if (amount <= 0)
            throw std::invalid_argument("deposit amount must be positive");

        Accounts::iterator it = getAccount(id); //to validate to not founded account
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

    void withdraw(size_t id, int value)
    {
        if (value <= 0)
            throw std::invalid_argument("withdrawal amount must be positive");

        Accounts::iterator it = getAccount(id);
        if (it->second->value < value)
            throw InsufficientFunds();

        it->second->value -= value;
    }

    const Account& operator [] (size_t id) const
    {
        return *(getAccount(id)->second);
    }

    friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
    {
    	p_os << "Bank informations : " << std::endl;
    	p_os << "Liquidity : " << p_bank.liquidity << std::endl;
        for (Accounts::const_iterator it=p_bank.clientAccounts.begin(); it!=p_bank.clientAccounts.end();it++)
            p_os << *(it->second) << std::endl;

    	return (p_os);
    }
    
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

    Accounts::iterator getAccount(size_t id)
    {
        Accounts::iterator it = clientAccounts.find(id);
        if (it == clientAccounts.end())
            throw std::out_of_range("no such account");
        return it;
    }

    Accounts::const_iterator getAccount(size_t id) const
    {
        Accounts::const_iterator it = clientAccounts.find(id);
        if (it == clientAccounts.end())
            throw std::out_of_range("no such account");
        return it;
    }

    Bank(const Bank&);
    Bank& operator=(const Bank&);

    class Account
    {
        friend class Bank;
    
    	const size_t id;
    	int value;
    
    	Account(size_t id) : id(id), value(0) {}
    
    	friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
    	{
    		p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
    		return (p_os);
    	}
    };
};

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
