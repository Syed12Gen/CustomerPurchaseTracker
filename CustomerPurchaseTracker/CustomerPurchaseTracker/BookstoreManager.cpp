
//  BookstoreManager.cpp
//  FinalProject_C++
//
//  Created by Syed12Gen on 12/10/24.
//

// BookstoreManager.cpp
#include "BookstoreManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

// Constructor
BookstoreManager::BookstoreManager(const string& custFile, const string& purchFile)
    : customerFileName(custFile), purchaseFileName(purchFile) {
    loadCustomersFromFile();
    loadPurchasesFromFile();
}
// Debug Function - Add it here, after constructor but before other functions
void BookstoreManager::debugPrintLoadedData() const {
    cout << "\nLoaded Customer Data:\n";
    for (const auto& customer : customers) {
        cout << "Account: [" << customer.getAccountNumber() << "] "
             << "Name: [" << customer.getFirstName() << " " << customer.getLastName() << "] "
             << "Phone: [" << customer.getPhoneNumber() << "]\n";
    }
    cout << "\nTotal customers loaded: " << customers.size() << "\n\n";
}
// File Operations
void BookstoreManager::loadCustomersFromFile() {
    ifstream file(customerFileName);
    if (!file) {
        cout << "No existing customer file found. Starting with empty database.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fn, ln, acc, addr, city, state, zip, phone;
        getline(ss, fn,   '|');
        getline(ss, ln,   '|');
        getline(ss, acc,  '|');
        getline(ss, addr, '|');
        getline(ss, city, '|');
        getline(ss, state,'|');
        getline(ss, zip,  '|');
        getline(ss, phone);
        
        
        
        customers.emplace_back(fn, ln, acc, addr, city, state, zip, phone);
    }
}

void BookstoreManager::loadPurchasesFromFile() {
    ifstream file(purchaseFileName);
    if (!file) {
        cout << "No existing purchase file found. Starting with empty purchase history.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string acc, item, date;
        double amount;
        getline(ss, acc, '|');
        getline(ss, item,'|');
        getline(ss, date,'|');
        ss >> amount;
        
        purchases.emplace_back(acc, item, date, amount);
    }
}

// Menu and Main Loop
void BookstoreManager::displayMenu() {
    cout << "\n\t╔════════════════════════════════════════╗\n";
    cout << "\t║     Bookstore Management System        ║\n";
    cout << "\t╠════════════════════════════════════════╣\n";
    cout << "\t║  1.  Print all customers               ║\n";
    cout << "\t║  2.  Print sorted customer list        ║\n";
    cout << "\t║  3.  Print customer details            ║\n";
    cout << "\t║  4.  Print customer total spend        ║\n";
    cout << "\t║  5.  Add new customer                  ║\n";
    cout << "\t║  6.  Add multiple customers            ║\n";
    cout << "\t║  7.  Update customer information       ║\n";
    cout << "\t║  8.  Delete customer                   ║\n";
    cout << "\t║  9.  Add purchase                      ║\n";
    cout << "\t║  10. Add multiple purchases            ║\n";
    cout << "\t║  11. Save data                         ║\n";
    cout << "\t║  0.  Exit                              ║\n";
    cout << "\t╚════════════════════════════════════════╝\n";
    cout << "\n\tEnter your choice: ";
}

void BookstoreManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                printAllCustomers();
                break;
            case 2: {
                char order;
                cout << "\tSort (A)scending or (D)escending? ";
                cin >> order;
                printCustomersByOrder(toupper(order) == 'A');
                break;
            }
            case 3: {
                string accNum;
                cout << "\tEnter account number: ";
                getline(cin, accNum);
                printCustomerDetails(accNum);
                break;
            }
            case 4: {
                string accNum;
                cout << "\tEnter account number: ";
                getline(cin, accNum);
                double total = getCustomerTotalSpend(accNum);
                cout << "\tTotal spend: $" << fixed << setprecision(2) << total << endl;
                break;
            }
            case 5:
                addCustomer();
                break;
            case 6:
                addCustomersRecursive();
                break;
            case 7:
                updateCustomer();
                break;
            case 8:
                deleteCustomer();
                break;
            case 9:
                addPurchase();
                break;
            case 10:
                addPurchasesRecursive();
                break;
            case 11: {
                char newFile;
                cout << "\tCreate new files? (Y/N): ";
                cin >> newFile;
                saveData(toupper(newFile) == 'Y');
                break;
            }
            case 0:
                cout << "\n\tThank you for using the Bookstore Management System!\n";
                break;
            default:
                cout << "\n\tInvalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Customer Management Functions
