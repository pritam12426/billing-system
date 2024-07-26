#include <sqlite3.h>

#include <format>
#include <iostream>
#include <string>


class Shopping {
 private:
  char *db_error_message = nullptr;
  sqlite3 *db { nullptr };

  int product_code            = 0;
  short int choice            = 0;
  float price                 = 0;
  int db_return_code          = 0;
  float discount              = 0;
  size_t max_product_name_len = 0;
  std::string product_name    = "";
  char *sql_query             = nullptr;
  sqlite3_stmt *stmt          = nullptr;

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
      add();
    }
    create_database();
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


/*Creat database is done*/
void Shopping::create_database(void) {
  sql_query = {
#include "../include/sql_query_1.txt"
  };

  db_return_code = sqlite3_exec(db, sql_query, NULL, 0, &db_error_message);
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

  db_return_code = sqlite3_exec(db, sql_query, NULL, 0, &db_error_message);
  if (db_return_code != SQLITE_OK) {
    std::cerr << "SQL error: while creat table 'Key value' ( "
              << db_error_message << " )\n";
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
    exit(1);
  }
}


/*menu database is done*/
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

/* administrator is done */
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


/* add is done */
void Shopping::add(void) {
user:
  std::clog << "Add new product\n";
  std::clog << "\tProduct code of the product ";
  std::cin >> product_code;
  std::clog << "\tName of the product ";
  std::cin >> product_name;
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
  list();
  std::clog << "Enter the product code code: ";
  std::cin >> choice;
  std::string sql_query =
      std::format("DELETE FROM \"Shop\" WHERE \"Shop Product Code\" = {};", choice);
  std::cout << sql_query << '\n';
  // exit(0);
  db_return_code =
      sqlite3_exec(db, sql_query.c_str(), callback, 0, &db_error_message);
  if (db_return_code != SQLITE_OK) {
    std::cerr << "SQL error: while deleting from table 'Shop' in data base ( "
              << db_error_message << " )\n";
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
    exit(1);
  }
}


void Shopping::list(void) {
  sql_query      = "SELECT * from 'Shop'";
  db_return_code = sqlite3_exec(db, sql_query, callback, 0, &db_error_message);

  if (db_return_code != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", db_error_message);
    sqlite3_free(db_error_message);
    db_error_message = nullptr;
  }
}


void Shopping::receipt() {
  ;
}


int main(void) {
  Shopping shop;
  shop.administrator();
  return 0;
}
