#ifndef SPELL_CHECKER_H_
#define SPELL_CHECKER_H_

#include <string>
#include <iostream>
#include "Book.h"

namespace sdds {

    constexpr size_t words{ 6 };

    class SpellChecker
    {
        const size_t m_size = words;
        std::string m_badWords[words];
        std::string m_goodWords[words];
        unsigned m_fixedWords[words]{};

    public:
        SpellChecker(const char* filename);

        // searches the text and replaces any mispelled word with the correct version
        // it should count how many times each misspelled word has been replaced
        void operator()(std::string& text);

        void showStatistics(std::ostream&) const;
    };

}

#endif // SPELL_CHECKER_H_