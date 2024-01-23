
#ifndef BOOK_H_
#define BOOK_H_

#include <string>

namespace sdds {

    class Book
    {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        std::string m_desc;
        size_t m_year;
        double m_price;

    public:
        // default constructor
        Book();

        // constructor that accepts a string to splice
        Book(const std::string& strBook);

        // returns title of book
        const std::string& title() const;

        // returns publication country
        const std::string& country() const;

        // returns publication year
        const size_t& year() const;

        // returns a non-constant price, can be updated by client
        double& price();

        template <typename T>
        void fixSpelling(T& spellChecker) {
            // calls the operator() of spellchecker, passing to it the book description
            spellChecker(m_desc);
            // ASSUMPTION: in this design, type T must have an overload of the operator() that accepts a string as a parameter
        }

        friend std::ostream& operator<<(std::ostream& os, const Book& book);

    };

    // erases trailing and leading white space of a string
    size_t findNewPos(std::string& str, size_t pos, char delim);

    // finds a new position in a complete supplied string, according to a specific delimiter
    void eraseWhiteSpace(std::string& str);

}

#endif // BOOK_H_