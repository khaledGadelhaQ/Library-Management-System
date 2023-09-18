#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

// Represents a book in the library
class Book {
private:
    int ID;                     // Unique identifier for the book
    string name;                // Name of the book
    int quantity;               // Total number of copies of the book
    int borrowed;               // Number of copies currently borrowed
    vector<string> UserBorrowedBook;  // List of users who borrowed this book

public:
    // Default constructor to initialize member variables
    Book() : ID(0), name(""), quantity(0), borrowed(0) {}

    // Set the book's information
    void ReadInfo(string name_, int id, int quantity_) {
        name = name_;
        ID = id;
        quantity = quantity_;
        borrowed = 0;
    }

    // Attempt to borrow the book by a user
    bool BorrowBook(string user_name) {

        auto it = find(UserBorrowedBook.begin(), UserBorrowedBook.end(), user_name);
        if (it != UserBorrowedBook.end()) {
            cout << "->-> " << user_name << " already has a copy of the book <-<- \n";
            return false;
        }
        if (quantity > 0) {
            quantity--;
            borrowed++;
            UserBorrowedBook.push_back(user_name);
            return true;
        }
        cout << "->-> No copies of this book available for borrowing. <-<-" << endl;
        return false;
    }

    // Return the book to the library
    bool ReturnBook(string user_name) {
        auto it = find(UserBorrowedBook.begin(), UserBorrowedBook.end(), user_name);
        if (it != UserBorrowedBook.end()) {
            quantity++;
            borrowed--;
            UserBorrowedBook.erase(it);
            return true;
        }
        cout << user_name << " did not borrow this book." << endl;
        return false;
    }

    // Print the information about the book
    void PrintBookInfo() {
        cout << "ID: " << ID << " - Name: " << name << " - Quantity: " << quantity << " - Borrowed: " << borrowed << endl;
    }

    // Print the list of users who borrowed the book
    void PrintWhoBorrowedBook() {
        if (UserBorrowedBook.empty()) {
            cout << "->-> No users have borrowed this book. <-<-" << endl;
        } else {
            cout << "\nUsers who borrowed this book:" << endl;
            for (const auto &user : UserBorrowedBook) {
                cout << "- " << user << endl;
            }
        }
    }

    // Increase the quantity of available copies of the book
    void AddQuantity(int new_books) {
        quantity += new_books;
    }

    // Getters for book information
    const string &GetName() const {
        return name;
    }

    int GetQuantity() const {
        return quantity;
    }

    int GetID() const {
        return ID;
    }
};

// Represents a library user
class User {
private:
    int ID;                 // Unique identifier for the user
    string FirstName;       // First name of the user
    string LastName;        // Last name of the user
    string UserName;        // Username of the user
    string Email;           // Email address of the user
    vector<string> BorrowedBooks;  // List of books borrowed by the user

public:
    // Default constructor to initialize member variables
    User() : ID(0), FirstName(""), LastName(""), UserName(""), Email("") {}

    // Set the user's information
    void ReadInfo(string user_name, int user_id) {
        string first, last, email;
        cout << "\tEnter First Name: ";
        cin >> first;
        cout << "\tEnter Last Name: ";
        cin >> last;
        cout << "\tEnter Email: ";
        cin >> email;

        FirstName = first;
        LastName = last;
        Email = email;
        UserName = user_name;
        ID = user_id;
    }

    // Borrow a book
    void BorrowBook(const string &book_name) {

        auto it = find(BorrowedBooks.begin(), BorrowedBooks.end(), book_name);

        if (it != BorrowedBooks.end()) {
            // The user already borrowed this book, no action needed.
        }
        BorrowedBooks.push_back(book_name);
    }

    // Return a borrowed book
    bool ReturnBook(const string &book_name) {
        auto it = find(BorrowedBooks.begin(), BorrowedBooks.end(), book_name);
        if (it != BorrowedBooks.end()) {
            BorrowedBooks.erase(it);
            return true;
        }
        cout << "->-> The user did not borrow this book. <-<-" << endl;
        return false;
    }

