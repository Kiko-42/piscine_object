#include <iostream>
#include <map>
#include <stdexcept>

class Bank
{
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

    void deposit(size_t id, int value)
    {
        if (value <= 0)
            throw std::invalid_argument("deposit amount must be positive");

        Accounts::iterator it = getAccount(id); //to validate to not founded account
        int truncated_deposit_fee = value * DEPOSIT_FEE_PERCENT / 100;
        if (truncated_deposit_fee <= 0)
            throw DepositTooSmall();

        liquidity += truncated_deposit_fee;
        it->second->value += value - truncated_deposit_fee;
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
    class Account;
    typedef std::map<size_t, Account *> Accounts;
    static const int DEPOSIT_FEE_PERCENT = 5;
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
