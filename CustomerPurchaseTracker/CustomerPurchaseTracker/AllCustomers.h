//
//  AllCustomers.h
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/10/24.
//

#ifndef ALLCUSTOMERS_H
#define ALLCUSTOMERS_H

#include <string>
#include <vector>  // Include vector for collection
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
    AllCustomers();   // Default constructor
    AllCustomers(const string& fn, const string& ln, const string& acc,
                 const string& addr, const string& c, const string& st,
                 const string& zip, const string& phone);

    // New static function to load customer data
    static vector<AllCustomers> loadFromFile(const string& filename);

    // Print all customers (non-static as it operates on an instance)
    void printAll() const;

    // Getter methods
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getAccountNumber() const { return accountNumber; }
    string getFullAddress() const;
    string getPhoneNumber() const { return phoneNumber; }

    // Setter methods
    void setFirstName(const string& fn) { firstName = fn; }
    void setLastName(const string& ln) { lastName = ln; }
    void setAddress(const string& addr, const string& c,
                    const string& st, const string& zip);
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }

    // Operator overloads
    bool operator<(const AllCustomers& other) const;         // Sorting comparison
    AllCustomers& operator=(const AllCustomers& other);      // Assignment operator
};

#endif  // End of header guard
