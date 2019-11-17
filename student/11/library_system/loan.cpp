#include "loan.hh"

Loan::Loan(const Book* loaned_book, const Person* loaner, const Date* loan_date):
    book_(loaned_book),
    loaner_(loaner),
    loan_date_(loan_date)
{

}

Loan::~Loan()
{

}
