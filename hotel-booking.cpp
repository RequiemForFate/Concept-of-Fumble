#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

class booking {
private:
    string name;
    int roomNumber;
    double price;
    int nights;
    bool checkedIn;

public:
    booking() : roomNumber(0), price(0.0), nights(0), checkedIn(false) {}

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

    int getRoomNumber() const { return roomNumber; }
    const string& getName() const { return name; }
    double getPrice() const { return price; }
    int getNights() const { return nights; }
    bool isCheckedIn() const { return checkedIn; }

    void setCheckedIn(bool status) { checkedIn = status; }

    double calculateTotalPrice() const {
        return price * nights;
    }

    void displayBooking() const {
        cout << "================ RECEIPT ==================" << endl;
        if (name.empty()) {
            cout << "No booking found." << endl;
        } else {
            cout << "Customer Name: " << name << endl;
            cout << "Room Number: " << roomNumber << endl;
            cout << "Room Price per Night: $" << fixed << setprecision(2) << price << endl;
            cout << "Nights Stayed: " << nights << endl;
            cout << "Total Price: $" << fixed << setprecision(2) << calculateTotalPrice() << endl;
            cout << "Check-In Status: " << (checkedIn ? "Yes" : "No") << endl;
        }
        cout << "===========================================" << endl;
    }
};

bool isRoomOccupied(int roomNumber, const vector<booking>& bookings) {
    for (const auto& b : bookings) {
        if (b.getRoomNumber() == roomNumber)
            return true;
    }
    return false;
}

const booking* findBooking(int roomNumber, const vector<booking>& bookings) {
    for (const auto& b : bookings) {
        if (b.getRoomNumber() == roomNumber)
            return &b;
    }
    return nullptr;
}

// Updated to include check-in status in the file report
void saveHotelFile(const vector<int>& allRooms, const vector<booking>& bookings, const string& filename = "bookings.txt") {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Unable to open " << filename << " for writing." << endl;
        return;
    }

    if (allRooms.empty()) {
        outfile << "No rooms are available in the system." << endl;
        cout << "No room data to save. " << filename << " has been created with an empty state." << endl;
        return;
    }

    outfile << "==== ROOM STATUS REPORT ====" << "\n";
    outfile << "============================" << "\n";
    for (int room : allRooms) {
        outfile << "Room Number: " << room << "\n";
        if (isRoomOccupied(room, bookings)) {
            const booking* b = findBooking(room, bookings);
            outfile << "Status: Occupied" << "\n";
            if (b) {
                outfile << "Customer Name: " << b->getName() << "\n";
                outfile << "Room Price per Night: $" << fixed << setprecision(2) << b->getPrice() << "\n";
                outfile << "Nights Stayed: " << b->getNights() << "\n";
                outfile << "Total Price: $" << fixed << setprecision(2) << b->calculateTotalPrice() << "\n";
                outfile << "Checked-In: " << (b->isCheckedIn() ? "Yes" : "No") << "\n";
            }
        } else {
            outfile << "Status: Available" << "\n";
        }
        outfile << "-------------------------------------" << "\n";
    }

    cout << "Hotel Data saved to " << filename << "." << endl;
}

