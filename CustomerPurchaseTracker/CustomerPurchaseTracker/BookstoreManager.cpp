//
//  BookstoreManager.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/11/24.
//

#include "BookstoreManager.h"
#include <iostream>
#include <limits>
using namespace std;

// Constructor
BookstoreManager::BookstoreManager(const string& customerFile, const string& purchaseFile)
    : customerFile(customerFile) {
    allCustomers.loadFromFile(customerFile); // Load customers from file
}

// Main loop
void BookstoreManager::run() {
    int choice = 0;
    do {
        displayMenu(); // Show menu
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // Clear input error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        handleMenuSelection(choice); // Process choice
    } while (choice != 2); // Exit when choice is 2
}

// Display menu
void BookstoreManager::displayMenu() const {
    cout << "\n==== Bookstore Manager Menu ====\n";
    cout << "1. Print all customers\n";
    cout << "2. Exit\n";
    cout << "================================\n";
}

// Handle menu options
void BookstoreManager::handleMenuSelection(int choice) {
    switch (choice) {
    case 1:
        allCustomers.printAll(); // Call AllCustomers method to print all customers
        break;
    case 2:
        cout << "Exiting the program. Goodbye!\n";
        break;
    default:
        cout << "Invalid option. Please try again.\n";
    }
}
