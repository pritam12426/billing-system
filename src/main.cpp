#include <sqlite3.h>

#include <format>
#include <iostream>
#include <string>

static short int choice;

class Shopping {
 private:
  char *db_error_message = nullptr;
  sqlite3 *db { nullptr };

  int product_code { 0 };
  float price { 0 };
  int db_return_code { 0 };
  float discount { 0 };
  size_t max_product_name_len {};
  std::string product_name {};
  char *sql_query = nullptr;

 public:
  void menu(void);
  void administrator(void);
  void buyer(void);
  void add(void);
  void edit(void);
  void remove(void);
  void list(void);
  void create_database(void);
  void receipt(void);
  static int callback(void *NotUsed, int argc, char **argv, char **azColName);

 public:
  Shopping() {
    db_return_code = sqlite3_open("data_base.db", &db);
    if (db_return_code) {
      std::cerr << "Creating new data base file: " << sqlite3_errmsg(db)
                << '\n';
      create_database();
      add();
    }
  }
  ~Shopping() {
    sqlite3_close(db);
    ;
  }
};

int Shopping::callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    std::printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  std::printf("\n");
  return 0;
}


void Shopping::create_database(void) {
  sql_query = {
#include "../include/sql_query_1.txt"
  };

  db_return_code = sqlite3_exec(db, sql_query, callback, 0, &db_error_message);
  if (db_return_code != SQLITE_OK) {
    std::cerr << "SQL error: while creating table 'Sh>>>sop' in data base ( "
              << db_error_message << " )\n";
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
    exit(1);
  }

  sql_query = {
#include "../include/sql_query_2.txt"
  };

  db_return_code = sqlite3_exec(db, sql_query, callback, 0, &db_error_message);
  if (db_return_code != SQLITE_OK) {
    std::cerr << "SQL error: while creat table 'Key value' ( "
              << db_error_message << " )\n";
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
    exit(1);
  }
}


void Shopping::menu(void) {
  std::string email {};
  int password { 0 };

  const char *mess1 = {
#include "../include/mess1.txt"
  };
  std::clog << mess1;

user:
  std::clog << "Please select!: ";
  std::cin >> choice;

  switch (choice) {
    case 1: {
      std::clog << "Please select!\n\tEnter you email: ";
      std::cin >> email;
      std::clog << "\tEnter you password: ";
      std::cin >> password;
      if (email == "some.com" && password == 1234) {
        administrator();
      } else {
        std::clog << "Invalid email/password\n";
      }
      break;
    }

    case 2: {
      buyer();
      break;
    }

    case 3: {
      exit(0);
    }

    default: {
      std::clog << "Please select from the given options!\n";
    }
  }
  goto user;
}


void Shopping::administrator(void) {
  const char *mess2 = {
#include "../include/mess2.txt"
  };
  std::clog << mess2;

user:
  std::clog << "Please select!: ";
  std::cin >> choice;


  switch (choice) {
    case 1: {
      add();
      break;
    }

    case 2: {
      edit();
      break;
    }

    case 3: {
      remove();
      break;
    }

    case 4: {
      menu();
      break;
    }

    default: {
      std::clog << "Invalid choice!";
    }
  }
  goto user;
}


void Shopping::buyer(void) {
  ;
  ;
}


void Shopping::add(void) {
user:
  std::clog << "Add new product\n";
  std::clog << "\tProduct code of the product ";
  std::cin >> product_code;
  std::clog << "\tName of the product ";
  std::getline(std::cin, product_name);
  std::clog << "\tPrice of the product: ";
  std::cin >> price;
  std::clog << "\tDiscount on product: ";
  std::cin >> discount;

  std::string sql_query(
      "INSERT INTO 'Shop' ('Shop Product Code', 'Shop Product Name', 'Shop "
      "Product Price', 'Shop Product Discount') ");
  sql_query += std::format("VALUES ({}, '{}', {}, {}); ", product_code,
                           product_name, price, discount);

  db_return_code =
      sqlite3_exec(db, sql_query.c_str(), callback, 0, &db_error_message);
  if (db_return_code == 19) {
    std::cerr << "\nProduct code should be unique the ( " << product_code
              << " ) already exist\n\a";
    goto user;
  }

  if (db_return_code != SQLITE_OK) {
    std::cerr << "SQL error: while creating table 'Shop' in data base ( "
              << db_error_message << " )\n";
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
    exit(1);
  }

  if (max_product_name_len > product_name.length()) {
    max_product_name_len = product_name.length();
  }
}


void Shopping::edit(void) {
  ;
}

void Shopping::remove() {
  ;
  ;
}

void Shopping::list(void) {
  std::cout
      << "\n\n|-----------------------------------------------------------|\n";
  std::cout << "Product Code \t\t Name \t\t Price \n";
  // TODO: list whole data base with while loop
}


void Shopping::receipt() {
  ;
}


int main(void) {
  Shopping shop;
  shop.menu();
  return 0;
}
