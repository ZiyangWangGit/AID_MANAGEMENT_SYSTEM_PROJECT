/*************************************************************************************

*

* Student Name :Ziyang Wang

* Student ID  :154296222

* Course/Section: OOP244
*

* I have done all the coding by myself and only copied the code that my professor

* provided to complete my workshops and assignments.

*

**************************************************************************************/
#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include "Status.h"


namespace sdds {

	const int largestYear = 2030;
	const int incorrectDefaultMonth = 13;
	const int incorrectDefaultDate = 32;

	class Date {
		int m_year;
		int m_month;
		int m_day;
		bool m_formatted = true;
		Status State;

	public:
		Date();
		Date(int year, int month, int day);
		bool validate();
		int uniqueDate()const;
		bool operator==(const Date& other) const;
		bool operator!=(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;

		operator bool() const;
		const Status& state() const;
		Date& formatted(bool format);

		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout)const;
	};

	std::ostream& operator<<(std::ostream& os, const Date& date);
	std::istream& operator>>(std::istream& is, Date& date);

}
#endif