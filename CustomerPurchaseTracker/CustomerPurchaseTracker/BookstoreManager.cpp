
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
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Constructor and Debug Functions
BookstoreManager::BookstoreManager(const string& custFile, const string& purchFile)
    : customerFileName(custFile), purchaseFileName(purchFile) {
    loadCustomersFromFile();
    loadPurchasesFromFile();
}

// Debugging utility: Prints all loaded customer data to the console.
void BookstoreManager::debugPrintLoadedData() const {
    cout << "\nLoaded Customer Data:\n";
    for (const auto& customer : customers) {
        cout << "Account: [" << customer.getAccountNumber() << "] "
             << "Name: [" << customer.getFirstName() << " " << customer.getLastName() << "] "
             << "Phone: [" << customer.getPhoneNumber() << "]\n";
    }
    cout << "\nTotal customers loaded: " << customers.size() << "\n\n";
}

// Loads customer data from a file and populates the `customers` vector.
// Assumes a pipe-delimited format for customer details
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
        
        // Ensure valid customer details before adding to the list
        if (!fn.empty() && !ln.empty() && !acc.empty()) {
            customers.emplace_back(fn, ln, acc, addr, city, state, zip, phone);
        }
    }
}

// Loads purchase data from a file and populates the `purchases` vector.
// Assumes a pipe-delimited format for purchase details.
void BookstoreManager::loadPurchasesFromFile() {
    ifstream file(purchaseFileName);
    if (!file) {
        cout << "No existing purchase file found. Starting with empty purchase history.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '/') continue; // Skip comments and empty lines
        
        stringstream ss(line);
        string acc, item, date;
        double amount;
        getline(ss, acc, '|');
        getline(ss, item,'|');
        getline(ss, date,'|');
        ss >> amount;
        
        // Validate account number and amount before adding to the list
        if (validateAccountNumber(acc) && isValidAmount(amount)) {
            purchases.emplace_back(acc, item, date, amount);
        }
    }
}

// Validates the format of an account number (e.g., "ACC123").
// Ensures the account number starts with "ACC" and is followed by digits.
bool BookstoreManager::isValidAccountNumberFormat(const string& accNum) const {
    if (accNum.length() != 6) return false;
    if (accNum.substr(0, 3) != "ACC") return false;
    
    string numPart = accNum.substr(3);
    return all_of(numPart.begin(), numPart.end(), ::isdigit);
}

// Generates a new unique account number in the format "ACC###".
// Finds the highest existing account number and increments it.
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

// Checks if a given account number exists in the customer database.
bool BookstoreManager::validateAccountNumber(const string& accNum) const {
    if (accNum.empty()) return false;
    
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    return it != customers.end();
}

// Validates a date in the format "YYYY-MM-DD".
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

// Validates a purchase amount to ensure it falls within a valid range.
bool BookstoreManager::isValidAmount(double amount) const {
    if (amount <= 0.0 || amount >= 10000.0) {
        cout << "\tAmount must be between $0.01 and $9,999.99\n";
        return false;
    }
    return true;
}

// Compares two customers based on their account numbers for sorting.
// Supports ascending or descending order based on a flag.
bool BookstoreManager::compareCustomers(const AllCustomers& a, const AllCustomers& b, bool ascending) {
    // Extract numeric parts
    int aNum = stoi(a.getAccountNumber().substr(3));
    int bNum = stoi(b.getAccountNumber().substr(3));
    
    // Return comparison based on ascending/descending flag
    if (ascending) {
        return aNum < bNum;
    } else {
        return aNum > bNum;
    }
}

// Waits for the user to press Enter before continuing.
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

