#include <iostream>
#include <string>
using namespace std;

class bank{
    private:
    double balance;
    protected:
    int transaction_history;
    public:
    bank(){
        balance = 0.0;
        transaction_history = 0;
    }
    double amount(){
        return balance;
    }
    void deposit(double amount){
        cout << "Enter deposit amount: ";
        cin >> amount;
        balance += amount;
        transaction_history++;
        cout << "Deposit successful." << endl;

    }
    void withdraw(double amount){
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        if(amount <= balance){
            balance -= amount;
            transaction_history++;
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
        cout << "Total Transactions: " << transaction_history << endl;
    }
};

int main(){
    banksystem myBank1;
    cout << "=================================" << endl;
    myBank1.deposit(1000);
    cout << "" << endl;
    myBank1.deposit(500);
    cout << "" << endl;
    myBank1.withdraw(300);
    cout << "" << endl;
    myBank1.showBalance();
    cout << "" << endl;
    myBank1.showTransactionHistory();
    cout << "=================================" << endl;
    return 0;
}

