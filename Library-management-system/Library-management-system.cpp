#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class Book {
public:
    Book(int id, const std::string& name, const std::string& author, int year) :
        bookID(id), bookName(name), author(author), yearPublished(year) {}

    int getBookID() const { return bookID; }
    std::string getBookName() const { return bookName; }
    std::string getAuthor() const { return author; }
    int getYearPublished() const { return yearPublished; }

    void setBookName(const std::string& name) { bookName = name; }
    void setAuthor(const std::string& authorName) { author = authorName; }
    void setYearPublished(int year) { yearPublished = year; }

    void displayBookInfo() const {
        std::cout << "Book ID: " << bookID << std::endl;
        std::cout << "Book Name: " << bookName << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Year Published: " << yearPublished << std::endl;
    }

private:
    int bookID;
    std::string bookName;
    std::string author;
    int yearPublished;
};

class Library {
public:
    Library(const std::string& filename) : fileName(filename) {
        loadBooksFromFile();
    }
    ~Library() {
        saveBooksToFile();
    }

    void addBook() {
        int id, year;
        std::string name, author;

        std::cout << "Enter Book ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter Book Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Author: ";
        std::getline(std::cin, author);
        std::cout << "Enter Year Published: ";
        std::cin >> year;

        books.push_back(Book(id, name, author, year));
        std::cout << "Book added successfully!\n";
    }

    void displayAllBooks() {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }
        for (const auto& book : books) {
            book.displayBookInfo();
            std::cout << std::endl;
        }
    }

    void searchBook() {
        std::cout << "Enter book name or author to search: ";
        std::string term;
        std::cin.ignore();
        std::getline(std::cin, term);

        auto indices = searchBooks(term);
        if (indices.empty()) {
            std::cout << "No books found.\n";
            return;
        }
        for (int index : indices) {
            books[index].displayBookInfo();
            std::cout << std::endl;
        }
    }

    void deleteBook() {
        std::cout << "Enter book ID to delete: ";
        int id;
        std::cin >> id;
        int index = searchBook(id);
        if (index == -1) {
            std::cout << "Book not found!\n";
            return;
        }
        books.erase(books.begin() + index);
        std::cout << "Book deleted successfully!\n";
    }

private:
    std::vector<Book> books;
    std::string fileName;

    void saveBooksToFile() {
        std::ofstream file(fileName);
        if (!file) {
            std::cerr << "Failed to open file for writing.\n";
            return;
        }
        for (const auto& book : books) {
            file << book.getBookID() << ',' << book.getBookName() << ','
                 << book.getAuthor() << ',' << book.getYearPublished() << '\n';
        }
        file.close();
    }

    void loadBooksFromFile() {
        std::ifstream file(fileName);
        if (!file) {
            std::cerr << "Failed to open file for reading.\n";
            return;
        }
        std::string line, name, author;
        int id, year;
        while (getline(file, line)) {
            std::istringstream iss(line);
            getline(iss, name, ',');
            getline(iss, author, ',');
            iss >> id >> year;
            books.emplace_back(id, name, author, year);
        }
        file.close();
    }

    int searchBook(int bookID) {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].getBookID() == bookID) {
                return i;
            }
        }
        return -1;
    }

    std::vector<int> searchBooks(const std::string& term) {
        std::vector<int> indices;
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].getBookName().find(term) != std::string::npos ||
                books[i].getAuthor().find(term) != std::string::npos) {
                indices.push_back(i);
            }
        }
        return indices;
    }
};

int main() {
    Library myLibrary("library.txt");
    int choice;

    do {
        std::cout << "\n1. Add Book\n";
        std::cout << "2. Display All Books\n";
        std::cout << "3. Search for a Book\n";
        std::cout << "4. Delete a Book\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                myLibrary.addBook();
                break;
            case 2:
                myLibrary.displayAllBooks();
                break;
            case 3:
                myLibrary.searchBook();
                break;
            case 4:
                myLibrary.deleteBook();
                break;
            case 5:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
