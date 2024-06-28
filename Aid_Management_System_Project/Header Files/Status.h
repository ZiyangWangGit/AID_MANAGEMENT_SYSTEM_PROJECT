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
#ifndef SDDS_STATUS_H_
#define SDDS_STATUS_H_
#include <iostream>

namespace sdds {
	class Status {
		char* m_description;
		int m_statusCode;

	public:
		Status(const char* statusDescript = nullptr, int optStatusCode = 0);
		~Status();
		Status& operator=(const Status& other);
		Status& operator=(int code);
		Status& operator=(const char* statusDescript);
		operator int()const;
		operator const char* ()const;
		operator bool()const;
		Status& clear();
	};
	std::ostream& operator<<(std::ostream& os, const Status& s);
}

#endif 