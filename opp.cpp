#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int year;

public:
    // Constructor
    Book(string t, string a, int y) {
        title = t;
        author = a;
        year = y;
    }

    // Method to display book details
    void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
    }

    // Get title for searching
    string getTitle() {
        return title;
    }
};

class Library {
private:
    vector<Book> books;

public:
    // Method to add a book
    void addBook(string title, string author, int year) {
        books.push_back(Book(title, author, year));
        cout << "Book added successfully!" << endl;
    }

    // Method to display all books
    void displayBooks() {
        cout << "Book List:" << endl;
        cout << "Title\t\t\tAuthor\t\tYear" << endl;
        for (Book &book : books) {
            book.display();
            cout << "-------------------" << endl;
        }
    }

    // Method to search for a book by title
    void searchBook(string searchTitle) {
        for (Book &book : books) {
            if (book.getTitle() == searchTitle) {
                cout << "Book found!" << endl;
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};

int main() {
    Library library;
    int choice;
    string title, author;
    int year;

    while (true) {
        cout << "\nMenu" << endl;
        cout << "1 - Add Book" << endl;
        cout << "2 - Display Books" << endl;
        cout << "3 - Search Book" << endl;
        cout << "4 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter year: ";
            cin >> year;
            cin.ignore();
            library.addBook(title, author, year);
            break;
        case 2:
            library.displayBooks();
            break;
        case 3:
            cout << "Enter a book to search: ";
            getline(cin, title);
            library.searchBook(title);
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
