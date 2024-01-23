#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds {

    Book::Book() {}

    Book::Book(const std::string& strBook) {
        size_t pos{ 0 };
        std::string input{ strBook };
        std::string temp{};

        // could be looped, but more convoluted
        // 1. finds position according to delimiter, assigns position
        // 2. extracts pre-position characters
        // 3. erases white space and assigns to appropriate member variable

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_author = temp;

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_title = temp;

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_country = temp;

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_price = stod(temp);

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_year = stoi(temp);

        pos = findNewPos(input, pos, '\n');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_desc = temp;
    }

    const std::string& Book::title() const {
        return m_title;
    }

    const std::string& Book::country() const {
        return m_country;
    }

    const size_t& Book::year() const {
        return m_year;
    }

    double& Book::price() {
        return m_price;
    }


    // UTILITY HELPERS //

    std::ostream& operator<<(std::ostream& os, const Book& book) {
        if (book.m_title != "") {
            os << std::right;

            os << std::setw(20) << book.m_author << " | ";
            os << std::setw(22) << book.m_title << " | ";
            os << std::setw(5) << book.m_country << " | ";
            os << std::setw(4) << book.m_year << " | ";
            os << std::fixed << std::setprecision(2);
            os << std::setw(6) << book.m_price << " | ";
            os << std::left;
            os << std::setw(22) << book.m_desc;

            os << std::endl;
        }
        return os;
    }


    // erases trailing and leading white space of a string
    void eraseWhiteSpace(std::string& str) {
        unsigned int i = 0;
        while (str[i] == ' ') {
            str.erase(i, 1);
        }
        i = str.length() - 1;
        while (str[i] == ' ') {
            str.erase(i--, 1);
        }
    }

    // finds a new position in a complete supplied string, according to a specific delimiter
    size_t findNewPos(std::string& str, size_t pos, char delim) {
        str.erase(0, pos);
        pos = str.find(delim);
        return pos;
    }
}