    // Print the list of books borrowed by the user
    void PrintBorrowedBooks() {
        if (BorrowedBooks.empty()) {
            cout << "->-> You have not borrowed any books. <-<-" << endl;
        } else {
            cout << "\nBooks borrowed by " << UserName << ":" << endl;
            for (const auto &book : BorrowedBooks) {
                cout << "- " << book << endl;
            }
        }
    }

    // Print the user's information
    void PrintUserInfo() {
        cout << "ID: " << ID << " - First Name: " << FirstName << " - Last Name: " << LastName
             << " - Email: " << Email << " - User-Name: " << UserName << endl;
    }

    // Getters for user information
    const string &GetUserName() const {
        return UserName;
    }

    int GetID() const {
        return ID;
    }
};

// Represents a library system
class LibrarySystem {
private:
    map<string, Book> books;  // Map of book names to Book objects
    map<string, User> users;  // Map of user usernames to User objects
    int currentBookID = 1001; // Unique identifier for the next book
    int currentUserID = 1;    // Unique identifier for the next user

    // Print available options in the library system
    void PrintOptions() {
        cout << "\nLibrary System Options:" << endl;
        cout << "\t1) Add Book" << endl;
        cout << "\t2) Add User" << endl;
        cout << "\t3) Borrow a Book" << endl;
        cout << "\t4) Return a Book" << endl;
        cout << "\t5) List Books by ID" << endl;
        cout << "\t6) List Books by Name" << endl;
        cout << "\t7) Search Books by Prefix" << endl;
        cout << "\t8) Print Who Borrowed a Book" << endl;
        cout << "\t9) List Users by ID" << endl;
        cout << "\t10) List Users by Name" << endl;
        cout << "\t11) List Borrowed Books by a User" << endl;
        cout << "\t12) Print Menu Options" << endl;
        cout << "\t13) Exit" << endl;
    }

    // Get the user's choice
    int GetChoice() {
        int choice;
        cout << "\nEnter your choice (1-13): ";
        cin >> choice;
        return choice;
    }

    // Add a new book to the library
    void AddBook() {
        string book_name;
        int book_quantity;

        cout << "\tEnter Book Name: ";
        cin >> book_name;

        if (books.find(book_name) != books.end()) {
            cout << " ->-> This book already exists. <-<-\n\tEnter the quantity to add: ";
            cin >> book_quantity;
            books[book_name].AddQuantity(book_quantity);
        } else {
            cout << "\tEnter Book Quantity: ";
            cin >> book_quantity;
            Book new_book;
            new_book.ReadInfo(book_name, currentBookID++, book_quantity);
            books[book_name] = new_book;
        }
    }

    // Add a new user to the library system
    void AddUser() {
        string user_name;

        cout << "\tEnter User-Name: ";
        cin >> user_name;

        if (users.find(user_name) != users.end()) {
            cout << " ->-> This user already exists. <-<-" << endl;
        } else {
            User new_user;
            new_user.ReadInfo(user_name, currentUserID++);
            users[user_name] = new_user;
        }
    }

    // Borrow a book from the library
    void BorrowBook() {
        string user_name, book_name;
        cout << "\tEnter User-Name: ";
        cin >> user_name;
        cout << "\tEnter Book Name: ";
        cin >> book_name;

        if (users.find(user_name) != users.end() && books.find(book_name) != books.end()) {
            bool BookAvailable = books[book_name].BorrowBook(user_name);
            if (!BookAvailable) {
                return;
            }
            users[user_name].BorrowBook(book_name);
            cout << "\n >>> " << user_name << " borrowed " << book_name << "." << endl;
        } else {
            cout << "->-> Invalid user or book. Check the names and try again. <-<-" << endl;
        }
    }

    // Return a borrowed book to the library
    void ReturnBook() {
        string user_name, book_name;
        cout << "Enter User-Name: ";
        cin >> user_name;
        cout << "Enter Book Name: ";
        cin >> book_name;

        if (users.find(user_name) != users.end() && books.find(book_name) != books.end()) {
            bool UserHasBook = books[book_name].ReturnBook(user_name);
            if (!UserHasBook) {
                return;
            }
            users[user_name].ReturnBook(book_name);

            cout << user_name << " returned " << book_name << "." << endl;
        } else {
            cout << "->-> Invalid user or book. Check the names and try again. <-<-" << endl;
        }
    }

