#include "Station.h"

#include <iomanip>
#include <iostream>

#include "Utilities.h"

namespace sdds {
    size_t Station::m_widthField{ 0 };
    size_t Station::id_generator{ 0 };

    Station::Station(const std::string& line) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_itemName = util.extractToken(line, next_pos, more);
        m_serialNum = std::stoul(util.extractToken(line, next_pos, more));
        m_numOfItems = std::stoul(util.extractToken(line, next_pos, more));
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
        m_description = util.extractToken(line, next_pos, more);
        id_generator++;
        m_stationID = id_generator;
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        m_serialNum += 1;
        return m_serialNum - 1;
    }

    size_t Station::getQuantity() const {
        return m_numOfItems;
    }

    void Station::updateQuantity() {
        if (m_numOfItems > 0) {
            m_numOfItems--;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        if (!full) {
            os << std::right << std::setw(3) << std::setfill('0') << m_stationID << " | ";
            os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | ";
            os << std::right << std::setw(6) << std::setfill('0') << m_serialNum << " | " << std::endl;
        }
        else {
            os << std::setw(0);
            os << std::right << std::setw(3) << std::setfill('0') << m_stationID << " | ";
            os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | ";
            os << std::right << std::setw(6) << std::setfill('0') << m_serialNum << " | ";
            os << std::right << std::setw(4) << std::setfill(' ') << m_numOfItems << " | ";
            os << m_description << std::endl;
        }
    }
}  // namespace sdds