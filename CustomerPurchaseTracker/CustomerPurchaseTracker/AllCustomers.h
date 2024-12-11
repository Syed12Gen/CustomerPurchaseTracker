//
//  AllCustomers.h
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

#ifndef ALLCUSTOMERS_H    // Header guard to prevent multiple inclusions
#define ALLCUSTOMERS_H

#include <string>
using namespace std;

class AllCustomers {
private:
    // Customer personal information
    string firstName;      // Customer's first name
    string lastName;       // Customer's last name
    string accountNumber;  // Unique customer identifier
    
    // Customer address information
    string streetAddress;  // Street address including house/apt number
    string city;          // City name
    string state;         // State/province
    string zipCode;       // Postal/ZIP code
    string phoneNumber;   // Contact phone number

public:
    // Constructors
    AllCustomers();   // Default constructor - initializes empty customer
    
    // Parameterized constructor - creates customer with all information
    AllCustomers(const string& fn, const string& ln, const string& acc,
                const string& addr, const string& c, const string& st,
                const string& zip, const string& phone);

    // Getter methods - return customer information
    string getFirstName() const { return firstName; }     // Returns first name
    string getLastName() const { return lastName; }       // Returns last name
    string getAccountNumber() const { return accountNumber; }  // Returns account number
    string getFullAddress() const;    // Returns formatted full address
    string getPhoneNumber() const { return phoneNumber; } // Returns phone number

    // Setter methods - modify customer information
    void setFirstName(const string& fn) { firstName = fn; }   // Update first name
    void setLastName(const string& ln) { lastName = ln; }     // Update last name
    
    // Update complete address
    void setAddress(const string& addr, const string& c,
                   const string& st, const string& zip);
                   
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }  // Update phone number

    // Operator overloads for functionality
    bool operator<(const AllCustomers& other) const;         // For sorting customers
    AllCustomers& operator=(const AllCustomers& other);      // Assignment operator
};

#endif  // End of header guard
