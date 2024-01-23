#include "Book.h"
using namespace std;
namespace sdds {
	Book::Book(const string& title, unsigned nChapters, unsigned nPages) :
		m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}
	Book::Book() {}

	Book::operator bool() const
	{
		return m_title[0] != '\0' && m_numChapters > 0 && m_numPages > 0;
	}

	Book& Book::operator=(const Book& other)
	{
		if (this != &other) {
			m_title = other.m_title;
			m_numChapters = other.m_numChapters;
			m_numPages = other.m_numPages;
		}
		return *this;
	}

	bool Book::operator<(const Book& other) const
	{
		return pgsPerChptrs() < other.pgsPerChptrs();
	}

	bool Book::operator>(const Book& other) const
	{
		return other < *this;
	}

	double Book::pgsPerChptrs() const
	{
		return (double)m_numPages / m_numChapters;
	}

	ostream& Book::print(ostream& os) const
	{
		if (*this) {
			os.setf(ios::right); os.setf(ios::fixed);
			os.width(m_numChapters > 9 ? 49 : 50);
			os << m_title << ',' << m_numChapters << ',' << m_numPages << " | (";

			os.precision(6);
			os << pgsPerChptrs() << ")    ";

			os.unsetf(ios::right);
		}
		else
			cout << "| Invalid book data";

		return os;
	}
	ostream& operator<<(ostream& os, const Book& bk)
	{
		return bk.print(os);
	}
}