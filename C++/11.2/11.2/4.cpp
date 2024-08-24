#include<iostream>
using namespace std;

class NegativeBalance {
public:
	NegativeBalance() {}
	void warning();
};
void NegativeBalance::warning()
{
	cout << "Negative Balance" << endl;
}

class BankAccount {
private:
	int balance;
public:
	BankAccount(int b = 0) :balance(b) {}
	~BankAccount();
	int getbalance();
	void setbalance(int b);
	int deposit(int m);
	int withdraw(int m);
	void print();
};
BankAccount::~BankAccount() {}
int BankAccount::getbalance()
{
	return balance;
}
void BankAccount::setbalance(int b)
{
	balance = b;
}
int BankAccount::deposit(int m)
{
	balance += m;
	return balance;
}
int BankAccount::withdraw(int m)
{
	try
	{
		if (m > balance)
			throw NegativeBalance();
		balance -= m;
		return balance;
	}
	catch (NegativeBalance n)
	{
		n.warning();
	}

}
void BankAccount::print()
{
	cout << balance << endl;
}

int main(void)
{
	BankAccount b1(1000);
	b1.withdraw(2000);
	return 0;
}