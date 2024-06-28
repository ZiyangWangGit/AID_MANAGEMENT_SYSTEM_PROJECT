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
#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_

#include <string>
#include "Item.h"
#include "Date.h"

using namespace std;
namespace sdds {
	const int minPerSku = 10000;
	const int maxPerSku = 39999;

	class Perishable : public Item {
		char* m_handling;
		Date m_expire;
	public:
		Perishable();
		~Perishable();
		Perishable(const Perishable& other);
		Perishable& operator=(const Perishable& other);
		Date expiry() const;
		virtual int readSku(std::istream& istr) override;
		virtual std::ofstream& save(std::ofstream& ofstr)const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr)const override;
		virtual std::istream& read(std::istream& istr) override;
		operator bool() const;

	};

}


#endif