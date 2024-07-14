// The Library System
//The main user for the system is an admin
//I am so lonely broken angle, I am so lonely listen to my heart
//I try to live in black and white, but I am so blue

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct book{
    int id, quantity;
    string bookName;
    vector<string> userWhoBorrowed;
    int borrowedCounter=0;
};

struct user{
    string name, nationalID;
    vector<book> borrowedBooks;
};

vector<book> books;
vector<user>users;

void addBook(){
    book initialBook;
    cout<<"Enter book information: Name, ID, and Quantity: ";
    cin>>initialBook.bookName>>initialBook.id>>initialBook.quantity;
    books.push_back(initialBook);
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void searchForBookByPrefix(){
    string prefix;
    cout << "Enter  book name prefix: ";
    cin>>prefix;
    vector<string> result;
    for (int i = 0; i < books.size(); ++i) {
        if (books[i].bookName.size() >= prefix.size() &&
            books[i].bookName.substr(0, prefix.size()) == prefix) {
            result.push_back(books[i].bookName);
        }
    }
    // Output the result
    if (result.empty()) {
        cout << "No books with such prefix." << endl;
    } else {
        for (const auto& name : result) {
            cout << name << endl;
        }
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";
}
void pintWhoBorrowedBookByName(){
    string bookName;
    bool flagCheckIfThereIsBookFound = false;
    cout<<"Enter the book name: ";
    cin>>bookName;
    for (int i = 0; i < books.size(); ++i) {
        if (books[i].bookName == bookName) {
            flagCheckIfThereIsBookFound = true;
            if (books[i].borrowedCounter == 0) {
                cout << "Not Borrowed yet! \n";
            } else {
                for (int j = 0; j < books[i].userWhoBorrowed.size(); ++j) {
                    cout << books[i].userWhoBorrowed[j] << "\n";
                }

            }
        }
    }
    if (!flagCheckIfThereIsBookFound)
        cout<<"Invalid Book Name ! \n";

    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void printLibraryById(){
    sort(books.begin(), books.end(), [](const book& a, const book& b) {
        return a.id < b.id;
    });
    for (auto & book : books) {
        cout<<"id = "<<book.id<<"  Name = "<<book.bookName<<"  Total Quantity = " << book.quantity<<"  Total Borrowed = "<<book.borrowedCounter<<"\n";
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void printLibraryByName(){
    sort(books.begin(), books.end(), [](const book& a, const book& b) {
        return a.bookName < b.bookName;
    });
    for (auto & book : books) {
        cout<<"User "<<"id = "<<book.id<<"  Name = "<<book.bookName<<"  Total Quantity = " << book.quantity<<"  Total Borrowed = "<<book.borrowedCounter<<"\n";
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void addUser(){
    cout<<"\n"<<"Enter user name and national id: ";
    user initialUser;
    cin>>initialUser.name>>initialUser.nationalID;
    users.push_back(initialUser);
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void userBorrowBook(){
    string userName, bookName;
    book book;
    bool checkAvailableBooks = false;
    cout<<"Enter user name and book name: ";
    cin>>userName>>bookName;
    for (auto & i : books) {
        if (i.bookName==bookName){
            if (i.borrowedCounter < i.quantity){
                checkAvailableBooks=true;
                i.borrowedCounter++;
                i.userWhoBorrowed.push_back(userName);
                book = i;
            }else{
                cout<<"all versions are borrowed come back another time!"<<"\n";
            }
        }
    }
    if (checkAvailableBooks){
        for (auto & user : users) {
            if (user.name==userName){
                user.borrowedBooks.push_back(book);
            }
        }
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";

}

void userReturnBook(){
    string userName, bookName;
    book book;
    cout<<"Enter user name and book name: ";
    cin>>userName>>bookName;
    for (auto & i : books) {
        if (i.bookName==bookName){
            i.borrowedCounter--;
            for (int j = 0; j < i.userWhoBorrowed.size(); ++j) {
                if (userName==i.userWhoBorrowed[j])
                    i.userWhoBorrowed.erase(i.userWhoBorrowed.begin()+j);
            }
            book = i;
        }
    }
    for (auto & user : users) {
        if (user.name==userName){
            for (int i = 0; i < user.borrowedBooks.size(); ++i) {
                if (bookName==user.borrowedBooks[i].bookName)
                    user.borrowedBooks.erase(user.borrowedBooks.begin()+i);
            }
        }
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void printUsers(){
    for (int i = 0; i < users.size(); ++i) {
        cout<<"User: "<<"name: "<<users[i].name<<", Id: "<<users[i].nationalID<<", borrowed books ids: ";
        for (int j = 0; j < users[i].borrowedBooks.size(); ++j) {
            cout<<users[i].borrowedBooks[j].id<<", ";
        }
        cout<<"\n";
    }
    cout<<"\n"<<"-------------------------------------"<<"\n";
}

void menu(){
    cout<<"library menu: \n";
    cout<<"1) add Book \n";
    cout<<"2) search For Book By Prefix \n";
    cout<<"3) pint Who Borrowed Book By Name \n";
    cout<<"4) print Library By Id \n";
    cout<<"5) print Library By Name \n";
    cout<<"6) add User \n";
    cout<<"7) user Borrow Book \n";
    cout<<"8) user Return Book \n";
    cout<<"9) print Users \n";
    cout<<"Exit \n";
}

void librarySystem(){
    menu();
    int choice = 0;
    while (choice != 10){
        bool validInput = false;
        while (!validInput) {
            cout << "Enter a choice between 1 and 10: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits < streamsize> ::max(), '\n');
                cout << "Invalid input. Please enter a choice." << std::endl;
            } else if (choice >= 1 && choice <= 10) {
                validInput = true;
            } else {
                std::cout << "Number out of range. Please enter a choice between 1 and 10." << std::endl;
            }
        }
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchForBookByPrefix();
                break;
            case 3:
                pintWhoBorrowedBookByName();
                break;
            case 4:
                printLibraryById();
                break;
            case 5:
                printLibraryByName();
                break;
            case 6:
                addUser();
                break;
            case 7:
                userBorrowBook();
                break;
            case 8:
                userReturnBook();
                break;
            case 9:
                printUsers();
                break;

        }
        menu();

    }
}
int main() {
    librarySystem();
    return 0;
}
