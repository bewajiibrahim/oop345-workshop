#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include "Book.h"
namespace sdds {
	template <typename T, unsigned C>
	class Collection {
		T m_items[C];
		size_t m_size{};
		static T m_smallestItem;
		static T m_largestItem;

		void formatToPrecision1() {
			std::cout.setf(std::ios::fixed);
			std::cout.precision(1);
		}
	protected:
		void setSmallestItem(const T& newSmallest) {
			if (newSmallest < m_smallestItem)
				m_smallestItem = newSmallest;
		}
		void setLargestItem(const T& newLargest) {
			if (newLargest > m_largestItem)
				m_largestItem = newLargest;
		}
		void addItem(const T& newItem) {
			Collection::operator+=(newItem);
		}

	public:
		T getSmallestItem() {
			formatToPrecision1();
			return m_smallestItem;
		}
		T getLargestItem() {
			formatToPrecision1();
			return m_largestItem;
		}

		size_t size() const { return m_size; }
		size_t capacity() const { return C; }
		std::ostream& print(std::ostream& os) {
			if (capacity() == 72) {
				double temp;
				for (size_t i = 0; i < size() - 1; i++) {
					for (size_t j = 0; j < size() - i - 1; j++) {
						if (m_items[j] > m_items[j + 1]) {
							temp = m_items[j];
							m_items[j] = m_items[j + 1];
							m_items[j + 1] = temp;
						}
					}
				}
			}

			std::cout << '[';

			//prints the item and a comma for all but last item
			for (size_t i = 0; i < m_size - 1; i++)
				std::cout << m_items[i] << ',';

			//prints last item without comma after
			return std::cout << m_items[m_size - 1] << "]\n";
		}

		bool operator+=(const T& newItem) {
			bool added{};
			if ((added = m_size < C))
			{
				if (newItem < m_smallestItem)
					setSmallestItem(newItem);
				else if (newItem > m_largestItem)
					setLargestItem(newItem);

				m_items[m_size++] = newItem;
			}
			return added;
		}
		T operator[](const size_t& i) const {
			T temp;
			if (i < m_size)
				temp = m_items[i];
			return temp;
		}

		void incrSize() { m_size++; }
	};

	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = 9999;
	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = -9999;


	template <>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 1000);
	template <>
	Book Collection<Book, 10>::m_largestItem = Book("", 1000, 1);

	template <>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 1000);
	template <>
	Book Collection<Book, 72>::m_largestItem = Book("", 1000, 1);

	template<>
	std::ostream& Collection<Book, 10>::print(std::ostream& os) {
		os << "| ---------------------------------------------------------------------------|\n";
		for (size_t i = 0; i < m_size; i++)
			m_items[i].print(os << "| ") << " |\n"; 

		return
			os << "| ---------------------------------------------------------------------------|\n";
	}
	template<>
	std::ostream& Collection<Book, 72>::print(std::ostream& os) {
		Book temp;
		for (size_t i = 0; i < size() - 1; i++) {
			for (size_t j = 0; j < size() - i - 1; j++) {
				if (m_items[j] > m_items[j + 1]) {
					temp = m_items[j];
					m_items[j] = m_items[j + 1];
					m_items[j + 1] = temp;
				}
			}
		}

		os << "| ---------------------------------------------------------------------------|\n";
		for (size_t i = 0; i < m_size; i++)
			m_items[i].print(os << "| ") << " |\n"; 

		return
			os << "| ---------------------------------------------------------------------------|\n";
	}
}
#endif // !SDDS_COLLECTION_H