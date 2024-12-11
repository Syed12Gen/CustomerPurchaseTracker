# My Thought Process While Solving This Problem

This is not a typical README file; it's a record of my thought process while solving the problem. I feel like I should do this more often as it keeps me engaged with the problem. I also always feel sad about not documenting the problems and errors I dealt with and how I solved them because I forget after a few days. This is also a good exercise for staying engaged, and it helps me quickly jog my memory when I face the same errors and issues in the future. You could say this README is my hobby. I have created another README specifically for the project, where you can read about how the project works.

---

## 📜 Project Requirements

This project simulates a **bookstore management system** with the following features:

- **Customer Management**: Load customer account data from a file into a vector of the `AllCustomers` class.
- **Purchase Management**: Load purchase records from a file into a vector of the `AllPurchases` class.
- **Dynamic Data Handling**: Supports files of any size and dynamically adjusts storage as needed.

### Classes Overview (From Project Question)
- **`AllCustomers`**: Manages customer account details.
- **`AllPurchases`**: Tracks purchase records associated with customers.

---

## 🧠 My Understanding

### Why Use `Vector`?
- A `vector` is a dynamic array that grows and shrinks as needed.
- Key advantages:
  - `push_back()`: Add elements dynamically.
  - `size()`: Get the current number of elements.
  - Memory safety: Reduces risks of leaks and segmentation faults through automatic memory management.

---

## 🗂️ Data Models

### `AllCustomers` Data Model
**Attributes (From Project Requirements)**:
- First Name
- Last Name
- Account #
- Street Address
- City
- State
- Zip Code
- Phone Number

**💡 My Understanding**:
- These attributes will be **private** members within the `AllCustomers` class.
- Each attribute will use a suitable data type (e.g., `std::string` for text fields).
- A **constructor** in the `public` section will initialize these attributes.
- **Getters and setters** will:
  - **Getters**: Retrieve private data.
  - **Setters**: Update private data securely and validate changes if necessary.

---

### `AllPurchases` Data Model
**Attributes (From Project Requirements)**:
- Account Number
- Item
- Date
- Amount

**💡 My Understanding**:
- These attributes will also be **private**.
- The class will feature:
  - A **constructor** to initialize the data.
  - **Getters and setters** to access and modify data while preserving encapsulation.

---

## 💡 Why Use Getters and Setters?

1. **Encapsulation**: Protect private data by controlling access.
2. **Validation**: Ensure data integrity through setter checks.
3. **Consistency**: Centralized access patterns reduce bugs.
4. **Flexibility**: Internal implementation can change without impacting the overall program.

---

## 🛠️ How Getters and Setters Work in This Project

- **Cross-Class Access**: Getters in `AllCustomers` retrieve private account numbers for purchase matching in `AllPurchases`.
- **Data Updates**: Setters ensure that updates like changing customer details or modifying purchase amounts are controlled and validated.
- **Reusability**: The standardized approach ensures scalability and reusability of classes in different contexts.

**Example**:
- Use a getter in `AllCustomers` to fetch an account number.
- Use a setter in `AllPurchases` to update purchase amounts safely.

---

### **1. Menu-driven program that loops after each selection until the user chooses to exit**
**💡 My Understanding**:
- The program needs to continuously display a menu and process user input until the user selects the "exit" option.
- Each menu option should trigger a specific operation, such as printing data, adding a customer, or updating records.

**🛠️ How I Plan to Write This**:
- Write a `run()` function in `BookstoreManager` to handle the menu loop.
- Use a `while (true)` loop that:
  1. Displays the menu using a `displayMenu()` function.
  2. Takes user input and calls the corresponding function for the selected operation.
  3. Includes a condition to break the loop when the user chooses to exit.
- Use a `switch` or `if-else` structure to handle user input and connect it to the appropriate functionality.

---

### **2. Load all Customer account info from a file into a vector of the class**
**💡 My Understanding**:
- Customer data (e.g., name, account number, address) will be stored in a file, and the program should load this data into a `vector` for dynamic management.
- Each line in the file represents a customer and contains all the required fields.

**🛠️ How I Plan to Write This**:
- Create a function `loadFromFile(const std::string& filename)` in `BookstoreManager`.
- Use `std::ifstream` to open and read the file line by line.
- Parse each line into the required fields, create a `Customer` object, and add it to the `customers` vector using `push_back()`.
- Handle file errors (e.g., missing file or invalid data) gracefully by showing error messages or creating a new file if necessary.

---

### **3. Use a vector within the class to store purchase information**
**💡 My Understanding**:
- Purchase records need to be stored dynamically in a `vector`. Each record will have fields like account number, item, date, and amount.
- The `vector` will allow me to easily add, update, or delete purchase data.

**🛠️ How I Plan to Write This**:
- Define a `std::vector<Purchase>` as a private member in `BookstoreManager`.
- Create a function `loadPurchasesFromFile(const std::string& filename)` to read and parse the purchase data from a file.
- For each line in the file, create a `Purchase` object and add it to the `purchases` vector using `push_back()`.

---

### **4. All functions should be public member functions of your classes**
**💡 My Understanding**:
- All operations (e.g., adding, updating, deleting, printing) must be implemented as public functions. This ensures they can be accessed from the main program.
- Public functions will act as an interface between the `BookstoreManager` class and the `main` program, keeping the data manipulation logic encapsulated.

**🛠️ How I Plan to Write This**:
- Declare all required functions (e.g., `addCustomer()`, `addPurchase()`, `printAllCustomers()`) as `public` in `BookstoreManager.h`.
- Implement these functions in `BookstoreManager.cpp` to encapsulate the logic for interacting with the `customers` and `purchases` vectors.
- Ensure private members (e.g., the vectors) are accessed or modified only through these public functions.

---


// For nextDay:
// 1. Determine the logic for sorting customers in ascending order.
// 2. Generate and display a detailed customer receipt.
// 3. Figure out how to add a new customer, particularly the logic behind the account numbers.
//    For example, why does it not allow using the pattern "ACC006"?
// 4. Test all other options;
// 5. Options 7-11 seem to be working, but you need a better implementation for handling multiple purchases.
// 6. Adding a new customer and multiple customers appears to have some issues; investigate further.
// 7. Provide users with an additional option to return to the main menu after completing an action.

