#include <fstream>
#include <string>
#include <iomanip>
#include "SpellChecker.h"
#include "Book.h"

namespace sdds {

    SpellChecker::SpellChecker(const char* filename) {

        std::fstream file;
        file.open(filename);

        if (file.is_open()) {
            int pos{ 0 };
            std::string line;
            for (unsigned i{ 0 }; i < m_size; i++) {
                line = "";
                pos = 0;

                // read a line from file
                std::getline(file, line, '\n');

                // ascii 32 == <space>
                pos = findNewPos(line, pos, 32);

                // splice pre-position characters into badWords array
                m_badWords[i] = line.substr(0, pos++);

                // extract from position after extracted badWord -> end of line
                line = line.substr(pos, line.length());

                // erase leading whitespace from extraction and assign to goodWords array
                eraseWhiteSpace(line);
                m_goodWords[i] = line;
            }
        }
        else {
            // throw an exception if file does not exist
            throw "Bad file name!";
        }

    }

    void SpellChecker::operator()(std::string& text) {

        for (unsigned i{ 0 }; i < m_size; i++) {
            unsigned pos{ 0 };
            pos = 0;
            while (text[pos] != '\0') {
                if (text[pos] == m_badWords[i][0]) {

                    // identifies the integer value for length of the bad word
                    unsigned wordLen = m_badWords[i].length();

                    // extracts the word to check for a match to a bad word
                    std::string word = text.substr(pos, wordLen);

                    if (word == m_badWords[i]) {

                        //replaces the bad word with the good word in the text
                        text.replace(pos, m_badWords[i].length(), m_goodWords[i]);

                        // increments the tracker of the associated fixed word in parallel
                        m_fixedWords[i]++;
                    }
                }
                pos++;
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream&) const {
        std::cout << "Spellchecker Statistics" << std::endl;
        for (unsigned i{ 0 }; i < words; i++) {
            std::cout << std::right;
            std::cout << std::setw(15) << m_badWords[i];
            std::cout << std::left << ": ";
            std::cout << m_fixedWords[i] << " replacements" << std::endl;
        }
    }


}