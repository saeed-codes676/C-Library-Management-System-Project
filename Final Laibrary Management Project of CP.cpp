
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

const int MAX_BOOKS = 100;

// Structure for storing book information
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    string studentName;
};

// Function Prototypes
bool readInteger(int &value);

void addBook(Book library[], int &count);
void displayAllBooks(const Book library[], int count);
void searchBook(const Book library[], int count);
void updateBook(Book library[], int count);
void issueBook(Book library[], int count);
void returnBook(Book library[], int count);
void deleteBook(Book library[], int &count);

void saveBooks(const Book library[], int count);
void loadBooks(Book library[], int &count);


// Main Function
int main() {

    Book library[MAX_BOOKS];
    int bookCount = 0;

    // Load saved records when program starts
    loadBooks(library, bookCount);

    int choice = 0;

    do {
        cout << "\n=========================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM         \n";
        cout << "=========================================\n";
        cout << " 1. Add New Book\n";
        cout << " 2. Display All Books\n";
        cout << " 3. Search Book by ID\n";
        cout << " 4. Update Book\n";
        cout << " 5. Issue Book\n";
        cout << " 6. Return Book\n";
        cout << " 7. Delete Book\n";
        cout << " 8. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice (1-8): ";

        if (!readInteger(choice)) {
            cout << "\n[Error] Please enter a valid number!\n";
            choice = 0;
        }

        switch (choice) {

            case 1:
                addBook(library, bookCount);
                saveBooks(library, bookCount);
                break;

            case 2:
                displayAllBooks(library, bookCount);
                break;

            case 3:
                searchBook(library, bookCount);
                break;

            case 4:
                updateBook(library, bookCount);
                saveBooks(library, bookCount);
                break;

            case 5:
                issueBook(library, bookCount);
                saveBooks(library, bookCount);
                break;

            case 6:
                returnBook(library, bookCount);
                saveBooks(library, bookCount);
                break;

            case 7:
                deleteBook(library, bookCount);
                saveBooks(library, bookCount);
                break;

            case 8:
                saveBooks(library, bookCount);
                cout << "\nThank you for using Library Management System!\n";
                break;

            default:
                cout << "\n[Error] Invalid choice! Enter 1 to 8.\n";
        }

    } while (choice != 8);

    return 0;
}


