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
#include <cstring>
#include "Menu.h"

using namespace std;

namespace sdds {

	Menu::Menu(const char* menu) {

		size_t characters;
		int optionNumber = 1;
		characters = strlen(menu);  //check how many characters within the string;

		for (int i = 0; i < characters; i++) {
			if (menu[i] == '\t') {
				optionNumber++;
			}
		}

		if ((optionNumber > maxOption) || (menu == nullptr)) {
			menuContent = nullptr;
			menuValid = false;
			numOfOption = 0;
		}
		else {
			menuContent = new char[(strlen(menu) + 1)];
			strcpy(menuContent, menu);
			numOfOption = optionNumber;
			menuValid = true;
		}
	}

	Menu :: ~Menu() {
		delete[] menuContent;
	}

	unsigned int Menu::run() {

		unsigned int numEntered;
		unsigned int num = numOfOption;

		if (menuValid == false) {
			cout << "Invalid Menu!" << endl;
			numEntered = 0;
		}
		else {
			int characterCount = 0;
			for (int i = 1; i <= numOfOption; i++) {
				cout << i << "- ";

				while (menuContent[characterCount] != '\t' && menuContent[characterCount] != '\0') {
					cout << menuContent[characterCount];
					characterCount++;
				}
				cout << endl;
				characterCount++;
			}

			cout << "---------------------------------" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";

			bool flag = false;
			do {
				cin >> numEntered;
				if (numEntered < 0 || numEntered > num) {
					cout << "Value out of range [0<=val<=" << num << "]: ";
				}
				else if (cin.fail()) {
					cout << "Invalid Integer, retry: ";
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else {
					flag = true;
				}
			} while (!(flag));
		}

		return numEntered;
	}
}