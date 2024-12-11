# Project Overview - Code Journey Documentation

This project is structured to simulate a bookstore management system. Below is the basic structure of the project, including all required files and their purposes.

## Project Description

A 2-class menu-driven program designed to track and manage customer account information and purchases for a business. 

- On launch, the program introduces itself and the business.
- Loads existing customer account information from a file of any size into a vector of a class called `AllCustomers`.
- Loads purchase information from a file of any size into a vector of a class called `AllPurchases`.

---

## My Understanding

- **Classes Needed**: 
  - `AllCustomers`
  - `AllPurchases`

- **Why Use `Vector`**:
  - It is a dynamic array that can grow using `push_back()` or shrink data as needed.
  - Provides utility functions like `size()` to get the number of elements.
  - Reduces the risk of memory leaks and segmentation faults with automatic memory management.

## Data Models

### AllCustomers Data Model
The `AllCustomers` class should include (but is not limited to) the following attributes:
- **First Name**
- **Last Name**
- **Account #**
- **Street Address**
- **City**
- **State**
- **Zip Code**
- **Phone Number**

**My Understanding**:
- These attributes are private members of the `AllCustomers` class and will be declared inside the `private` section.
- Each attribute can be declared as a `std::string`.
- A constructor will be created in the `public` section to initialize these attributes using parameters.
- Getters and setters will be written to access and modify private data safely:
  - **Getters**: Retrieve the value of private members.
  - **Setters**: Update the value of private members.

---

### AllPurchases Data Model
The `AllPurchases` class should include (but is not limited to) the following attributes:
- **Account Number**
- **Item**
- **Date**
- **Amount**

**My Understanding**:
- These attributes are private members of the `AllPurchases` class and will be declared inside the `private` section.
- A constructor will be created in the `public` section to initialize these attributes using parameters.
- Getters and setters will be written to ensure secure access and modification of private data.

## Extra basic knowledge of using Getters and Setters Across Classes or Files

### Why Getters and Setters Are Useful:
1. **Encapsulation**: They protect private data by controlling how it is accessed and modified.
2. **Validation**: Setters can include checks to ensure data integrity when updating values.
3. **Consistency**: Ensure all access and updates follow a standardized process, reducing bugs.
4. **Flexibility**: If internal implementation changes, only the getter and setter need updates, not the entire codebase.

### How They Help in the Full Project:
- **Cross-Class Access**: Getters allow us to retrieve private data from one class while maintaining its encapsulation.
- **Data Updates**: Setters enable secure and controlled updates to private data from other classes or files.
- **Reusability**: By using getters and setters, we can easily reuse classes in different parts of the project without directly exposing internal details.

For example:
- In the `AllCustomers` class, we can use getters to retrieve a customer’s account number in another class to match purchase records from the `AllPurchases` class.
- Setters can be used to update customer details or purchase amounts when required, ensuring data is always consistent and valid.
