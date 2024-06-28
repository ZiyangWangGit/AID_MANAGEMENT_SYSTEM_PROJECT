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
#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_

#include "iProduct.h"
#include "Status.h"

namespace sdds {
    const int minSku = 40000;
    const int maxSku = 99999;
    const int minQty = 1;
    const int maxQty = 9999;
    const int maxDesLength = 35;
    const double maxPrice = 9999.9;


    class Item : public iProduct {
        double m_price;
        int m_qtyOnHand;
        int m_qtyNeeded;
        char* m_description;
        bool m_isLinear;
    protected:
        Status m_state;
        int m_sku;
    protected:
        bool linear() const;
    public:
        Item();
        ~Item();
        Item(const Item&);
        Item& operator=(const Item&);
        virtual int qtyNeeded() const;
        virtual int qty() const;
        virtual operator double() const;
        virtual operator bool() const;
        virtual int operator-=(int qty);
        virtual int operator+=(int qty);
        virtual void linear(bool isLinear);
        void clear();
        virtual bool operator==(int sku)const;
        virtual bool operator==(const char* description)const;
        virtual std::ofstream& save(std::ofstream& ofstr) const;
        virtual std::ifstream& load(std::ifstream& ifstr);
        virtual std::ostream& display(std::ostream& ostr) const;
        virtual std::istream& read(std::istream& istr);
        virtual int readSku(std::istream& istr);
        int readIntInRange(std::istream& istr, int minVal, int maxVal);


    };
}
#endif

