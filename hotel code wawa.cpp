#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class booking {
private:
    string name;
    int roomNumber;
    double price;
    int nights;

public:
    booking() : roomNumber(0), price(0.0), nights(0) {}

    void bookRoom() {
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

        cin.ignore();
        cout << "=======================================" << endl;
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    double calculateTotalPrice() const {
        return price * nights;
    }

    void displayBooking() const {
        cout << "================ RECEIPT ==================" << endl;
        if(name.empty()){
            cout << "No booking found." << endl;
        } else {
            cout << "Customer Name: " << name << endl;
            cout << "Room Number: " << roomNumber << endl;
            cout << "Room Price per Night: $" << fixed << setprecision(2) << price << endl;
            cout << "Nights Stayed: " << nights << endl;
            cout << "Total Price: $" << fixed << setprecision(2) << calculateTotalPrice() << endl;
        }
        cout << "===========================================" << endl;
    }
};

int main(){
    vector<booking> myBooking;
    vector<int> allRooms = {101, 102, 103, 104, 105};

    int choice;
    do {
        cout << "====== HOTEL BOOKING SYSTEM ======" << endl;
        cout << "1. Add Room" << endl;
        cout << "2. Book Room" << endl;
        cout << "3. Cancel Booking" << endl;
        cout << "4. Display Booking" << endl;
        cout << "5. Calculate Total Price" << endl;
        cout << "6. Display Room Status" << endl;
        cout << "7. Exit" << endl;
        cout << "==================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                int roomNumber;

                cout << "Enter room number to add: ";
                cin >> roomNumber;

                bool exists = false;

                for(int room : allRooms) {
                    if(room == roomNumber) {
                        exists = true;
                        break;
                    }
                }

                if(exists) {
                    cout << "Room already exists.\n";
                }
                else {
                    allRooms.push_back(roomNumber);
                    cout << "Room added successfully.\n";
                }

                break;
            }
            case 2: {
                booking newBooking;
                newBooking.bookRoom();
                bool roomExists = false;
                for(int room : allRooms) {
                    if(room == newBooking.getRoomNumber()) {
                        roomExists = true;
                        break;
                    }
                }
                if(!roomExists) {
                    cout << "Room does not exist.\n";
                    break;
                }

                bool occupied = false;

                for(int i = 0; i < myBooking.size(); i++) {
                    if(myBooking[i].getRoomNumber() == newBooking.getRoomNumber()) {
                        occupied = true;
                        break;
                    }
                }

                if(occupied) {
                    cout << "Room is already occupied.\n";
                }
                else {
                    myBooking.push_back(newBooking);
                    cout << "Room booked successfully.\n";
                }

                break;
            }

                case 3: {
                    int roomToCancel;
                    bool found = false;
                    cout << "Enter room number to cancel: ";
                    cin >> roomToCancel;
                    for(int i = 0; i < myBooking.size(); i++) {
                        if(myBooking[i].getRoomNumber() == roomToCancel) {
                            myBooking.erase(myBooking.begin() + i);
                            cout << "Booking cancelled." << endl;
                            found = true;
                            break;
                        }
                    }
                    if(!found) {
                        cout << "Booking not found." << endl;
                    }

                    break;
                }
            case 4:
                if(myBooking.empty()) {
                    cout << "No bookings found." << endl;
                }
                else {
                    for(int i = 0; i < myBooking.size(); i++) {
                        myBooking[i].displayBooking();
                    }
                }
                break;
            case 5: {
                double totalRevenue = 0;

                for(int i = 0; i < myBooking.size(); i++) {
                    totalRevenue += myBooking[i].calculateTotalPrice();
                }

                cout << "Displaying total price for current booking:" << endl;
                cout << "Total Price: $" << totalRevenue << endl;
                break;
            }
            case 6:
                cout << "========== ROOM STATUS ==========" << endl;

                for(int room : allRooms) {

                    bool occupied = false;

                    for(int i = 0; i < myBooking.size(); i++) {
                        if(myBooking[i].getRoomNumber() == room) {
                            occupied = true;
                            break;
                        }
                    }

                    cout << "Room " << room << " : ";

                    if(occupied)
                        cout << "Occupied";
                    else
                        cout << "Available";

                    cout << endl;
                }

                cout << "=================================" << endl;
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "" << endl;
    } while(choice != 7);

    return 0;
}
