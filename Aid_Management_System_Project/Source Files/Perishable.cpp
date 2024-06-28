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
#include <string>
#include "Perishable.h"
#include "Date.h"

using namespace std;
namespace sdds {
	Perishable::Perishable() {
		m_handling = nullptr;
	}

	Perishable ::~Perishable() {
		delete[] m_handling;
		m_handling = nullptr;
	}

	Perishable::Perishable(const Perishable& other) : Item(other) {
		if (other.m_handling != nullptr) {
			m_handling = new char[strlen(other.m_handling) + 1];
			strcpy(m_handling, other.m_handling);
		}
		else {
			m_handling = nullptr;
		}
		m_expire = other.m_expire;
	}

	Perishable& Perishable::operator=(const Perishable& other) {
		if (this != &other) {
			Item::operator=(other);
			delete[] m_handling;
			if (other.m_handling != nullptr) {
				m_handling = new char[strlen(other.m_handling) + 1];
				strcpy(m_handling, other.m_handling);
			}
			else {
				m_handling = nullptr;
			}
			m_expire = other.m_expire;
		}
		return *this;
	}


	Date Perishable::expiry() const {
		return m_expire;
	}

	int Perishable::readSku(std::istream& istr) {
		cout << "SKU: ";
		m_sku = readIntInRange(istr, minPerSku, maxPerSku);
		return m_sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr)const {
		if (m_state) {
			Item::save(ofstr);
			ofstr << "\t";
			ofstr << m_handling << "\t";
			Date t = m_expire;
			t.formatted(false);
			ofstr << t;
			//ofstr << '\n';
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {

		Item::load(ifstr);
		ifstr.ignore(1000, '\t');
		char tempHandling[1000];
		ifstr.getline(tempHandling, 1000, '\t');
		delete[] m_handling;
		m_handling = new char[strlen(tempHandling) + 1];
		strcpy(m_handling, tempHandling);
		if (ifstr.peek() != EOF) {
			ifstr >> m_expire;
		}
		return ifstr;
	}

	ostream& Perishable::display(ostream& ostr) const {

		if (m_state) {
			if (linear() == false) {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << m_expire << endl;
				if (m_handling != nullptr && m_handling[0] != '\0') {
					ostr << "Handling Instructions: " << m_handling << endl;
				}
			}
			else {
				Item::display(ostr);
				ostr << (m_handling != nullptr && m_handling[0] != '\0' ? '*' : ' ') << m_expire;
			}
		}
		else {
			char localDescription[256];
			strcpy(localDescription, (const char*)(m_state));
			ostr << localDescription;
		}
		return ostr;
	}

	istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		cout << "Expiry date (YYMMDD): ";
		istr >> m_expire;
		istr.ignore();
		cout << "Handling Instructions, ENTER to skip: ";

		if (istr.bad()) {
			istr.clear();
			istr.ignore(1000, '\n');
		}

		char tempHandling[1000];
		istr.getline(tempHandling, 1000, '\n');
		delete[] m_handling;
		m_handling = new char[strlen(tempHandling) + 1];
		strcpy(m_handling, tempHandling);

		return istr;

	}

	Perishable::operator bool() const {
		return Item::m_sku != 0;
	}

}