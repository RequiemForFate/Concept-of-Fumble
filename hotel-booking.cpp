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

    int choice;
    do {
        cout << "1. Book Room" << endl;
        cout << "2. Cancel Booking" << endl;
        cout << "3. Display Booking" << endl;
        cout << "4. Calculate Total Price" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after entering choice

        switch(choice) {
            case 1:
                myBooking.bookRoom();
                break;
            case 2:
                myBooking.cancelBooking();
                break;
            case 3:
                myBooking.displayBooking();
                break;
            case 4:
                int nights;
                cout << "Enter number of nights: ";
                cin >> nights;
                myBooking.calculateTotalPrice(nights);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "" << endl; // Add a blank line for better readability
    } while(choice != 5);

    return 0;


}