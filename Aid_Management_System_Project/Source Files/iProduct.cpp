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
#include "iProduct.h"

namespace sdds {

    std::ostream& operator<<(std::ostream& ostr, const iProduct& product) {
        return product.display(ostr);
    }

    std::istream& operator>>(std::istream& istr, iProduct& product) {
        return product.read(istr);
    }
}
