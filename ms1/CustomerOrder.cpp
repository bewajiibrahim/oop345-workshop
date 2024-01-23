#include "CustomerOrder.h"
#include "Utilities.h"
#include <vector>
#include <iomanip>

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {

	}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities util;
		size_t pos = 0u;
		bool more = true;

		m_name = util.extractToken(str, pos, more);

		m_product = util.extractToken(str, pos, more);

		std::vector<std::string> temp;

		while (more) {
			temp.push_back(util.extractToken(str, pos, more));
		}

		m_cntItem = temp.size();
		m_lstItem = new Item * [temp.size()];

		for (size_t i = 0; i < temp.size(); i++) {
			m_lstItem[i] = new Item(temp[i]);
		}

		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();

	}

	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		*this = std::move(co);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_cntItem = co.m_cntItem;
			m_name = co.m_name;
			m_product = co.m_product;

			m_lstItem = co.m_lstItem;
			co.m_lstItem = nullptr;
			co.m_cntItem = 0u;

		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool isOrderFilled = false;
		int filledCounter = 0;
		for (int i = 0; i < (int)m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled) {
				filledCounter++;
			}
		}
		if (filledCounter == (int)m_cntItem)
			isOrderFilled = true;

		return isOrderFilled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (int i = 0; i < (int)m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				return m_lstItem[i]->m_isFilled;
			}
		}

		// If the item is not found, you can consider it as not filled.
		return false;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (int i = 0; i < (int)m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					break;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}


	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << '\n';
		for (int i = 0; i < (int)m_cntItem; i++) {
			os << "[" << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::setw(m_widthField) << std::left;
			os << m_lstItem[i]->m_itemName;
			os << (m_lstItem[i]->m_isFilled ? "   - FILLED" : " - TO BE FILLED") << std::endl;
		}
	}
}