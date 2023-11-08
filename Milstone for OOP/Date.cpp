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
#include <cstring>
#include "Date.h"
#include "Utils.h"

using namespace std;
namespace sdds {

    Date::Date() {
        ut.getSystemDate(&m_year, &m_month, &m_day);
    }

    Date::Date(int year, int month, int date) {
        m_year = year;
        m_month = month;
        m_day = date;
        validate();
    }


    bool Date::validate() {
        int currentYear, numberOfDays;
        bool valid = true;
        ut.getSystemDate(&currentYear, nullptr, nullptr);
        numberOfDays = ut.daysOfMon(m_month, m_year);


        if (m_year > largestYear || m_year < currentYear) {
            State = "Invalid year in date";
            State = 1;
            valid = false;
        }
        else if (m_month < 1 || m_month > 12) {
            State = "Invalid month in date";
            State = 2;
            valid = false;
        }
        else {
            if (m_day < 1 || m_day > numberOfDays) {
                State = "Invalid day in date";
                State = 3;
                valid = false;
            }
        }
        if (valid)
        {
            State.clear();
        }
        return valid;
    }

    int Date::uniqueDate() const {
        return m_year * 372 + m_month * 31 + m_day;
    }


    bool Date::operator==(const Date& other) const {
        return uniqueDate() == other.uniqueDate();
    }

    bool Date::operator!=(const Date& other) const {
        return uniqueDate() != other.uniqueDate();;
    }

    bool Date::operator<(const Date& other) const {
        return uniqueDate() < other.uniqueDate();
    }

    bool Date::operator>(const Date& other) const {
        return uniqueDate() > other.uniqueDate();
    }

    bool Date::operator<=(const Date& other) const {
        return uniqueDate() <= other.uniqueDate();
    }

    bool Date::operator>=(const Date& other) const {
        return uniqueDate() >= other.uniqueDate();
    }

    const Status& Date::state() const {
        return State;
    }

    Date& Date::formatted(bool format) {
        m_formatted = format;
        return *this;
    }

    Date::operator bool() const {
        return State;
    }


    istream& Date::read(std::istream& is) {
        int inputValue;
        is >> inputValue;

        if (is.fail()) {
            cerr << "Invalid date value";
            is.setstate(std::ios::failbit);
        }
        else {
            ut.testMode(false);
            ut.getSystemDate(&m_year, &m_month, &m_day);

            int length = 0;
            int temp = inputValue;
            while (temp > 0) {
                temp /= 10;
                length++;
            }

            if (inputValue > 0 && inputValue < 31) {

                m_day = inputValue;
                m_month = incorrectDefaultMonth;
            }


            else if (inputValue > 31 && inputValue < 100)
            {
                m_day = inputValue;
            }


            else if (length == 4) {
                m_month = inputValue / 100;
                m_day = inputValue % 100;
            }
            else if (length == 6) {
                m_year = inputValue / 10000 + 2000;
                m_month = (inputValue / 100) % 100;
                m_day = inputValue % 100;
            }
            else {
                m_year = inputValue / 10000 + 2000;
                m_month = (inputValue / 100) % 100;
                m_day = inputValue % 100;
            }

            bool checkState = validate();
            if (checkState == false) {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }


    ostream& Date::write(std::ostream& os)const {
        if (m_formatted) {
            os << m_year << "/";
            os.fill('0');
            os.setf(ios::right);
            os.width(2);
            os << m_month << "/";
            os.width(2);
            os << m_day;
        }
        else {
            os << m_year % 100;
            os.fill('0');
            os.setf(ios::left);
            os.width(2);
            os << m_month;
            os.width(2);
            os << m_day;
        }
        os.unsetf(ios::left);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Date& date) {
        date.write(os);
        return os;
    }

    std::istream& operator>>(std::istream& is, Date& date) {
        return date.read(is);
    }

}