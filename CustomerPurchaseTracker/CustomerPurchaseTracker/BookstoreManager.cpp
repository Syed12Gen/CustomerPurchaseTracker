
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
#include <ctime>

using namespace std;

// Constructor and Debug Functions
BookstoreManager::BookstoreManager(const string& custFile, const string& purchFile)
    : customerFileName(custFile), purchaseFileName(purchFile) {
    loadCustomersFromFile();
    loadPurchasesFromFile();
}

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
        if (line.empty()) continue;
        
        stringstream ss(line);
        string fn, ln, acc, addr, city, state, zip, phone;
        getline(ss, fn, '|');
        getline(ss, ln, '|');
        getline(ss, acc, '|');
        getline(ss, addr, '|');
        getline(ss, city, '|');
        getline(ss, state,'|');
        getline(ss, zip, '|');
        getline(ss, phone);
        
        if (!fn.empty() && !ln.empty() && !acc.empty()) {
            customers.emplace_back(fn, ln, acc, addr, city, state, zip, phone);
        }
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
        if (line.empty() || line[0] == '/') continue;
        
        stringstream ss(line);
        string acc, item, date;
        double amount;
        getline(ss, acc, '|');
        getline(ss, item,'|');
        getline(ss, date,'|');
        ss >> amount;
        
        if (validateAccountNumber(acc) && isValidAmount(amount)) {
            purchases.emplace_back(acc, item, date, amount);
        }
    }
}

// Helper Functions
bool BookstoreManager::isValidAccountNumberFormat(const string& accNum) const {
    if (accNum.length() != 6) return false;
    if (accNum.substr(0, 3) != "ACC") return false;
    
    string numPart = accNum.substr(3);
    return all_of(numPart.begin(), numPart.end(), ::isdigit);
}

string BookstoreManager::generateNewAccountNumber() const {
    int maxNum = 0;
    for (const auto& customer : customers) {
        string accNum = customer.getAccountNumber();
        if (accNum.substr(0, 3) == "ACC") {
            try {
                int num = stoi(accNum.substr(3));
                maxNum = max(maxNum, num);
            } catch (...) {}
        }
    }
    
    ostringstream oss;
    oss << "ACC" << setfill('0') << setw(3) << (maxNum + 1);
    return oss.str();
}

bool BookstoreManager::validateAccountNumber(const string& accNum) const {
    if (accNum.empty()) return false;
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    return it != customers.end();
}

bool BookstoreManager::isValidDate(const string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        cout << "\tInvalid date format. Please use YYYY-MM-DD\n";
        return false;
    }
    
    try {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "\tInvalid date values\n";
            return false;
        }
        return true;
    } catch (...) {
        cout << "\tInvalid date format\n";
        return false;
    }
}

bool BookstoreManager::isValidAmount(double amount) const {
    if (amount <= 0.0 || amount >= 10000.0) {
        cout << "\tAmount must be between $0.01 and $9,999.99\n";
        return false;
    }
    return true;
}

bool BookstoreManager::compareCustomers(const AllCustomers& a, const AllCustomers& b, bool ascending) {
    int lastNameComp = a.getLastName().compare(b.getLastName());
    if (lastNameComp != 0) {
        return ascending ? (lastNameComp < 0) : (lastNameComp > 0);
    }
    
    int firstNameComp = a.getFirstName().compare(b.getFirstName());
    if (firstNameComp != 0) {
        return ascending ? (firstNameComp < 0) : (firstNameComp > 0);
    }
    
    return ascending ?
        (a.getAccountNumber() < b.getAccountNumber()) :
        (a.getAccountNumber() > b.getAccountNumber());
}

void BookstoreManager::waitForEnter() const {
    cout << "\n\tPress Enter to continue...";
    cin.get();
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
                cin.ignore();
                printCustomersByOrder(toupper(order) == 'A');
                break;
            }
            case 3: {
                string accNum;
                cout << "\tEnter account number: ";
                getline(cin, accNum);
                printCustomerDetails(accNum);
                waitForEnter();
                break;
            }
            case 4: {
                string accNum;
                cout << "\tEnter account number: ";
                getline(cin, accNum);
                double total = getCustomerTotalSpend(accNum);
                cout << "\tTotal spend: $" << fixed << setprecision(2) << total << endl;
                waitForEnter();
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
                cin.ignore();
                saveData(toupper(newFile) == 'Y');
                waitForEnter();
                break;
            }
            case 0:
                cout << "\n\tThank you for using the Bookstore Management System!\n";
                break;
            default:
                cout << "\n\tInvalid choice. Please try again.\n";
                waitForEnter();
        }
    } while (choice != 0);
}

