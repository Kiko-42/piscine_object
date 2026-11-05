#include <iostream>
#include <vector>

class Bank;

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

struct Bank
{
	int liquidity;
	std::vector<Account *> clientAccounts;

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
        p_os << *(p_bank.clientAccounts[i]) << std::endl;
    }
		return (p_os);
	}

  void createAccount(int value) {
    size_t id = clientAccounts.size();
    clientAccounts.push_back(new Account(id, value));
  }

  void deposit(size_t id, int value) {
    clientAccounts[id]->value += value; 
  }

  void withdraw(size_t id, int value) {
    clientAccounts[id]->value -= value; 
  }
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
