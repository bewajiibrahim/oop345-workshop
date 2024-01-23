#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

extern double g_taxrate;
extern double g_discount;

namespace sdds {

    class RideRequest {
        char m_custName[10]{};
        char m_custDetails[25]{};
        double m_price{};
        bool m_discount{};

    public:
        RideRequest() {};
        RideRequest(const RideRequest& src);
        RideRequest& operator=(RideRequest& src);
        std::istream& read(std::istream& is);
        void display();
    };
}  // namespace sdds
#endif