void BookstoreManager::addCustomer() {
    string fn, ln, acc, addr, city, state, zip, phone;
    
    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║       Add New Customer              ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    cout << "\t║ Enter customer details:             ║\n";
    cout << "\t╚═════════════════════════════════════╝\n";
    
    cout << "\tFirst Name: ";
    getline(cin, fn);
    cout << "\tLast Name: ";
    getline(cin, ln);
    
    do {
        cout << "\tAccount Number: ";
        getline(cin, acc);
    } while (!validateAccountNumber(acc));
    
    cout << "\tStreet Address: ";
    getline(cin, addr);
    cout << "\tCity: ";
    getline(cin, city);
    cout << "\tState: ";
    getline(cin, state);
    cout << "\tZip Code: ";
    getline(cin, zip);
    cout << "\tPhone Number: ";
    getline(cin, phone);
    
    customers.emplace_back(fn, ln, acc, addr, city, state, zip, phone);
    cout << "\n\tCustomer added successfully!\n";
}

void BookstoreManager::addCustomersRecursive() {
    char more;
    addCustomer();
    
    cout << "\n\tAdd another customer? (Y/N): ";
    cin >> more;
    cin.ignore();
    
    if (toupper(more) == 'Y') {
        addCustomersRecursive();
    }
}

void BookstoreManager::updateCustomer() {
    string accNum;
    cout << "\n\tEnter account number to update: ";
    getline(cin, accNum);
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    if (it != customers.end()) {
        string fn, ln, addr, city, state, zip, phone;
        
        cout << "\n\t╔═══════════════════════════════════╗\n";
        cout << "\t║      Update Customer Details        ║\n";
        cout << "\t╠═════════════════════════════════════╣\n";
        cout << "\t║ Press Enter to keep current value   ║\n";
        cout << "\t╚═════════════════════════════════════╝\n";
        
        cout << "\tFirst Name [" << it->getFirstName() << "]: ";
        getline(cin, fn);
        if (!fn.empty()) it->setFirstName(fn);
        
        cout << "\tLast Name [" << it->getLastName() << "]: ";
        getline(cin, ln);
        if (!ln.empty()) it->setLastName(ln);
        
        cout << "\tStreet Address: ";
        getline(cin, addr);
        cout << "\tCity: ";
        getline(cin, city);
        cout << "\tState: ";
        getline(cin, state);
        cout << "\tZip Code: ";
        getline(cin, zip);
        if (!addr.empty() && !city.empty() && !state.empty() && !zip.empty()) {
            it->setAddress(addr, city, state, zip);
        }
        
        cout << "\tPhone Number [" << it->getPhoneNumber() << "]: ";
        getline(cin, phone);
        if (!phone.empty()) it->setPhoneNumber(phone);
        
        cout << "\n\tCustomer information updated successfully!\n";
    } else {
        cout << "\n\tCustomer not found!\n";
    }
}

void BookstoreManager::deleteCustomer() {
    string accNum;
    cout << "\n\tEnter account number to delete: ";
    getline(cin, accNum);
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    if (it != customers.end()) {
        customers.erase(it);
        // Also remove associated purchases
        purchases.erase(
            remove_if(purchases.begin(), purchases.end(),
                [&accNum](const AllPurchases& p) { return p.getAccountNumber() == accNum; }),
            purchases.end()
        );
        cout << "\n\tCustomer and associated purchases deleted successfully!\n";
    } else {
        cout << "\n\tCustomer not found!\n";
    }
}

// Purchase Management Functions
void BookstoreManager::addPurchase() {
    string accNum, item, date;
    double amount;
    
    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║        Add New Purchase             ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    cout << "\t║ Enter purchase details:             ║\n";
    cout << "\t╚═════════════════════════════════════╝\n";
    
    cout << "\tAccount Number: ";
    getline(cin, accNum);
    
    if (!validateAccountNumber(accNum)) {
        cout << "\n\tInvalid account number!\n";
        return;
    }
    
    cout << "\tItem: ";
    getline(cin, item);
    cout << "\tDate (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "\tAmount: $";
    cin >> amount;
    cin.ignore();
    
    purchases.emplace_back(accNum, item, date, amount);
    cout << "\n\tPurchase added successfully!\n";
}

void BookstoreManager::addPurchasesRecursive() {
    char more;
    addPurchase();
    
    cout << "\n\tAdd another purchase? (Y/N): ";
    cin >> more;
    cin.ignore();
    
    if (toupper(more) == 'Y') {
        addPurchasesRecursive();
    }
}

double BookstoreManager::getCustomerTotalSpend(const string& accountNum) const {
    double total = 0.0;
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNum) {
            total += purchase.getAmount();
        }
    }
    return total;
}

// Helper Functions
bool BookstoreManager::validateAccountNumber(const string& accNum) const {
    if (accNum.empty()) return false;
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    return it != customers.end();
}

