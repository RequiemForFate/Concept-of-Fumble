#include <iostream>
#include <string>
using namespace std;

class booking {
private: 
    string name;
    int roomNumber;
    double price;
    int nights;
public: 
    booking() : roomNumber(0), price(0.0), nights(0) {}

    void bookRoom(){
        cout << "================ INFO ==================" << endl;
        cout << "Enter customer name: ";
        getline(cin, name);
        cout << "Enter room number: ";
        cin >> roomNumber;
        cout << "Enter room price: ";
        cin >> price;
        cout << "Enter number of nights: ";
        cin >> nights;
        if (nights < 0) {
            nights = 0;
        }
        cout << "=======================================" << endl;
    }

    bool cancelBooking(int roomToCancel){
        if(name.empty()){
            cout << "No booking found to cancel." << endl;
            return false;
        }
        if(roomToCancel != roomNumber){
            cout << "Room number does not match current booking." << endl;
            cout << "Current booked room is " << roomNumber << "." << endl;
            return false;
        }
        name = "";
        roomNumber = 0;
        price = 0.0;
        nights = 0;
        cout << "Booking for room " << roomToCancel << " cancelled." << endl;
        return true;
    }

    double calculateTotalPrice() const {
        return price * nights;
    }

    void displayBooking(){
        cout << "================ RECEIPT ==================" << endl;
        if(name.empty()){
            cout << "No booking found." << endl;
        } else {
            cout << "Customer Name: " << name << endl;
            cout << "Room Number: " << roomNumber << endl;
            cout << "Room Price per Night: $" << price << endl;
            cout << "Nights Stayed: " << nights << endl;
            cout << "Total Price: $" << calculateTotalPrice() << endl;
        }
        cout << "===========================================" << endl;
    }
};

int main(){
    booking myBooking;

    int choice;
    do {
        cout << "====== HOTEL BOOKING SYSTEM ======" << endl;
        cout << "1. Book Room" << endl;
        cout << "2. Cancel Booking" << endl;
        cout << "3. Display Booking" << endl;
        cout << "4. Calculate Total Price" << endl;
        cout << "5. Exit" << endl;
        cout << "==================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                myBooking.bookRoom();
                break;
            case 2: {
                int roomToCancel;
                cout << "Enter room number to cancel: ";
                cin >> roomToCancel;
                myBooking.cancelBooking(roomToCancel);
                break;
            }
            case 3:
                myBooking.displayBooking();
                break;
            case 4:
                cout << "Displaying total price for current booking:" << endl;
                cout << "Total Price: $" << myBooking.calculateTotalPrice() << endl;
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "" << endl;
    } while(choice != 5);



    return 0;


}