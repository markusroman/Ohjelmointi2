/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
 * TIE-0220x S2019
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
    Loan(const Book* loaned_book,
         const Person* loaner,
         const Date* loan_date);
    ~Loan();

private:
    const Book* book_;
    const Person* loaner_;
    const Date* loan_date_;
};

#endif // LOAN_HH
