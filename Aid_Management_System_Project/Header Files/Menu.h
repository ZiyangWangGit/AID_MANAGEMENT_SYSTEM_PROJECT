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
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_

namespace sdds {

	const int maxOption = 15;

	class Menu {
		char* menuContent;
		int numOfOption;
		bool menuValid;

	public:
		Menu(const char* menu);
		~Menu();
		unsigned int run();
	};
}


#endif

