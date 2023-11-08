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
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include "Status.h"

using namespace std;
namespace sdds {
    Status::Status(const char* statusDescript, int optStatusCode) {
        if (statusDescript != nullptr && statusDescript[0] != '\0') {
            m_description = new char[strlen(statusDescript) + 1];
            strcpy(m_description, statusDescript);
        }
        else {
            m_description = nullptr;
        }
        m_statusCode = 0;
    }

    Status::~Status() {
        delete[] m_description;
    }


    Status& Status::operator=(const Status& other) {
        if (other.m_description != nullptr) {
            m_description = new char[strlen(other.m_description) + 1];
            strcpy(m_description, other.m_description);
        }
        else {
            m_description = nullptr;
        }
        m_statusCode = other.m_statusCode;

        return *this;
    }

    Status& Status::operator=(int code) {

        m_statusCode = code;
        return *this;
    }

    Status& Status::operator=(const char* statusDescript) {
        if (m_description != nullptr) {
            delete[] m_description;
            m_description = nullptr;
        }
        if (statusDescript != nullptr && statusDescript[0] != '\0') {
            m_description = new char[strlen(statusDescript) + 1];
            strcpy(m_description, statusDescript);
        }
        return *this;
    }

    Status::operator int()const {
        return m_statusCode;
    }

    Status::operator const char* () const {
        return m_description;
    }

    Status::operator bool()const {
        return (m_description == nullptr);
    }

    Status& Status::clear() {

        m_description = nullptr;
        m_statusCode = 0;

        return *this;
    }

    ostream& operator<<(ostream& os, const Status& s) {

        if ((int(s) == 0) && (!s)) {
            os << "Invalid Integer";
        }

        else if (!s) {
            os << "ERR#" << int(s);
            os << ": " << (const char*)(s);
        }
        return os;
    }

}