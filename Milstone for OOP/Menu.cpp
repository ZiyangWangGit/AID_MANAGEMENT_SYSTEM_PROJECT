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

		int characters;
		int optionNumber = 0;
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
		if (menuValid == true) {
			delete[] menuContent;
		}
	}

	unsigned int Menu::run() {

		unsigned int numEntered;

		if (menuValid == false) {
			cout << "Invalid Menu!" << endl;
			numEntered = 0;
		}
		else {
			cout << menuContent << endl;
			cout << "---------------------------------" << endl;
			cout << "0- Exit" << endl;

			do {
				cout << "> ";
				cin >> numEntered;
				if (numEntered < 0 || numEntered > numOfOption) {
					cout << "Value out of range [0<=" << numOfOption << "me <= X]: ";
				}
				else if (!(isdigit(numEntered))) {
					cout << "Invalid Integer, retry: ";
				}
			} while (numEntered < 0 || numEntered > numOfOption || !(isdigit(numEntered)));
		}

		return numEntered;
	}
}