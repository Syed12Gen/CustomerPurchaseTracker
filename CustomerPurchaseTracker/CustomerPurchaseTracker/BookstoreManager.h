//
//  BookstoreManager.h
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/11/24.
//

#ifndef BOOKSTOREMANAGER_H
#define BOOKSTOREMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "AllCustomers.h"

class BookstoreManager {
public:
    BookstoreManager(const std::string& customerFile, const std::string& purchaseFile);
    void run(); // Start the menu-driven program

private:
    AllCustomers allCustomers; // Holds customer data
    std::string customerFile;  // Path to the customer file

    void displayMenu() const;  // Display menu options
    void handleMenuSelection(int choice); // Process menu options
};

#endif