    // List books by their unique ID
    void ListBooksByID() {
        if (books.empty()) {
            cout << "->-> No books in the library right now. <-<-" << endl;
        } else {
            cout << "\nBooks sorted by ID:" << endl;

            vector<Book> sorted_books;
            for (const auto &pair : books) {
                sorted_books.push_back(pair.second);
            }
            sort(sorted_books.begin(), sorted_books.end(), [](const Book &a, const Book &b) {
                return a.GetID() < b.GetID();
            });

            for (auto &book : sorted_books) {
                book.PrintBookInfo();
            }
        }
    }

    // List books by their names
    void ListBooksByName() {
        if (books.empty()) {
            cout << "->-> No books in the library right now. <-<-" << endl;
        } else {
            cout << "\nBooks sorted by Name:" << endl;
            for (auto &book : books) {
                book.second.PrintBookInfo();
            }
        }
    }

    // Search for books by a prefix of their names
    void SearchBooksByPrefix() {
        string prefix;
        cout << "\tEnter Book Name Prefix: ";
        cin >> prefix;

        vector<string> matched_books;
        for (const auto &pair : books) {
            const string &book_name = pair.first;
            if (book_name.find(prefix) == 0) {
                matched_books.push_back(book_name);
            }
        }

        if (matched_books.empty()) {
            cout << "->-> No books with such prefix. <-<-" << endl;
        } else {
            cout << "\nBooks matching the prefix:" << endl;
            for (const string &book_name : matched_books) {
                cout << "- " << book_name << endl;
            }
        }
    }

    // Print the list of users who borrowed a specific book
    void PrintWhoBorrowedBook() {
        string book_name;
        cout << "\tEnter Book Name: ";
        cin >> book_name;

        if (books.find(book_name) != books.end()) {
            books[book_name].PrintWhoBorrowedBook();
        } else {
            cout << "->-> No book with such name. <-<- " << endl;
        }
    }

    // List users by their unique ID
    void ListUsersByID() {
        if (users.empty()) {
            cout << "->-> No users in the system. <-<-" << endl;
        } else {
            cout << "\nUsers sorted by ID:" << endl;
            vector<User> sorted_users;
            for (const auto &pair : users) {
                sorted_users.push_back(pair.second);
            }
            sort(sorted_users.begin(), sorted_users.end(), [](const User &a, const User &b) {
                return a.GetID() < b.GetID();
            });

            for (auto &user : sorted_users) {
                user.PrintUserInfo();
            }
        }
    }

    // List users by their names
    void ListUsersByName() {
        if (users.empty()) {
            cout << "->-> No users in the system. <-<-" << endl;
        } else {
            cout << "\nUsers sorted by Name:" << endl;

            for (auto &user : users) {
                user.second.PrintUserInfo();
            }
        }
    }

    // List books borrowed by a specific user
    void ListBorrowedBooksByUser() {
        string user_name;
        cout << "\n\tEnter User Name: ";
        cin >> user_name;

        if (users.find(user_name) != users.end()) {
            users[user_name].PrintBorrowedBooks();
        } else {
            cout << "->-> No user with such name. <-<-" << endl;
        }
    }

public:

    // Main loop for running the library system
    void Run() {
        PrintOptions();
        while (true) {

            int choice = GetChoice();

            switch (choice) {
                case 1:
                    AddBook();
                    break;
                case 2:
                    AddUser();
                    break;
                case 3:
                    BorrowBook();
                    break;
                case 4:
                    ReturnBook();
                    break;
                case 5:
                    ListBooksByID();
                    break;
                case 6:
                    ListBooksByName();
                    break;
                case 7:
                    SearchBooksByPrefix();
                    break;
                case 8:
                    PrintWhoBorrowedBook();
                    break;
                case 9:
                    ListUsersByID();
                    break;
                case 10:
                    ListUsersByName();
                    break;
                case 11:
                    ListBorrowedBooksByUser();
                    break;
                case 12:
                    PrintOptions();
                    break;
                case 13:
                    return;
                default:
                    cout << " \n->-> Invalid choice. Try again. <-<- \n" << endl;
            }
        }
    }

};

int main() {
    LibrarySystem system;
    system.Run();
    return 0;
}
