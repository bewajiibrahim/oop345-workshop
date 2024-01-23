/***********************************************************************
Student ID: 128143203
Email: iabewaji@myseneca.ca
Date of completion: 24 September 2023

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
***********************************************************************/
#include <iomanip>
#include <fstream>
#include "AirportModels.h"
using namespace std;
namespace sdds {
	std::ostream& Airport::print(std::ostream& os) const
	{
		if (*this) {
			os.fill('.');
			os << right << setw(20) << "Airport Code" << " : " <<
				left << setw(30) << m_code << "\n" <<
				right << setw(20) << "Airport Name" << " : " <<
				left << setw(30) << m_name << "\n" <<
				right << setw(20) << "City" << " : " <<
				left << setw(30) << m_city << "\n" <<
				right << setw(20) << "State" << " : " <<
				left << setw(30) << m_state << "\n" <<
				right << setw(20) << "Country" << " : " <<
				left << setw(30) << m_country << "\n" <<
				right << setw(20) << "Latitude" << " : " <<
				left << setw(30) << m_latitude << "\n" <<
				right << setw(20) << "Longitude" << " : " <<
				left << setw(30) << m_longitude << '\n';
			os.fill(' ');
		}
		else cout << "Empty Airport";

		return os;
	}
	void Airport::reset()
	{
		m_code.clear();
		m_name.clear();
		m_city.clear();
		m_state.clear();
		m_country.clear();
		m_latitude = .0f;
		m_longitude = .0f;
	}
	Airport::Airport() {}
	Airport::Airport(const char* code,
		const char* name,
		const char* city,
		const char* state,
		const char* country,
		const double latitude,
		const double longitude) :
		m_code(code), m_name(name), m_city(city), m_state(state),
		m_country(country), m_latitude(latitude), m_longitude(longitude) {}
	Airport::Airport(const Airport& other)
	{
		*this = other;
	}
	Airport& Airport::operator=(const Airport& other)
	{
		if (this != &other) {
			m_code = other.m_code;
			m_name = other.m_name;
			m_city = other.m_city;
			m_state = other.m_state;
			m_country = other.m_country;
			m_latitude = other.m_latitude;
			m_longitude = other.m_longitude;
		}
		return *this;
	}
	istream& Airport::read(istream& is)
	{
		reset();
		if (is) {
			getline(is, m_code, ',');
			getline(is, m_name, ',');
			getline(is, m_city, ',');
			getline(is, m_state, ',');
			getline(is, m_country, ',');
			is >> m_latitude; is.ignore();
			is >> m_longitude; is.ignore();
		}
		return is;
	}
	Airport::operator bool() const
	{
		return m_name[0] != '\0';
	}
	string Airport::getState() const
	{
		return m_state;
	}
	string Airport::getCountry() const
	{
		return m_country;
	}
	ostream& operator<<(ostream& os, const Airport& A)
	{
		return A.print(os);
	}
	istream& operator>>(istream& is, Airport& A)
	{
		return A.read(is);
	}


	AirportLog::AirportLog() {}
	AirportLog::AirportLog(const char* fname)
	{
		ifstream fptr(fname);
		string tempstr;

		if (fptr.is_open()) {
			while (getline(fptr, tempstr))
				m_size++;
			m_size--;
			fptr.close();
		}

		if (m_size > 0) {
			fptr.open(fname);

			//remove header line 
			while (fptr.get() != '\n');

			m_airportArr = new Airport[m_size];
			for (size_t i = 0; i < m_size; i++)
				m_airportArr[i].read(fptr);

			fptr.close();
		}
	}
	AirportLog::AirportLog(const AirportLog& other)
	{
		*this = other;
	}
	AirportLog::AirportLog(AirportLog&& other) noexcept :
		m_airportArr{}, m_size{}
	{
		*this = move(other);
	}
	AirportLog& AirportLog::operator=(const AirportLog& other)
	{
		if (this != &other) {
			m_size = other.m_size;

			delete[] m_airportArr;
			m_airportArr = new Airport[m_size];
			for (size_t i = 0; i < m_size; i++)
				m_airportArr[i] = other.m_airportArr[i];

		}
		return *this;
	}
	AirportLog& AirportLog::operator=(AirportLog&& other) noexcept
	{
		if (this != &other) {
			delete[] m_airportArr;

			m_size = other.m_size;
			m_airportArr = other.m_airportArr;

			other.m_airportArr = nullptr;
			other.m_size = 0;
		}
		return *this;
	}
	AirportLog::~AirportLog()
	{
		delete[] m_airportArr;
	}
	void AirportLog::addAirport(const Airport& other)
	{
		Airport* temp = new Airport[m_size + 1];

		for (size_t i = 0; i < m_size; i++)
			temp[i] = m_airportArr[i];

		//accesing the index and updating the value in the same line
		//won't cause trouble
		temp[m_size++] = other;

		delete[] m_airportArr;
		m_airportArr = temp;
	}
	AirportLog AirportLog::findAirport(const char* state, const char* country) const
	{
		AirportLog foundAirports;

		for (size_t i = 0; i < m_size; i++)
			if (m_airportArr[i].getState() == state && m_airportArr[i].getCountry() == country)
				foundAirports.addAirport(m_airportArr[i]);

		return foundAirports;
	}
	Airport AirportLog::operator[](size_t i)
	{
		Airport temp{};
		if (i < m_size)
			temp = m_airportArr[i];
		return temp;
	}
	AirportLog::operator size_t()
	{
		return m_size;
	}
}