// Main execution loop for the Bookstore Manager.
// Displays a menu, takes user input for an action, and calls the corresponding function.
void BookstoreManager::run() {
    int choice;
    do {
        displayMenu(); // Display the menu
        
        // Input validation to ensure valid menu choice.
        while (!(cin >> choice) || choice < 0 || choice > 11) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\n\tInvalid input. Please enter a number corresponding to the menu options (0-11): ";
        }
        cin.ignore(); // Consume any leftover input
        
       // Execute the function corresponding to the user's choice.
        switch (choice) {
            case 1:
                printAllCustomers();
                break;
            case 2: {
                char order;
                cout << "\tSort (A)scending or (D)escending? ";
                cin >> order;
                cin.ignore();

                // Validate sorting choice
                while (toupper(order) != 'A' && toupper(order) != 'D') {
                    cout << "\n\tInvalid input. Please enter 'A' for Ascending or 'D' for Descending: ";
                    cin >> order;
                    cin.ignore();
                }
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

                // Validate Yes/No choice
                while (toupper(newFile) != 'Y' && toupper(newFile) != 'N') {
                    cout << "\n\tInvalid input. Please enter 'Y' for Yes or 'N': ";
                    cin >> newFile;
                    cin.ignore();
                }
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


// Adds a single new customer to the system.
// Prompts the user for customer details and generates a new account number.
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

// Adds multiple customers to the system by repeatedly calling `addCustomer`.
// Recursively prompts the user to add another customer.
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

// Updates the details of an existing customer.
// Prompts the user for new values or allows keeping existing values by pressing Enter.
void BookstoreManager::updateCustomer() {
    string accNum;
    cout << "\n\tEnter account number to update: ";
    getline(cin, accNum);
    
    // Validate account number
    if (!validateAccountNumber(accNum)) {
        cout << "\n\tCustomer not found!\n";
        waitForEnter();
        return;
    }
    
    // Locate the customer by account number.
    auto it = find_if(customers.begin(), customers.end(),
        [&accNum](const AllCustomers& c) { return c.getAccountNumber() == accNum; });
    
    string fn, ln, addr, city, state, zip, phone;
    
    cout << "\n\t╔═══════════════════════════════════╗\n";
    cout << "\t║      Update Customer Details        ║\n";
    cout << "\t╠═════════════════════════════════════╣\n";
    cout << "\t║ Press Enter to keep current value   ║\n";
    cout << "\t╚═════════════════════════════════════╝\n";
    
    // Update customer details or keep current values if input is empty.
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

// Deletes a customer and all their associated purchase records.
// Prompts the user for the account number and removes matching data.
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

// Generates and displays a receipt for a specific purchase.
// Displays customer information, purchase details, and formatted output.
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

// Adds multiple purchases for a specific customer.
// Prompts the user for item names, amounts, and validates inputs.
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

// Calculates the total amount spent by a specific customer across all purchases.
double BookstoreManager::getCustomerTotalSpend(const string& accountNum) const {
    double total = 0.0;
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNum) {
            total += purchase.getAmount();
        }
    }
    return total;
}

// Prints a formatted list of all customers in the system.
// Displays account number, name, phone number, and address.
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

// Prints customers sorted by their account numbers in ascending or descending order.
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

// Prints detailed information for a specific customer.
// Includes name, account number, address, phone number, and purchase history.
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

// Saves customer and purchase data to files.
// Prompts for new filenames if the user chooses to create new files; otherwise, uses default filenames.
void BookstoreManager::saveData(bool createNewFiles) {
    string custFile, purchFile;

    if (createNewFiles) {
        // Prompt the user to enter a new filename for customer data.
        cout << "\n\tEnter new filename for customer data (e.g., new_customers.txt): ";
        getline(cin, custFile);
        if (custFile.empty()) custFile = "new_customers.txt"; // Default name

        // Prompt the user to enter a new filename for purchase data.
        cout << "\tEnter new filename for purchase data (e.g., new_purchases.txt): ";
        getline(cin, purchFile);
        if (purchFile.empty()) purchFile = "new_purchases.txt"; // Default name
    } else {
        // Use existing filenames for saving data.
        custFile = customerFileName;
        purchFile = purchaseFileName;
    }
    
    // Save customer and purchase data to the specified files.
    saveCustomersToFile(custFile);
    savePurchasesToFile(purchFile);
    
    // Confirm successful saving of data.
    cout << "\n\tData saved successfully to:\n\t- " << custFile << "\n\t- " << purchFile << "\n";
}

// Writes all customer data to a specified file.
// Formats data in a pipe-delimited format (e.g., "FirstName|LastName|AccountNumber|Address|PhoneNumber").
void BookstoreManager::saveCustomersToFile(const string& filename) {
    string filePath = "/Users/syed12gen/Documents/Projects/TheLastProject/" + filename; // Save to the current directory
    
    // Open the file for writing.
    ofstream file(filePath);
    if (!file) {
        cerr << "\n\tError: Could not create or write to file " << filePath << "\n";
        return;
    }
    
    // Write each customer's details to the file in pipe-delimited format.
    for (const auto& customer : customers) {
        file << customer.getFirstName() << "|"
             << customer.getLastName() << "|"
             << customer.getAccountNumber() << "|"
             << customer.getFullAddress() << "|"
             << customer.getPhoneNumber() << "\n";
    }
    
    // Close the file after writing all data.
    file.close();
    cout << "\n\tCustomer data successfully written to " << filePath << "\n";
}

// Writes all purchase data to a specified file.
// Formats data in a pipe-delimited format (e.g., "AccountNumber|Item|Date|Amount").
void BookstoreManager::savePurchasesToFile(const string& filename) {
    // Construct the file path (absolute path in this case).
    string filePath = "/Users/syed12gen/Documents/Projects/TheLastProject/" + filename; // Absolute path
    
    // Open the file for writing.
    ofstream file(filePath);
    if (!file) {
        cerr << "\n\tError: Could not create or write to file " << filePath << "\n";
        return; // Exit if the file cannot be created or opened.
    }
    
    // Write each purchase's details to the file in pipe-delimited format.
    for (const auto& purchase : purchases) {
        file << purchase.getAccountNumber() << "|"
             << purchase.getItem() << "|"
             << purchase.getDate() << "|"
             << purchase.getAmount() << "\n";
    }
    
    // Close the file after writing all data.
    file.close();
    cout << "\n\tPurchase data successfully written to " << filePath << "\n";
}

