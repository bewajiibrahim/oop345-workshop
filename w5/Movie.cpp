#include <iostream>
#include <string>
#include <iomanip>
#include "Movie.h"
#include "Book.h"

namespace sdds {

    Movie::Movie(const std::string& strMovie) {
        size_t pos{ 0 };
        std::string input{ strMovie };
        std::string temp{};

        // could be looped, but more convoluted
        // 1. finds position according to delimiter, assigns position
        // 2. extracts pre-position characters
        // 3. erases white space and assigns to appropriate member variable

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_title = temp;

        pos = findNewPos(input, pos, ',');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_releaseYear = stoi(temp);

        pos = findNewPos(input, pos, '\n');
        temp = input.substr(0, pos++);
        eraseWhiteSpace(temp);
        m_description = temp;
    }

    // returns title of the movie
    const std::string& Movie::title() const {
        return m_title;
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        if (movie.m_title != "") {
            os << std::right;
            os << std::setw(40) << movie.m_title << " | ";
            os << std::setw(4) << movie.m_releaseYear << " | ";
            os << std::setw(5) << movie.m_description;
            os << std::endl;
        }
        return os;
    }

}