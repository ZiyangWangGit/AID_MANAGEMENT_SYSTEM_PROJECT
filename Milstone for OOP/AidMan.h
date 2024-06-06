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
#ifndef SDDS_AIDMAN_H_
#define SDDS_AIDMAN_H_

#include "Menu.h"
#include "iProduct.h"

const int noFileLength = 8;
const int contentLength = 200;


namespace sdds {
	const int sdds_max_num_items = 100;

	class AidMan {
		char* fileName;
		int productItems;
		iProduct* productArray[sdds_max_num_items];
		Menu mainMenu;
		unsigned int menu();

	public:
		AidMan();
		AidMan(const char* filename);
		~AidMan();
		void run();
		void save();
		bool load();
		int search(int sku) const;
		int list(const char* sub_desc = nullptr);
		void remove(int index);
		void sort();
		void shipItem();
	};

}


#endif

