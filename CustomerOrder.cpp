#include "CustomerOrder.h"

#include <iomanip>

#include "Utilities.h"

namespace sdds {
    size_t CustomerOrder::m_widthField{ 0 };

    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw std::runtime_error("Copy constructor, throw an exception");
    }

    CustomerOrder::CustomerOrder() {}

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_listItem[i];
        }
        delete[] m_listItem;
    }

    CustomerOrder::CustomerOrder(const std::string& src) {
        Utilities util;
        size_t pos = 0;
        bool more = true;
        m_name = util.extractToken(src, pos, more);
        m_product = util.extractToken(src, pos, more);
        size_t itemsPos = pos;
        std::string items;
        while (more) {
            items = util.extractToken(src, pos, more);
            m_cntItem++;
        }
        more = true;
        m_listItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++) {
            m_listItem[i] = new Item(util.extractToken(src, itemsPos, more));
        }
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_listItem[i];
            }
            delete[] m_listItem;
            m_name = std::move(src.m_name);
            m_product = std::move(src.m_product);
            m_cntItem = src.m_cntItem;
            src.m_cntItem = 0;
            m_listItem = src.m_listItem;
            src.m_listItem = nullptr;
        }
        return *this;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_listItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_listItem[i]->m_itemName == itemName && !m_listItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_listItem[i]->m_itemName == station.getItemName()) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_listItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << std::endl;
                    return;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setfill('0') << std::setw(6) << m_listItem[i]->m_serialNumber << "] ";
            os << std::left << std::setfill(' ') << std::setw(m_widthField) << m_listItem[i]->m_itemName << " ";
            os << "- " << (m_listItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}  // namespace sdds