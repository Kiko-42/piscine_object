#include <iostream>
#include <map>
#include <stdexcept>

class Bank
{
    class Account; //class定義の先頭にAccountがあるとコードの可読性が下がる気がするので前方宣言でしたに書いているが、ここはどうなるべきなんだろう。hppを書いてBankとAccountのファイルを分けてよみやすくするのがいいのかな
    typedef std::map<size_t, Account *> Accounts;
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

    void createAccount(int value)
    {
        clientAccounts[new_id] = new Account(new_id, value);
        new_id++;
    }

    void deleteAccount(size_t id)
    {
        Accounts::iterator it = getAccount(id);
        delete it->second;
        clientAccounts.erase(it);
    }

    void deposit(size_t id, int value)
    {
        Accounts::iterator it = getAccount(id);
        it->second->value += value;
    }

    void withdraw(size_t id, int value)
    {
        Accounts::iterator it = getAccount(id);
        it->second->value -= value;
    }

private:
    class Account
    {
        friend class Bank;
    
    	size_t id;
    	int value;
    
    
    	Account(size_t id, int value) :
    		id(id),
    		value(value)
    	{
    	
    	}
    
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
