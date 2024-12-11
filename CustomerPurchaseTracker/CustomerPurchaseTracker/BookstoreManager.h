//
//  BookstoreManager.h
//  CustomerPurchaseTracker
//
//  Created by Syed12Gen on 12/11/24.
//

// BookstoreManager.h
#ifndef BOOKSTORE_MANAGER_H
#define BOOKSTORE_MANAGER_H

#include <vector>
#include "AllCustomers.h"
#include "AllPurchases.h"
using namespace std;

class BookstoreManager {
private:
    vector<AllCustomers> customers;
    vector<AllPurchases> purchases;
    string customerFileName;
    string purchaseFileName;

    // Helper functions
    void loadCustomersFromFile();
    void loadPurchasesFromFile();
    void saveCustomersToFile(const std::string& filename);
    void savePurchasesToFile(const std::string& filename);
    bool validateAccountNumber(const std::string& accNum) const;

public:
    void debugPrintLoadedData() const;
    BookstoreManager(const std::string& custFile, const std::string& purchFile);
    
    
    // Customer management
    void addCustomer();
    void addCustomersRecursive();
    void updateCustomer();
    void deleteCustomer();
    void printAllCustomers() const;
    void printCustomersByOrder(bool ascending);
    void printCustomerDetails(const std::string& accountNum) const;
    
    // Purchase management
    void addPurchase();
    void addPurchasesRecursive();
    double getCustomerTotalSpend(const std::string& accountNum) const;
    
    // File operations
    void saveData(bool createNewFiles);
    
    // Menu
    void displayMenu();
    void run();
};

#endif
