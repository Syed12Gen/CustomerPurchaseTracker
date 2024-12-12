#ifndef BOOKSTORE_MANAGER_H
#define BOOKSTORE_MANAGER_H

#include <vector>
#include <string>
#include "AllCustomers.h"
#include "AllPurchases.h"

using namespace std;

class BookstoreManager {
private:
    vector<AllCustomers> customers;
    vector<AllPurchases> purchases;
    string customerFileName;
    string purchaseFileName;

    // Helper functions for file operations
    void loadCustomersFromFile();
    void loadPurchasesFromFile();
    void saveCustomersToFile(const string& filename);
    void savePurchasesToFile(const string& filename);

    // Helper functions for validation and generation
    bool validateAccountNumber(const string& accNum) const;
    bool isValidAccountNumberFormat(const string& accNum) const;
    string generateNewAccountNumber() const;
    bool isValidDate(const string& date) const;
    bool isValidAmount(double amount) const;
    static bool compareCustomers(const AllCustomers& a, const AllCustomers& b, bool ascending);
    void waitForEnter() const;
    
    // Receipt generation
    void generateReceipt(const string& accountNum, const AllPurchases& purchase) const;

public:
    // Constructor and debug
    BookstoreManager(const string& custFile, const string& purchFile);
    void debugPrintLoadedData() const;
    
    // Customer management
    void addCustomer();
    void addCustomersRecursive();
    void updateCustomer();
    void deleteCustomer();
    void printAllCustomers() const;
    void printCustomersByOrder(bool ascending);
    void printCustomerDetails(const string& accountNum) const;
    
    // Purchase management
    void addPurchase();
    void addPurchasesRecursive();
    void addBulkPurchases(const string& accountNum);
    double getCustomerTotalSpend(const string& accountNum) const;
    
    // File operations
    void saveData(bool createNewFiles);
    
    // Menu and navigation
    void displayMenu();
    void run();
};

#endif
