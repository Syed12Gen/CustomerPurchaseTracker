//
//  AllPurchases.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

#include "AllPurchases.h"
using namespace std;

// Default constructor - initializes empty purchase with zero amount
AllPurchases::AllPurchases() : accountNumber(""), item(""), date(""), amount(0.0) {}

// Parameterized constructor - initializes purchase with provided information
AllPurchases::AllPurchases(const string& acc, const string& i,
                         const string& d, double amt)
    : accountNumber(acc), item(i), date(d), amount(amt) {}

// Assignment operator - copies all data from one purchase to another
AllPurchases& AllPurchases::operator=(const AllPurchases& other) {
    if (this != &other) {  // Check for self-assignment
        accountNumber = other.accountNumber;
        item = other.item;
        date = other.date;
        amount = other.amount;
    }
    return *this;
}

