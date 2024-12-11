//
//  AllCustomers.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

// Customer.cpp
#include "AllCustomers.h"
using namespace std;

AllCustomers::AllCustomers() : firstName(""), lastName(""), accountNumber(""),
    streetAddress(""), city(""), state(""), zipCode(""), phoneNumber("") {}

AllCustomers::AllCustomers(const string& fn, const string& ln, const string& acc,
                 const string& addr, const string& c, const string& st,
                 const string& zip, const string& phone)
    : firstName(fn), lastName(ln), accountNumber(acc), streetAddress(addr),
      city(c), state(st), zipCode(zip), phoneNumber(phone) {}

string AllCustomers::getFullAddress() const {
    return streetAddress + ", " + city + ", " + state + " " + zipCode;
}

bool AllCustomers::operator<(const AllCustomers& other) const {
    return lastName < other.lastName;
}

AllCustomers& AllCustomers::operator=(const AllCustomers& other) {
    if (this != &other) {
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

void AllCustomers::setAddress(const std::string& addr, const std::string& c,
                         const std::string& st, const std::string& zip) {
    streetAddress = addr;
    city = c;
    state = st;
    zipCode = zip;
}
