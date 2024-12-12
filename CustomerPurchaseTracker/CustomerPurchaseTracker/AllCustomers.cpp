//
//  AllCustomers.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

#include "AllCustomers.h"  // Include header file for class definition
using namespace std;

// Default constructor: Initializes all member variables to empty strings.
AllCustomers::AllCustomers()
    : firstName(""), lastName(""), accountNumber(""),
      streetAddress(""), city(""), state(""), zipCode(""), phoneNumber("") {}

// Parameterized constructor: Initializes the object with the provided values.
AllCustomers::AllCustomers(const string& fn, const string& ln, const string& acc,
                           const string& addr, const string& c, const string& st,
                           const string& zip, const string& phone)
    : firstName(fn), lastName(ln), accountNumber(acc), streetAddress(addr),
      city(c), state(st), zipCode(zip), phoneNumber(phone) {}

// Combines and returns the full address as a single formatted string.
string AllCustomers::getFullAddress() const {
    return streetAddress + ", " + city + ", " + state + " " + zipCode;
}

// Overloaded '<' operator for sorting customers by account number.
// Extracts and compares the numeric part of the account numbers.
bool AllCustomers::operator<(const AllCustomers& other) const {
    // Convert account numbers (after "ACC") to integers for comparison
    int thisNum = stoi(accountNumber.substr(3)); // Extract numeric part of this account
    int otherNum = stoi(other.accountNumber.substr(3)); // Extract numeric part of other account
    return thisNum < otherNum; // Return true if this account number is smaller
}

// Overloaded '=' operator for assignment.
// Copies all member variables from the source object to this object.
AllCustomers& AllCustomers::operator=(const AllCustomers& other) {
    // Avoid self-assignment
    if (this != &other) {
        // Copy all data members
        firstName = other.firstName;
        lastName = other.lastName;
        accountNumber = other.accountNumber;
        streetAddress = other.streetAddress;
        city = other.city;
        state = other.state;
        zipCode = other.zipCode;
        phoneNumber = other.phoneNumber;
    }
    return *this; // Return a reference to the current object
}

// Updates the address information for the customer.
// @param addr: New street address.
// @param c: New city.
// @param st: New state or province.
// @param zip: New ZIP/postal code.
void AllCustomers::setAddress(const string& addr, const string& c,
                              const string& st, const string& zip) {
    streetAddress = addr;
    city = c;
    state = st;
    zipCode = zip;
}