// Function to read an integer safely
bool readInteger(int &value) {

    if (cin >> value) {
        return true;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return false;
}


// Function to add a new book
void addBook(Book library[], int &count) {

    if (count >= MAX_BOOKS) {
        cout << "\n[Error] Library is full!\n";
        return;
    }

    cout << "\n--- Add New Book ---\n";

    cout << "Enter Book ID: ";

    if (!readInteger(library[count].id)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    // Check for duplicate ID
    for (int i = 0; i < count; i++) {

        if (library[i].id == library[count].id) {
            cout << "\n[Error] This Book ID already exists!\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Book Title: ";
    getline(cin, library[count].title);

    cout << "Enter Author Name: ";
    getline(cin, library[count].author);

    library[count].isIssued = false;
    library[count].studentName = "N/A";

    count++;

    cout << "\n[Success] Book added successfully!\n";
}


// Function to display all books
void displayAllBooks(const Book library[], int count) {

    if (count == 0) {
        cout << "\n[Info] No books in the library!\n";
        return;
    }

    cout << "\n";
    cout << "                                  CURRENT BOOK LIST                                     \n";
    cout << "========================================================================================\n";

    cout << left
         << setw(8) << "ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(12) << "Status"
         << setw(20) << "Issued To"
         << "\n";

    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {

        string statusStr = library[i].isIssued ? "Issued" : "Available";

        cout << left
             << setw(8) << library[i].id
             << setw(30) << library[i].title
             << setw(25) << library[i].author
             << setw(12) << statusStr
             << setw(20) << library[i].studentName
             << "\n";
    }

    cout << "========================================================================================\n";
    cout << "Total Books: " << count << "\n";
}


// Function to search for a book
void searchBook(const Book library[], int count) {

    if (count == 0) {
        cout << "\n[Info] Library is empty!\n";
        return;
    }

    int targetId;

    cout << "\n--- Search Book by ID ---\n";
    cout << "Enter Book ID: ";

    if (!readInteger(targetId)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (library[i].id == targetId) {

            found = true;

            cout << "\n=========================================\n";
            cout << "              BOOK FOUND                 \n";
            cout << "=========================================\n";

            cout << "Book ID   : " << library[i].id << "\n";
            cout << "Title     : " << library[i].title << "\n";
            cout << "Author    : " << library[i].author << "\n";

            cout << "Status    : "
                 << (library[i].isIssued ? "Issued" : "Available") << "\n";

            if (library[i].isIssued) {
                cout << "Issued To : " << library[i].studentName << "\n";
            }

            cout << "=========================================\n";

            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found\n";
    }
}


// Function to update a book
void updateBook(Book library[], int count) {

    if (count == 0) {
        cout << "\n[Info] Library is empty!\n";
        return;
    }

    int targetId;

    cout << "\n--- Update Book ---\n";
    cout << "Enter Book ID: ";

    if (!readInteger(targetId)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (library[i].id == targetId) {

            found = true;

            cout << "\nCurrent Title : " << library[i].title << "\n";
            cout << "Current Author: " << library[i].author << "\n";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEnter New Title: ";
            getline(cin, library[i].title);

            cout << "Enter New Author: ";
            getline(cin, library[i].author);

            cout << "\n[Success] Book updated successfully!\n";

            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found\n";
    }
}


// Function to issue a book
void issueBook(Book library[], int count) {

    if (count == 0) {
        cout << "\n[Info] Library is empty!\n";
        return;
    }

    int targetId;

    cout << "\n--- Issue Book ---\n";
    cout << "Enter Book ID: ";

    if (!readInteger(targetId)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (library[i].id == targetId) {

            found = true;

            if (library[i].isIssued) {
                cout << "\nBook is already issued!\n";
            }

            else {

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Student Name: ";
                getline(cin, library[i].studentName);

                library[i].isIssued = true;

                cout << "\n[Success] Book issued successfully!\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found\n";
    }
}


// Function to return a book
void returnBook(Book library[], int count) {

    if (count == 0) {
        cout << "\n[Info] Library is empty!\n";
        return;
    }

    int targetId;

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ID: ";

    if (!readInteger(targetId)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (library[i].id == targetId) {

            found = true;

            if (!library[i].isIssued) {
                cout << "\nThis book is not currently issued!\n";
            }

            else {

                string previousStudent = library[i].studentName;

                library[i].isIssued = false;
                library[i].studentName = "N/A";

                cout << "\n[Success] Book returned successfully!\n";
                cout << "Previously issued to: " << previousStudent << "\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found\n";
    }
}


// Function to delete a book
void deleteBook(Book library[], int &count) {

    if (count == 0) {
        cout << "\n[Info] Library is empty!\n";
        return;
    }

    int targetId;

    cout << "\n--- Delete Book ---\n";
    cout << "Enter Book ID: ";

    if (!readInteger(targetId)) {
        cout << "\n[Error] Invalid Book ID!\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (library[i].id == targetId) {

            found = true;

            // Shift remaining books to the left
            for (int j = i; j < count - 1; j++) {
                library[j] = library[j + 1];
            }

            count--;

            cout << "\n[Success] Book deleted successfully!\n";

            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found\n";
    }
}


// Function to load books from file
void loadBooks(Book library[], int &count) {

    ifstream inFile("books.txt");

    if (!inFile) {
        count = 0;
        return;
    }

    int total = 0;

    if (!(inFile >> total) || total < 0) {
        count = 0;
        inFile.close();
        return;
    }

    inFile.ignore(numeric_limits<streamsize>::max(), '\n');

    if (total > MAX_BOOKS) {
        total = MAX_BOOKS;
    }

    count = 0;

    for (int i = 0; i < total; i++) {

        if (!(inFile >> library[i].id)) {
            break;
        }

        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(inFile, library[i].title)) {
            break;
        }

        if (!getline(inFile, library[i].author)) {
            break;
        }

        if (!(inFile >> library[i].isIssued)) {
            break;
        }

        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(inFile, library[i].studentName)) {
            break;
        }

        count++;
    }

    inFile.close();

    if (count > 0) {
        cout << "\n[File Handling] Successfully loaded "
             << count << " book record(s) from books.txt!\n";
    }
}


// Function to save books into file
void saveBooks(const Book library[], int count) {

    ofstream outFile("books.txt");

    if (!outFile) {
        cout << "\n[Error] Unable to open books.txt for writing!\n";
        return;
    }

    outFile << count << "\n";

    for (int i = 0; i < count; i++) {

        outFile << library[i].id << "\n";
        outFile << library[i].title << "\n";
        outFile << library[i].author << "\n";
        outFile << library[i].isIssued << "\n";
        outFile << library[i].studentName << "\n";
    }

    outFile.close();

    cout << "\n[File Handling] All "
         << count << " book record(s) successfully saved!\n";
}
