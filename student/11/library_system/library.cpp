#include "library.hh"
#include <iostream>

// Let's use the date when the project was published as the first date.
Library::Library():
    today_(new Date(13, 11, 2019)),
    books_({}),
    authors_({}),
    accounts_({}),
    loans_({})
{

}

Library::~Library()
{
    // Free all memory reserved with the keyword new.
    delete today_; today_ = nullptr;
    for ( std::pair<std::string, Book*> book : books_ ){
        delete book.second;
        book.second = nullptr;
    }
    for ( std::pair<std::string, Person*> author : authors_ ){
        delete author.second;
        author.second = nullptr;
    }
    for ( std::pair<std::string, Person*> account : accounts_ ){
        delete account.second;
        account.second = nullptr;
    }
    for ( std::pair<std::string, Loan*> loan : loans_ ){
        delete loan.second;
        loan.second = nullptr;
    }
}

void Library::all_books()
{
    for ( std::pair<std::string, Book*> book : books_ ){
        std::cout << book.first << std::endl;
    }
}

void Library::all_books_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Book*> book : books_ ){
        book.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

void Library::all_borrowers()
{
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        std::cout << borrower.first << std::endl;
    }
}

void Library::all_borrowers_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        borrower.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

bool Library::add_book(const std::string &title,
                       const std::vector<std::string> authors,
                       const std::string &description,
                       const std::set<std::string> genres)
{
    if ( authors.empty() ){
        std::cout << MISSING_AUTHOR_ERROR << std::endl;
        return false;
    }
    std::vector<Person*> author_ptrs;
    for ( std::string author : authors ){
        Person* n_person;
        if ( authors_.find(author) == authors_.end() ){
            n_person = new Person(author, "", "");
            authors_.insert({author, n_person});
        } else {
            n_person = authors_.at(author);
        }
        author_ptrs.push_back(n_person);
    }
    Book* n_book = new Book(title, author_ptrs, description, genres);
    books_.insert({title, n_book});
    return true;
}

void Library::add_borrower(const std::string &name, const std::string &email,
                           const std::string &address)
{
    if ( accounts_.find(name) != accounts_.end()){
        std::cout << DUPLICATE_PERSON_ERROR << std::endl;
        return;
    }

    Person* n_person = new Person(name, email, address);
    accounts_.insert({name, n_person});
}

void Library::set_date(int day, int month, int year)
{
    delete today_;
    today_ = new Date(day, month, year);
    today_->show();
}

void Library::advance_date(int days)
{
    today_->advance_by(days);
    today_->show();
}

// Checks if there are no loans and prints the info if at least one exists.
void Library::loaned_books()
{
    if ( loans_.size() == 0 ) {
        return;
    }
    std::cout << LOAN_INFO << std::endl;
    for ( std::pair<std::string, Loan*> loan : loans_ ) {
        std::cout << loan.second->print_info(today_, true) << std::endl;
    }
}

// Checks if the given person exists in the system and prints his/her loans.
void Library::loans_by(const std::string &borrower)
{
    if ( accounts_.find(borrower) == accounts_.end() ) {
        std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
        return;
    }
    for ( std::pair<std::string, Loan*> loan : loans_ ) {
        if ( loan.second->get_loaner()->get_name() == borrower ) {
            std::cout << loan.second->print_info(today_, false) << std::endl;
        }
    }
}

// Checks if given parameter(s) are valid and creates and
// adds a new loan to the map structure.
void Library::loan(const std::string &book_title, const std::string &borrower_id)
{
    if ( loans_.find(book_title) != loans_.end() ) {
        std::cout << ALREADY_LOANED_ERROR << std::endl;
        return;
    }
    if ( books_.find(book_title) == books_.end() ) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }
    if ( accounts_.find(borrower_id) == accounts_.end() ) {
        std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
        return;
    }
    Date* loan_due = new Date(today_->getDay(),
                              today_->getMonth(),
                              today_->getYear());
    loan_due->advance_by_loan_length();
    Loan* new_loan = new Loan(books_.at(book_title),
                              accounts_.at(borrower_id),
                              loan_due);
    loans_.insert({book_title, new_loan});
}

// Checks if given parameter(s) are valid and tries to renew the loan.
// Then continues to print info accordingly.
void Library::renew_loan(const std::string &book_title)
{
    if ( books_.find(book_title) == books_.end() ) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }
    if ( loans_.find(book_title) == loans_.end() ) {
        std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
        return;
    }
    if ( ! loans_.at(book_title)->renew_loan() ) {
        std::cout << OUT_OF_RENEWALS_ERROR << std::endl;
    } else {
        std::cout << RENEWAL_SUCCESSFUL <<
                     loans_.at(book_title)->get_due_date() <<
                     std::endl;
    }
}

// Checks parameter(s) and deletes loan from the structure.
void Library::return_loan(const std::string &book_title)
{
    if ( books_.find(book_title) == books_.end() ) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }
    if ( loans_.find(book_title) == loans_.end() ) {
        std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
        return;
    }
    delete loans_.at(book_title);
    loans_.at(book_title) = nullptr;
    loans_.erase(book_title);
    std::cout << RETURN_SUCCESSFUL << std::endl;
}
