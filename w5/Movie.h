#ifndef MOVIE_H_
#define MOVIE_H_

namespace sdds {

    class Movie
    {
        std::string m_title{};
        std::string m_description{};
        unsigned m_releaseYear{};

    public:
        Movie() {};

        // constructs a movie object based on a string
        Movie(const std::string& strMovie);

        // returns title of the movie
        const std::string& title() const;

        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_description);
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

    };

}

#endif // MOVIE_H_