int main() {
    vector<booking> myBooking;
    vector<int> allRooms = {101, 102, 103, 104, 105};

    int choice;
    do {
        cout << "====== HOTEL BOOKING SYSTEM ======" << endl;
        cout << "1. Add Room" << endl;
        cout << "2. Book Room" << endl;
        cout << "3. Cancel Booking" << endl;
        cout << "4. Display Options" << endl;
        cout << "5. Check-In / Check-Out" << endl;
        cout << "6. Exit" << endl;
        cout << "==================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int roomNumber;
                cout << "Enter room number to add: ";
                cin >> roomNumber;

                bool exists = false;
                for (int room : allRooms) {
                    if (room == roomNumber) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    cout << "Room already exists.\n";
                } else {
                    allRooms.push_back(roomNumber);
                    cout << "Room added successfully.\n";
                }
                break;
            }
            case 2: {
                booking newBooking;
                newBooking.bookRoom();
                bool roomExists = false;
                for (int room : allRooms) {
                    if (room == newBooking.getRoomNumber()) {
                        roomExists = true;
                        break;
                    }
                }
                if (!roomExists) {
                    cout << "Room does not exist.\n";
                    break;
                }

                bool occupied = false;
                for (const auto& b : myBooking) {
                    if (b.getRoomNumber() == newBooking.getRoomNumber()) {
                        occupied = true;
                        break;
                    }
                }

                if (occupied) {
                    cout << "Room is already occupied.\n";
                } else {
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
                for (int i = 0; i < myBooking.size(); i++) {
                    if (myBooking[i].getRoomNumber() == roomToCancel) {
                        myBooking.erase(myBooking.begin() + i);
                        cout << "Booking cancelled." << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Booking not found." << endl;
                }
                break;
            }
            case 4: {
                int displayChoice;
                do {
                    cout << "========================================" << endl;
                    cout << "1. Display All Bookings" << endl;
                    cout << "2. Display Room Status" << endl;
                    cout << "========================================" << endl;
                    cout << "Enter your choice: ";
                    cin >> displayChoice;
                    cin.ignore();

                    if (displayChoice == 1) {
                        if (myBooking.empty()) {
                            cout << "No bookings found." << endl;
                        } else {
                            for (const auto& b : myBooking) {
                                b.displayBooking();
                            }
                        }
                    } else if (displayChoice == 2) {
                        cout << "========== ROOM STATUS ==========" << endl;
                        for (int room : allRooms) {
                            bool occupied = false;
                            for (const auto& b : myBooking) {
                                if (b.getRoomNumber() == room) {
                                    occupied = true;
                                    break;
                                }
                            }
                            cout << "Room " << room << " : " << (occupied ? "Occupied" : "Available") << endl;
                        }
                        cout << "=================================" << endl;
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (displayChoice < 1 || displayChoice > 2);
                break;
            }
            case 5: {
                int roomChoice;
                // Fixed submenu loop
                do {
                    cout << "========================================" << endl;
                    cout << "1. Check-In" << endl;
                    cout << "2. Check-Out" << endl;
                    cout << "========================================" << endl;
                    cout << "Enter your choice: ";
                    cin >> roomChoice;
                    cin.ignore();
                    if (roomChoice < 1 || roomChoice > 2) {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (roomChoice < 1 || roomChoice > 2);

                if (roomChoice == 1) {
                    // Check-In
                    cout << "========== CHECK-IN ==========" << endl;
                    cout << "Enter room number to check-in: ";
                    int roomToCheck;
                    cin >> roomToCheck;
                    cin.ignore(); // ignore newline before getline

                    cout << "Enter Customer name: ";
                    string customerName;
                    getline(cin, customerName);

                    bool found = false;
                    for (auto& b : myBooking) {
                        if (b.getRoomNumber() == roomToCheck) {
                            if (b.getName() == customerName) {
                                if (!b.isCheckedIn()) {
                                    b.setCheckedIn(true);
                                    cout << "Check-In successful for room " << roomToCheck << "." << endl;
                                    saveHotelFile(allRooms, myBooking);  // update file
                                } else {
                                    cout << "Customer is already checked in to room " << roomToCheck << "." << endl;
                                }
                            } else {
                                cout << "Customer name does not match the booking for room " << roomToCheck << "." << endl;
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "No booking found for room " << roomToCheck << "." << endl;
                    }
                } else if (roomChoice == 2) {
                    // Check-Out
                    cout << "========== CHECK-OUT ==========" << endl;
                    cout << "Enter room number to check-out: ";
                    int roomCheckOut;
                    cin >> roomCheckOut;
                    cin.ignore(); // ignore newline

                    cout << "Enter Customer name: ";
                    string customerName;
                    getline(cin, customerName);

                    bool found = false;
                    for (int i = 0; i < myBooking.size(); i++) {
                        if (myBooking[i].getRoomNumber() == roomCheckOut) {
                            if (myBooking[i].getName() == customerName) {
                                myBooking.erase(myBooking.begin() + i);
                                cout << "Check-Out successful for room " << roomCheckOut << "." << endl;
                                saveHotelFile(allRooms, myBooking);  // update file
                            } else {
                                cout << "Customer name does not match the booking for room " << roomCheckOut << "." << endl;
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "No booking found for room " << roomCheckOut << "." << endl;
                    }
                }
                break;
            }
            case 6: {
                saveHotelFile(allRooms, myBooking);
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    } while (choice != 6);  // Corrected exit condition

    return 0;
}