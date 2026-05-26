#include <iostream>
#include <string>
using namespace std;

class bank{
    private:
    double balance;
    protected:
    int transactionCount = 0;
    public:

    void deposit(double amount){
        cout << "Enter deposit amount: ";
        cin >> amount;
        balance += amount;
        transactionCount++;
        cout << "Deposit successful." << endl;

    }
    void withdraw(double amount){
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        if(amount <= balance){
            balance -= amount;
            transactionCount++;
            cout << "Withdrawal successful." << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }
    }
    void showBalance(){
        cout << "Current Balance: $" << balance << endl;
    }
};

class banksystem : public bank{
    public:
    void showTransactionHistory(){
        cout << "Total Transactions: " << transactionCount << endl;
    }
};

int main(){
    banksystem myBank;
    cout << "=================================" << endl;
    myBank.deposit(1000);
    cout << "" << endl;
    myBank.deposit(500);
    cout << "" << endl;
    myBank.withdraw(300);
    cout << "" << endl;
    myBank.showBalance();
    cout << "" << endl;
    myBank.showTransactionHistory();
    cout << "=================================" << endl;
    return 0;
}