// Customer Management Functions
void BookstoreManager::addCustomer() {
    string fn, ln, addr, city, state, zip, phone;
    
    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║       Add New Customer              ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    cout << "\t║ Enter customer details:             ║\n";
    cout << "\t╚═════════════════════════════════════╝\n";
    
    cout << "\tFirst Name: ";
    getline(cin, fn);
    cout << "\tLast Name: ";
    getline(cin, ln);
    
    string acc = generateNewAccountNumber();
    cout << "\tGenerated Account Number: " << acc << "\n";
    
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
    waitForEnter();
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
    
    if (!validateAccountNumber(accNum)) {
        cout << "\n\tCustomer not found!\n";
        waitForEnter();
        return;
    }
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
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
    waitForEnter();
}

void BookstoreManager::deleteCustomer() {
    string accNum;
    cout << "\n\tEnter account number to delete: ";
    getline(cin, accNum);
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    if (it != customers.end()) {
        customers.erase(it);
        purchases.erase(
            remove_if(purchases.begin(), purchases.end(),
                [&accNum](const AllPurchases& p) { return p.getAccountNumber() == accNum; }),
            purchases.end()
        );
        cout << "\n\tCustomer and associated purchases deleted successfully!\n";
    } else {
        cout << "\n\tCustomer not found!\n";
    }
    waitForEnter();
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
        cout << "\n\tCustomer not found!\n";
        waitForEnter();
        return;
    }
    
    cout << "\tItem: ";
    getline(cin, item);
    
    do {
        cout << "\tDate (YYYY-MM-DD): ";
        getline(cin, date);
    } while (!isValidDate(date));
    
    do {
        cout << "\tAmount: $";
        cin >> amount;
        cin.ignore();
    } while (!isValidAmount(amount));
    
    purchases.emplace_back(accNum, item, date, amount);
    generateReceipt(accNum, purchases.back());
    cout << "\n\tPurchase added successfully!\n";
    waitForEnter();
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

void BookstoreManager::generateReceipt(const string& accountNum, const AllPurchases& purchase) const {
    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║           PURCHASE RECEIPT         ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accountNum](const AllCustomers& c) { return c.getAccountNumber() == accountNum; });
    
    if (it != customers.end()) {
        cout << "\t║ Customer: " << setw(21) << (it->getFirstName() + " " + it->getLastName()) << "║\n";
        cout << "\t║ Account #: " << setw(20) << accountNum << "║\n";
        cout << "\t╠═════════════════════════════════════╣\n";
        cout << "\t║ Date: " << setw(25) << purchase.getDate() << "║\n";
        cout << "\t║ Item: " << setw(25) << purchase.getItem() << "║\n";
        cout << "\t║ Amount: $" << setw(22) << fixed << setprecision(2) << purchase.getAmount() << "║\n";
        cout << "\t╚═══════════════════════════════════╝\n";
    }
}

void BookstoreManager::addBulkPurchases(const string& accountNum) {
    if (!validateAccountNumber(accountNum)) {
        cout << "\n\tInvalid account number!\n";
        waitForEnter();
        return;
    }

    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║      Add Multiple Purchases         ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    
    string date;
    do {
        cout << "\tEnter date for all purchases (YYYY-MM-DD): ";
        getline(cin, date);
    } while (!isValidDate(date));

    while (true) {
        string item;
        double amount;
        
        cout << "\n\tEnter item (or 'done' to finish): ";
        getline(cin, item);
        if (item == "done") break;
        
        do {
            cout << "\tAmount: $";
            cin >> amount;
            cin.ignore();
        } while (!isValidAmount(amount));
        
        purchases.emplace_back(accountNum, item, date, amount);
        generateReceipt(accountNum, purchases.back());
    }
    
    cout << "\n\tBulk purchases added successfully!\n";
    waitForEnter();
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

// Print Functions
void BookstoreManager::printAllCustomers() const {
    if (customers.empty()) {
        cout << "\n\tNo customers found.\n";
        waitForEnter();
        return;
    }
    
    string border(85, '-');
    string empty(80, ' ');
    
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
    waitForEnter();
}

void BookstoreManager::printCustomersByOrder(bool ascending) {
    vector<AllCustomers> sortedCustomers = customers;
    
    sort(sortedCustomers.begin(), sortedCustomers.end(),
         [ascending](const AllCustomers& a, const AllCustomers& b) {
             return compareCustomers(a, b, ascending);
         });
    
    string border(85, '-');
    string empty(80, ' ');
    
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
    waitForEnter();
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

// File Operations
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


