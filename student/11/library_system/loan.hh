/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
 * TIE-0220x S2019
 *
 * */
#ifndef LOAN_HH
#define LOAN_HH

#include "person.hh"
#include "book.hh"
#include "date.hh"

const int DEFAULT_RENEWAL_AMOUNT = 6;

class Loan
{
public:
    Loan(Book* loaned_book,
         Person* loaner,
         Date* due_date);
    ~Loan();
    Person* get_loaner();
    std::string get_due_date();
    std::string print_info( Date* today, bool print_borrower );
    bool renew_loan();

private:
    Book* book_;
    Person* loaner_;
    Date* due_date_;
    int renewals_;
};

#endif // LOAN_HH
