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

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Item.h"

using namespace std;
namespace sdds {


	Item::Item() {
		m_price = 0;
		m_qtyOnHand = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_isLinear = false;
		m_sku = 0;
	}

	Item::~Item() {
		delete[] m_description;
	}

	bool Item::linear() const {
		return m_isLinear;
	}

	Item::Item(const Item& another) {
		m_price = another.m_price;
		m_qtyOnHand = another.m_qtyOnHand;
		m_qtyNeeded = another.m_qtyNeeded;
		m_isLinear = another.m_isLinear;
		m_sku = another.m_sku;
		m_state.clear();

		if (another.m_description != nullptr) {
			m_description = new char[strlen(another.m_description) + 1];
			strcpy(m_description, another.m_description);
		}
		else {
			m_description = nullptr;
		}

	}

	Item& Item::operator=(const Item& another) {
		if (this != &another) {
			m_price = another.m_price;
			m_qtyOnHand = another.m_qtyOnHand;
			m_qtyNeeded = another.m_qtyNeeded;
			m_isLinear = another.m_isLinear;
			m_sku = another.m_sku;
			m_state = another.m_state;

			delete[] m_description;

			if (another.m_description != nullptr) {
				m_description = new char[strlen(another.m_description) + 1];
				strcpy(m_description, another.m_description);
			}
			else {
				m_description = nullptr;
			}

		}
		return *this;
	}

	int Item::qtyNeeded() const {
		return m_qtyNeeded;
	}

	int Item::qty() const {
		return m_qtyOnHand;
	}

	Item::operator double() const {
		return m_price;
	}


	Item::operator bool() const {
		return m_state;
	}

	int Item::operator-=(int qty) {
		m_qtyOnHand -= qty;
		return m_qtyOnHand;
	}

	int Item:: operator+=(int qty) {
		m_qtyOnHand += qty;
		return m_qtyOnHand;
	}

	void Item::linear(bool isLinear) {
		m_isLinear = isLinear;
	}

	void Item::clear() {
		m_state.clear();
	}

	bool Item::operator == (int sku) const {
		return m_sku == sku;
	}


	bool Item:: operator == (const char* description)const {
		if (description == nullptr || m_description == nullptr) {
			return false;
		}

		return strstr(m_description, description) != nullptr;
	}

	ofstream& Item::save(ofstream& ofstr) const {
		if (m_state) {
			ofstr << m_sku << "\t" << m_description << "\t" << m_qtyOnHand << "\t" << m_qtyNeeded << "\t" << m_price;
		}
		return ofstr;
	}

	ifstream& Item::load(ifstream& ifstr) {
		if (m_description != nullptr) {
			delete[] m_description;
			m_description = nullptr;
		}
		if (!ifstr) {
			cerr << "Input file stream read failed!";
		}
		else {
			ifstr >> m_sku;
			ifstr.ignore();
			char buffer[1000];
			ifstr.get(buffer, sizeof(buffer), '\t');
			if (ifstr.peek() == '\t') {
				ifstr.ignore();
			}
			m_description = new char[strlen(buffer) + 1];
			strcpy(m_description, buffer);

			ifstr >> m_qtyOnHand >> m_qtyNeeded >> m_price;

			//cout << m_sku << m_description << m_qtyOnHand << m_qtyNeeded << m_price;
		}

		return ifstr;

	}
	ostream& Item::display(ostream& ostr) const {
		if (m_state) {
			double moneyNeeded = (m_price * (m_qtyNeeded - m_qtyOnHand));
			if (m_isLinear == false) {
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qtyOnHand << endl;
				ostr << "Unit Price: $" << m_price << endl;
				ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << moneyNeeded << endl;
			}
			else {
				ostr << setw(5) << setfill(' ') << m_sku << " | ";

				if (m_description != nullptr) {
					int descriptionLength = strlen(m_description);
					if (descriptionLength >= maxDesLength) {
						for (int i = 0; i < maxDesLength; i++) {
							ostr << m_description[i];
						}
					}
					else {
						ostr << left << setw(35) << setfill(' ') << m_description;
					}
				}
				ostr << " | ";
				ostr << right << setw(4) << setfill(' ') << m_qtyOnHand << " | ";
				ostr << setw(4) << setfill(' ') << m_qtyNeeded << " | ";
				ostr << noshowpoint << fixed << setprecision(2) << setw(7) << setfill(' ') << m_price << " |";
			}
		}
		else {
			char localDescription[256];
			strcpy(localDescription, (const char*)(m_state));
			ostr << localDescription;
		}
		return ostr;
	}

	istream& Item::read(std::istream& istr) {
		if (m_description != nullptr) {
			delete[] m_description;
			m_description = nullptr;
		}
		m_state.clear();

		cout << "AMA Item:" << endl << "SKU: " << m_sku << endl << "Description: ";
		istr.ignore();
		char tempDescription[1000];
		istr.getline(tempDescription, 1000);

		m_description = new char[strlen(tempDescription) + 1];
		strcpy(m_description, tempDescription);

		cout << "Quantity Needed: ";
		m_qtyNeeded = readIntInRange(istr, minQty, maxQty);
		cout << "Quantity On Hand: ";
		m_qtyOnHand = readIntInRange(istr, 0, m_qtyNeeded);
		cout << "Unit Price: $";
		bool flag = false;
		do {
			istr >> m_price;
			if (istr.fail()) {
				cout << "Invalid number, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
			}
			else if (m_price > maxPrice || m_price < 0.0) {
				cout << "Value out of range [0.00<=val<=9999.00]: ";
			}
			else {
				flag = true;
			}
		} while (flag == false);

		return istr;
	}

	int Item::readSku(std::istream& istr) {
		cout << "SKU: ";
		m_sku = readIntInRange(istr, minSku, maxSku);

		return m_sku;
	}

	int Item::readIntInRange(std::istream& istr, int minVal, int maxVal) {
		bool flag = false;
		int userInput;
		do {
			istr >> userInput;
			if (istr.fail()) {
				cout << "Invalid Integer, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
			}
			else if (userInput > maxVal || userInput < minVal) {
				cout << "Value out of range [" << minVal << "<=val<=" << maxVal << "]: ";
			}
			else {
				flag = true;
			}
		} while (flag == false);
		return userInput;
	}
}