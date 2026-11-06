#include <iostream>
#include <map>

class Bank
{
    class Account; //class定義の先頭にAccountがあるとコードの可読性が下がる気がするので前方宣言でしたに書いているが、ここはどうなるべきなんだろう。hppを書いてBankとAccountのファイルを分けてよみやすくするのがいいのかな
	int liquidity;
    size_t new_id;
	std::map<size_t, Account *> clientAccounts;

	Bank() :
		liquidity(0)
	{

	}
    ~Bank() {
        for (size_t i=0; i<clientAccounts.size(); i++)
        delete clientAccounts[i];
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

    friend Account& operator [] (size_t id) const
    {
        return (clientAccounts.find(id));
    }

    public: 
    void createAccount(int value) {
        clientAccounts.push_back(new Account(new_id, value));
        new_id++;
    }

    void deleteAccount(size_t id) {
        Account* account = clientAccounts.find(id);
        delete account;
    }

    void deposit(size_t id, int value) {
        clientAccounts[id]->value += value; 
    }

    void withdraw(size_t id, int value) {
        clientAccounts[id]->value -= value; 
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
	bank.liquidity = 999;

     bank.createAccount(100);
     bank.createAccount(100);

     bank.liquidity -= 200;

     bank.deposit(0, 400);


	std::cout << " ----- " << std::endl;

	std::cout << "Bank : " << std::endl;
	std::cout << bank << std::endl;

	return (0);
}
