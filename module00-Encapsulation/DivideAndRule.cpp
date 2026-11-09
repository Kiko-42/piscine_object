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

	Bank() :
		liquidity(0)
	{

	}
    ~Bank() {
        for (size_t i=0; i<clientAccounts.size(); i++)
        delete clientAccounts[i];
    }

    Accounts::iterator findOrThrow(size_t id)
    {
        Accounts::iterator it = clientAccounts.find(id);
        if (it == clientAccounts.end())
            throw std::out_of_range("no such account");
        return it;
    }

    Accounts::const_iterator findOrThrow(size_t id) const
    {
        Accounts::const_iterator it = clientAccounts.find(id);
        if (it == clientAccounts.end())
            throw std::out_of_range("no such account");
        return it;
    }

    const Account& operator [] (size_t id) const 
    {
        return *(findOrThrow(id)->second);
    }

    friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
    {
    	p_os << "Bank informations : " << std::endl;
    	p_os << "Liquidity : " << p_bank.liquidity << std::endl;
        for (size_t i=0; i<p_bank.clientAccounts.size(); i++) {
            p_os << p_bank[i] << std::endl;
        }
    	return (p_os);
    }

public:
    void createAccount(int value)
    {
        clientAccounts[new_id] = new Account(new_id, value);
        new_id++;
    }

    void deleteAccount(size_t id)
    {
        Accounts::iterator it = findOrThrow(id);
        delete it->second;
        clientAccounts.erase(it);
    }

    void deposit(size_t id, int value)
    {
        Accounts::iterator it = findOrThrow(id);
        it->second->value += value;
    }

    void withdraw(size_t id, int value)
    {
        Accounts::iterator it = findOrThrow(id);
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
	Bank bank = Bank();

     bank.createAccount(100);
     bank.createAccount(100);

     bank.liquidity -= 200;

     bank.deposit(0, 400);


	std::cout << " ----- " << std::endl;

	std::cout << "Bank : " << std::endl;
	std::cout << bank << std::endl;

	return (0);
}
