#include <iostream>
#include <string>
using namespace std;

class booking {
private: 
string name;
int roomNumber;
double price;
public: 
void bookRoom(){
    cout << "Enter customer name: ";
    getline(cin, name);
    cout << "Enter room number: ";
    cin >> roomNumber;
    cout << "Enter room price: ";
    cin >> price;
}

void cancelBooking(){
    name = "";
    roomNumber = 0;
    price = 0.0;
    cout << "Booking cancelled." << endl;
}

void displayBooking(){
    if(name.empty()){
        cout << "No booking found." << endl;
    } else {
        cout << "Customer Name: " << name << endl;
        cout << "Room Number: " << roomNumber << endl;
        cout << "Room Price: $" << price << endl;
    }
}

void calculateTotalPrice(int nights){
    double totalPrice = price * nights;
    cout << "Total Price for " << nights << " nights: $" << totalPrice << endl;
}

void showBookingDetails(){
    cout << "Customer Name: " << name << endl;
    cout << "Room Number: " << roomNumber << endl;
    cout << "Room Price: $" << price << endl;

}
};

int main(){
    booking myBooking;
    cout << "=================Hotel Booking System================" << endl;
    myBooking.bookRoom();
    cout << "" << endl;
    myBooking.displayBooking();
    cout << "" << endl;
    int nights;
    cout << "Enter number of nights: ";
    cin >> nights;
    myBooking.calculateTotalPrice(nights);
    cout << "" << endl;
    myBooking.cancelBooking();
    cout << "" << endl;
    myBooking.displayBooking();
    cout << "===================================================" << endl;
    return 0;


}