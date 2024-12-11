//
//  AllCustomers.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

#include "AllCustomers.h"
using namespace std;

// Default constructor - initializes all string members to empty strings
AllCustomers::AllCustomers() : firstName(""), lastName(""), accountNumber(""),
    streetAddress(""), city(""), state(""), zipCode(""), phoneNumber("") {}

// Parameterized constructor - initializes customer with provided information
AllCustomers::AllCustomers(const string& fn, const string& ln, const string& acc,
                         const string& addr, const string& c, const string& st,
                         const string& zip, const string& phone)
    : firstName(fn), lastName(ln), accountNumber(acc), streetAddress(addr),
      city(c), state(st), zipCode(zip), phoneNumber(phone) {}

// Returns formatted full address string
string AllCustomers::getFullAddress() const {
    return streetAddress + ", " + city + ", " + state + " " + zipCode;
}

// Comparison operator for sorting (compares by last name)
bool AllCustomers::operator<(const AllCustomers& other) const {
    return lastName < other.lastName;
}

// Assignment operator - copies all data from one customer to another
AllCustomers& AllCustomers::operator=(const AllCustomers& other) {
    if (this != &other) {  // Check for self-assignment
        firstName = other.firstName;
        lastName = other.lastName;
        accountNumber = other.accountNumber;
        streetAddress = other.streetAddress;
        city = other.city;
        state = other.state;
        zipCode = other.zipCode;
        phoneNumber = other.phoneNumber;
    }
    return *this;
}

// Updates all address components at once
void AllCustomers::setAddress(const string& addr, const string& c,
                            const string& st, const string& zip) {
    streetAddress = addr;
    city = c;
    state = st;
    zipCode = zip;
}
