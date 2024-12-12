//
//  AllPurchases.h
//  CustomerPurchaseTracker

#ifndef ALLPURCHASES_H    // Header guard to prevent multiple inclusions
#define ALLPURCHASES_H

#include <string>
using namespace std;

class AllPurchases {
private:
    // Purchase transaction information
    string accountNumber;  // Customer account number who made the purchase
    string item;          // Name/description of item purchased
    string date;          // Date of purchase (format: YYYY-MM-DD)
    double amount;        // Purchase amount in dollars

public:
    // Constructors
    AllPurchases();   // Default constructor - initializes empty purchase
    
    // Parameterized constructor - creates purchase with all information
    AllPurchases(const string& acc, const string& i,
                const string& d, double amt);

    // Getter methods - return purchase information
    string getAccountNumber() const { return accountNumber; }  // Returns linked account number
    string getItem() const { return item; }                   // Returns item description
    string getDate() const { return date; }                   // Returns purchase date
    double getAmount() const { return amount; }               // Returns purchase amount

    // Operator overloads
    AllPurchases& operator=(const AllPurchases& other);       // Assignment operator
};

#endif  // End of header guard


