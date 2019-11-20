#include "loan.hh"

#include <string>

using namespace std;

Loan::Loan(Book* loaned_book, Person* loaner, Date* loan_due):
    book_(loaned_book),
    loaner_(loaner),
    due_date_(loan_due),
    renewals_(0)
{
}

Loan::~Loan()
{
    delete due_date_;
    due_date_ = nullptr;
}

Person* Loan::get_loaner()
{
    return loaner_;
}

string Loan::get_due_date()
{
    return due_date_->to_string();
}

string Loan::print_info( Date* today, bool print_borrower ) {
    string info_to_print = book_->get_title();
    if ( print_borrower ) {
        info_to_print += " : ";
        info_to_print += loaner_->get_name();
    }
    info_to_print += " : " + due_date_->to_string();
    if ( today < due_date_ or today == due_date_ ) {
        info_to_print += " : 0";
    } else {
        info_to_print += " : 1";
    }
    return info_to_print;
}

bool Loan::renew_loan()
{
    if ( renewals_ == DEFAULT_RENEWAL_AMOUNT ) {
        return false;
    }
    due_date_->advance_by_loan_length();
    ++renewals_;
    return true;
}
