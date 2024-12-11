# Bookstore Management System

A menu-driven program to manage customer accounts and purchase records efficiently. This project uses dynamic data structures and encapsulation to create a robust and scalable solution.

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

