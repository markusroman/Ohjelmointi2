#include "loan.hh"

#include <string>

using namespace std;

Loan::Loan(Book* loaned_book, Person* loaner, Date* due_date):
    book_(loaned_book),
    loaner_(loaner),
    due_date_(due_date)
{
    due_date_->advance_by_loan_length();
}

Loan::~Loan()
{
    
}

Person* Loan::get_loaner()
{
    return loaner_;
}

string Loan::print_info( Date* today, bool print_borrower ) {
    string info_to_print = book_->get_title();
    if ( print_borrower ) {
        info_to_print += " : ";
        info_to_print += loaner_->get_name();
    }
    info_to_print += " : " + due_date_->to_string();
    if ( today < due_date_ ) {
        info_to_print += " : 0";
    } else {
        info_to_print += " : 1";
    }
    return info_to_print;
}
