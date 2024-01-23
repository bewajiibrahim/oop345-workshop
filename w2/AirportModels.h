#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H
#include <iostream>
#include <string>
namespace sdds {
	struct Airport {
	private:
		std::string m_code{};
		std::string m_name{};
		std::string m_city{};
		std::string m_state{};
		std::string m_country{};
		double m_latitude{};
		double m_longitude{};

		void reset();
	public:
		Airport();
		Airport(const char* code,
			const char* name,
			const char* city,
			const char* state,
			const char* country,
			const double latitude,
			const double longitude);
		Airport(const Airport& other);
		Airport& operator=(const Airport& other);

		std::ostream& print(std::ostream& os) const;
		std::istream& read(std::istream& is);
		operator bool()const;

		std::string getState() const;
		std::string getCountry() const;
	};
	std::ostream& operator<<(std::ostream& os, const Airport& A);
	std::istream& operator>>(std::istream& is, Airport& A);

	class AirportLog {
		Airport* m_airportArr{};
		size_t m_size{};

	public:
		AirportLog();
		AirportLog(const char* fname);
		AirportLog(const AirportLog& other);
		AirportLog(AirportLog&& other) noexcept;
		AirportLog& operator=(const AirportLog& other);
		AirportLog& operator=(AirportLog&& other) noexcept;

		~AirportLog();

		void addAirport(const Airport& other);
		AirportLog findAirport(const char* state, const char* country) const;

		Airport operator[](size_t i);
		operator size_t();
	};
}
#endif // !SDDS_AIRPORTMODELS_H