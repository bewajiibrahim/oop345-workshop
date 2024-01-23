#include "RideRequest.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <cstring>

double g_taxrate;
double g_discount;

namespace sdds {
    RideRequest::RideRequest(const RideRequest& src) {
        strcpy(m_custName, src.m_custName);
        strcpy(m_custDetails, src.m_custDetails);
        m_price = src.m_price;
        m_discount = src.m_discount;
    }

    RideRequest& RideRequest::operator=(RideRequest& src) {
        if (this != &src) {
            strcpy(m_custName, src.m_custName);
            strcpy(m_custDetails, src.m_custDetails);
            m_price = src.m_price;
            m_discount = src.m_discount;
        }
        return *this;
    }

    std::istream& RideRequest::read(std::istream& is) {
        if (is) {
            is.getline(m_custName, std::numeric_limits<std::streamsize>::max(), ',');
            is.getline(m_custDetails, std::numeric_limits<std::streamsize>::max(), ',');
            is >> m_price;
            is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            char discount{};
            is >> discount;
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (discount == 'N') {
                m_discount = false;
            }
            else if (discount == 'Y') {
                m_discount = true;
            }
        }
        return is;
    }

    void RideRequest::display() {
        double fullPrice = ((m_price * g_taxrate) + m_price);
        static int counter = 0;
        if (m_custName[0] != '\0') {
            std::cout << std::left << std::setw(2) << ++counter << ". ";
            std::cout << std::left << std::setw(10) << m_custName << "|";
            std::cout << std::left << std::setw(25) << m_custDetails << "|";
            std::cout << std::left << std::setw(12) << std::fixed << std::setprecision(2) << fullPrice << "|";
            if (m_discount) {
                double discountFullPrice = fullPrice - g_discount;
                std::cout << std::right << std::setw(13) << std::fixed << std::setprecision(2) << discountFullPrice;
            }
            std::cout << std::endl;
        }
        else {
            std::cout << std::left << std::setw(2) << ++counter << ". ";
            std::cout << "No Ride Request" << std::endl;
        }
    }
}  // namespace sdds