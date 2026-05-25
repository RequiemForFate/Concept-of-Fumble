#include <iostream>
#include <cctype>   //toupper
#include <ctime>    //struct time
#include <iomanip>  
#include <fstream>  //ofstream
#include <string>   // getline()
using namespace std;

// Function to convert hexadecimal string to binary string
string hexToBinary(const string& hex) {
    string binary = "";
    for (char hexDigit : hex) {
        switch (toupper(hexDigit)) {
            case '0': binary += "0000"; break;
            case '1': binary += "0001"; break;
            case '2': binary += "0010"; break;
            case '3': binary += "0011"; break;
            case '4': binary += "0100"; break;
            case '5': binary += "0101"; break;
            case '6': binary += "0110"; break;
            case '7': binary += "0111"; break;
            case '8': binary += "1000"; break;
            case '9': binary += "1001"; break;
            case 'A': binary += "1010"; break;
            case 'B': binary += "1011"; break;
            case 'C': binary += "1100"; break;
            case 'D': binary += "1101"; break;
            case 'E': binary += "1110"; break;
            case 'F': binary += "1111"; break;
            default: 
                cerr << "Invalid hexadecimal digit: " << hexDigit << endl;
                return "";
        }
    }
    return binary;
}

// Function to remove spaces from binary string and validate
string processBinary(const string& input) {
    string binary = "";
    for (char c : input) {
        if (c == ' ') {
            continue;  // Skip spaces
        } else if (c == '0' || c == '1') {
            binary += c;
        } else {
            cerr << "Invalid binary digit: " << c << endl;
            return "";
        }
    }
    return binary;
}

// Function to format binary string with spaces every 4 bits
string formatBinary(const string& binary) {
    string formatted = "";
    for (int i = 0; i < binary.length(); i++) {
        if (i > 0 && i % 4 == 0) {
            formatted += " ";
        }
        formatted += binary[i];
    }
    return formatted;
}

// Function to convert binary string to hexadecimal
string binaryToHex(const string& binary) {
    if (binary.length() % 4 != 0) {
        cerr << "Binary string length must be a multiple of 4" << endl;
        return "";
    }
    
    string hex = "";
    for (int i = 0; i < binary.length(); i += 4) {
        string nibble = binary.substr(i, 4);
        int value = stoi(nibble, nullptr, 2);
        hex += "0123456789ABCDEF"[value];
    }
    return hex;
}
int main() 
{    
    char ch;    
    
    while(1)
    {
        cout << "\n========== MENU ==========" << endl;
        cout << "[A] Hexadecimal to Binary" << endl;
        cout << "[B] Binary to Hexadecimal" << endl;
        cout << "[X] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        
        switch (toupper(ch))
        {
        case 'A':
            {
                string hexString;
                cout << "Enter a number in Hexadecimal Notations: ";
                cin >> hexString;

                string binaryString = hexToBinary(hexString);
                if (!binaryString.empty()) {
                    cout << "Binary Equivalent: " << binaryString << endl;
                }
            }
            break;
        case 'B':
            {
                string binaryString;
                cout << "Enter a binary number: ";
                cin.ignore();  // Clear the newline from previous input
                getline(cin, binaryString);

                string cleanBinary = processBinary(binaryString);
                if (!cleanBinary.empty()) {
                    string hexResult = binaryToHex(cleanBinary);
                    if (!hexResult.empty()) {
                        cout << "Hexadecimal representation: " << hexResult << endl;
                        cout << "Binary Equivalent: " << formatBinary(cleanBinary) << endl;
                    }
                }
            }
            break;
        case 'X':
        case 'x':
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}