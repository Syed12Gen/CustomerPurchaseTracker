// CustomerPurchaseTracker
//
// Created by Syed12Gen on 12/10/24.
//

#ifndef ALLCUSTOMERS_H
#define ALLCUSTOMERS_H

#include <string>
#include <vector>  // For storing multiple customer objects
using namespace std;

// Represents a customer with personal, address, and contact information.
class AllCustomers {
private:
    string firstName;      // Customer's first name
    string lastName;       // Customer's last name
    string accountNumber;  // Customer's unique account number

    string streetAddress;  // Customer's street address
    string city;           // City where the customer resides
    string state;          // State or province of the customer
    string zipCode;        // Postal code of the customer
    string phoneNumber;    // Customer's contact phone number

public:
    // Default constructor: Initializes an empty customer.
    AllCustomers();

    // Parameterized constructor: Initializes a customer with given details.
    AllCustomers(const string& fn, const string& ln, const string& acc,
                 const string& addr, const string& c, const string& st,
                 const string& zip, const string& phone);

    // Loads customer data from a file and returns a vector of AllCustomers objects.
    // @param filename: Name of the file to load data from.
    static vector<AllCustomers> loadFromFile(const string& filename);

    // Prints customer information to the console.
    void printAll() const;

    // Getter for customer's first name.
    string getFirstName() const { return firstName; }

    // Getter for customer's last name.
    string getLastName() const { return lastName; }

    // Getter for customer's account number.
    string getAccountNumber() const { return accountNumber; }

    // Getter for customer's full address as a formatted string.
    string getFullAddress() const;

    // Getter for customer's phone number.
    string getPhoneNumber() const { return phoneNumber; }

    // Setter for customer's first name.
    void setFirstName(const string& fn) { firstName = fn; }

    // Setter for customer's last name.
    void setLastName(const string& ln) { lastName = ln; }

    // Updates customer's address details.
    // @param addr: New street address.
    // @param c: New city.
    // @param st: New state or province.
    // @param zip: New ZIP/postal code.
    void setAddress(const string& addr, const string& c,
                    const string& st, const string& zip);

    // Setter for customer's phone number.
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }

    // Overloaded '<' operator for sorting customers.
    // Compares this object with another AllCustomers object.
    bool operator<(const AllCustomers& other) const;

    // Overloaded '=' operator for assignment.
    // Copies data from another AllCustomers object.
    AllCustomers& operator=(const AllCustomers& other);
};

#endif  // End of header guard