void BookstoreManager::printAllCustomers() const {
    if (customers.empty()) {
        cout << "\n\tNo customers found.\n";
        return;
    }
    
    string border(85, '-');    // Using regular equals sign instead of double line
       string empty(80, ' ');     // For title centering
       
       cout << "\n\t+" << border << "+\n";
    cout << "\t|" << setw(45) << "Customer List";
    cout << setw(42) << " |\n";
       cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
       cout << "\t| Account# |       Name         |    Phone     |            Address                   |\n";
       cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
       
       for (const auto& customer : customers) {
           cout << "\t| " << setw(8) << customer.getAccountNumber()
                << " | " << setw(18) << (customer.getFirstName() + " " + customer.getLastName())
                << " | " << setw(12) << customer.getPhoneNumber()
                << " | " << setw(36) << customer.getFullAddress()
                << " |\n";
       }
       
       cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
   }

void BookstoreManager::printCustomersByOrder(bool ascending) {
    vector<AllCustomers> sortedCustomers = customers;
    if (ascending) {
        sort(sortedCustomers.begin(), sortedCustomers.end());
    } else {
        sort(sortedCustomers.rbegin(), sortedCustomers.rend());
    }
    
    string border(85, '-');    // Match the border length
      string empty(80, ' ');     // For title centering
      
      cout << "\n\t+" << border << "+\n";
      cout << "\t|" << setw(45) << (ascending ? "Ascending Customer List" : "Descending Customer List");
      cout << setw(42) << " |\n";
      cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
      cout << "\t| Account# |       Name         |    Phone     |            Address                   |\n";
      cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
      
      for (const auto& customer : sortedCustomers) {
          cout << "\t| " << setw(8) << customer.getAccountNumber()
               << " | " << setw(18) << (customer.getFirstName() + " " + customer.getLastName())
               << " | " << setw(12) << customer.getPhoneNumber()
               << " | " << setw(36) << customer.getFullAddress()
               << " |\n";
      }
      
      cout << "\t+----------+--------------------+--------------+--------------------------------------+\n";
  }

void BookstoreManager::printCustomerDetails(const string& accountNum) const {
    auto it = find_if(customers.begin(), customers.end(),
        [&accountNum](const AllCustomers& c) { return c.getAccountNumber() == accountNum; });
    
    if (it != customers.end()) {
        cout << "\n\t╔═══════════════════════════════════╗\n";
        cout << "\t║        Customer Details             ║\n";
        cout << "\t╠═════════════════════════════════════╣\n";
        cout << "\t║ Name: " << setw(24) << (it->getFirstName() + " " + it->getLastName()) << "║\n";
        cout << "\t║ Account #: " << setw(20) << it->getAccountNumber() << "║\n";
        cout << "\t║ Address: " << setw(22) << it->getFullAddress() << "║\n";
        cout << "\t║ Phone: " << setw(24) << it->getPhoneNumber() << "║\n";
        
        cout << "\t╠═════════════════════════════════════╣\n";
        cout << "\t║        Purchase History             ║\n";
        cout << "\t╠═════════════════════════════════════╣\n";
        
        bool hasPurchases = false;
        double totalSpend = 0.0;
        
        for (const auto& purchase : purchases) {
            if (purchase.getAccountNumber() == accountNum) {
                hasPurchases = true;
                totalSpend += purchase.getAmount();
                cout << "\t║ " << purchase.getDate() << " - "
                     << setw(20) << purchase.getItem() << " - $"
                     << fixed << setprecision(2)
                     << purchase.getAmount() << "  ║\n";
            }
        }
        
        if (!hasPurchases) {
            cout << "\t║      No purchase history        ║\n";
        } else {
            cout << "\t╠═══════════════════════════════════╣\n";
            cout << "\t║ Total Spend: $" << setw(17) << fixed << setprecision(2) << totalSpend << "║\n";
        }
        cout << "\t╚═══════════════════════════════════╝\n";
    } else {
        cout << "\n\tCustomer not found!\n";
    }
}

void BookstoreManager::saveData(bool createNewFiles) {
    string custFile = createNewFiles ? "customers_new.txt" : customerFileName;
    string purchFile = createNewFiles ? "purchases_new.txt" : purchaseFileName;
    
    saveCustomersToFile(custFile);
    savePurchasesToFile(purchFile);
    
    cout << "\n\tData saved successfully!\n";
}

void BookstoreManager::saveCustomersToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& customer : customers) {
        file << customer.getFirstName() << "|"
             << customer.getLastName() << "|"
             << customer.getAccountNumber() << "|"
             << customer.getFullAddress() << "|"
             << customer.getPhoneNumber() << "\n";
    }
}

void BookstoreManager::savePurchasesToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& purchase : purchases) {
        file << purchase.getAccountNumber() << "|"
             << purchase.getItem() << "|"
             << purchase.getDate() << "|"
             << purchase.getAmount() << "\n";
    }
}
