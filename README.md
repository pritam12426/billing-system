# Shop Billing System

This project is a simple billing system for a shop, developed using C++ and SQLite. It allows users to manage product storage information in a database, including functionalities for adding, editing, listing, and removing products. The system includes error handling to manage duplicate product entries.

## Features

- **Add Products**: Add new products to the database with unique product codes.
- **Edit Products**: Modify existing product details.
- **Remove Products**: Delete products from the database.
- **List Products**: Display all products stored in the database.
- **Error Handling**: Handle errors for duplicate product codes and other database-related issues.

## Prerequisites

- C++ Compiler
- SQLite library

## Installation

1. **Clone the repository:**
   ```bash
   git clone git@github.com:pritam12426/billing-system.git
   cd shop-billing-system
   mkdir build
   cd build
   make
   ./shop
   ```

**If you don't have cmake install you can use**

2. **Build the project:**
   ```bash
   g++ -o shop src/main.cpp -lsqlite3
   ```

3. **Run the executable:**
   ```bash
   ./shop
   ```

## Usage

1. **Menu Navigation:**
   - The application starts by presenting a menu for the administrator.
   - Choose the desired operation (add, edit, remove, list) by entering the corresponding number.

2. **Adding Products:**
   - Enter the product details (code, name, price, discount).
   - Ensure the product code is unique to avoid errors.

3. **Editing Products:**
   - Modify existing product details by entering the product code.

4. **Removing Products:**
   - Delete a product by entering its code.

5. **Listing Products:**
   - Display all products stored in the database.

## Error Handling

- If a product with a duplicate code is added, an error message is displayed.
- SQL errors during database operations are handled and displayed to the user.

## Project Structure

```
.
├── include
│   ├── sql_query_1.txt
│   └── sql_query_2.txt
├── src
│   └── main.cpp
└── README.md
```

- **main.cpp**: The main C++ source file containing the implementation.
- **include/sql_query_1.txt**: SQL queries for creating tables.
- **include/sql_query_2.txt**: Additional SQL queries.
- **README.md**: This README file.
