//
//  main.cpp
//  CustomerPurchaseTracker
//
//  Created by Syed Haider on 12/10/24.
//

// Main.cpp
#include "BookstoreManager.h"
#include <iostream>
using namespace std;

int main () {
    cout << "Welcome to the Bookstore Management System!\n";
    cout << "--------------------------------------\n";
    
    BookstoreManager manager("customers.txt", "purchases.txt");
    manager.debugPrintLoadedData();
    manager.run();
    return 0;
}

