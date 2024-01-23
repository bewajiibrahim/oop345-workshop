#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <iostream>
#include <string>

namespace sdds {

    template <typename T>
    class Collection
    {
        std::string m_name{};
        T* m_collection{};
        size_t m_size{};
        void (*m_observer)(const Collection<T>&, const T&) {};

    public:

        Collection() {}

        // no support for copy operations
        Collection(const std::string& name) : m_name(name) {}
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;

        // deletes dynamic array
        ~Collection() { delete[] m_collection; }

        // returns name
        const std::string& name() const {
            return m_name;
        }

        // returns size
        size_t size() const {
            return m_size;
        }

        // set m_observer to function address
        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            m_observer = observer;
        }

        Collection<T>& operator+=(const T& item) {
            bool match{ false };
            for (unsigned i{ 0 }; i < m_size; i++) {
                if (m_collection[i].title() == item.title()) {
                    match = true;
                }
            }
            // if no match is found in array based on title
            if (!match) {
                T* temp = new T[m_size + 1];
                for (unsigned i{ 0 }; i < m_size; i++) {
                    temp[i] = m_collection[i];
                }

                // delete unused old collection
                delete[]m_collection;

                // assign item to new collection
                temp[m_size] = item;
                m_size++;
                m_collection = temp;

                // calls observer if active
                if (m_observer) {
                    m_observer(*this, item);
                }
            }
            return *this;
        }

        T& operator[](size_t idx) const {
            if (idx < 0 || idx >= m_size) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
            }
            else {
                return m_collection[idx];
            }
        }

        T* operator[](const std::string& title) {
            T* adr = nullptr;
            for (unsigned i{ 0 }; i < m_size; i++) {
                if (m_collection[i].title() == title) {
                    adr = &m_collection[i];
                }
            }
            return adr == nullptr ? nullptr : adr;
        }

        friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
            for (unsigned i{ 0 }; i < collection.size(); i++) {
                os << collection.m_collection[i];
            }
            return os;
        }

    };


}

#endif // COLLECTION_H_