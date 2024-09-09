# Supermarket Management System

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Future Improvements](#future-improvements)

---

## Introduction

The **Supermarket Management System** is a console-based application designed to manage products in a supermarket. It allows users to add products, delete products, update product details, sort products by various parameters (price, quantity, and ID), display products in different categories, and manage a cart with product purchases.

---

## Features

- **Product Management**: 
    - Add new products to the inventory.
    - Delete products based on their ID.
    - Update product details such as name, price, category, and quantity.
    - Sort products based on ID, price, or quantity.
    - View products by category.

- **Cart Management**:
    - Add products to the cart with specified quantities.
    - View all items in the cart with a total price calculation.

---

## Technologies Used

- **Programming Language**: C
- **File Handling**: User credentials are stored in a text file (`credentials.txt`).
- **Data Structures**: Linked lists are used to manage product inventory and shopping cart.
  
---

## Setup Instructions

### 1. Clone the Repository

Clone the repository to your local machine using the following command:

```bash
git clone https://github.com/your-repository/supermarket-management-system.git
```

### 2. Compilation

Make sure you have a C compiler installed (e.g., GCC). You can compile the program using:

```bash
gcc supermarket.c -o supermarket
```

### 3. Running the Program

Once compiled, you can run the program with the following command:

```bash
./supermarket
```

### 4. Credentials File Setup

Create a file named `credentials.txt` in the same directory as the executable and store the initial credentials in the following format:

```
admin
password123
admin@example.com
```

---

## Usage

- **Main Menu Options**:
    1. **Add Products**: Enter product details such as ID, name, category, price, and quantity.
    2. **Delete Products**: Remove a product by providing its ID.
    3. **Update Products**: Update any of the product details (name, category, price, or quantity).
    4. **Display Products**: View all products in the inventory or view by category.
    5. **Sort Products**: Sort products by ID, price, or quantity.
    6. **Manage Cart**: Add items to the cart, view the cart, and calculate the total.

---

## File Structure

```bash
supermarket-management-system/
│
├── supermarket.c           # Main C program file
├── credentials.txt         # File storing user credentials
└── README.md               # This README file
```

---

## Future Improvements

- Implement a **GUI** for a more user-friendly experience.
- **Database Integration** to replace file-based storage and allow for a more scalable solution.
- Enhance the **cart system** by allowing users to remove items from the cart or adjust quantities.
- **Reporting System**: Generate detailed reports on sales, stock levels, etc.

---

Feel free to contribute to this project by suggesting new features or improvements!
