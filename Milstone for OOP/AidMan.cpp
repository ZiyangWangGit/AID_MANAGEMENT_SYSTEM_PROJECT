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
#include <limits>
#include "Utils.h"
#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"

using namespace std;
namespace sdds {
	unsigned int AidMan::menu() {
		int year, month, date;
		unsigned int userSelection;

		ut.getSystemDate(&year, &month, &date);
		cout << "Aid Management System" << endl;
		cout << "Date: " << year << "/" << month << "/0" << date << endl;
		cout << "Data file: ";
		if (fileName != nullptr) {
			cout << fileName << endl;
		}
		else {
			cout << "No file" << endl;
		}
		cout << "---------------------------------" << endl;
		userSelection = mainMenu.run();

		return userSelection;
	}

	AidMan::AidMan() : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		for (int i = 0; i < sdds_max_num_items; ++i) {
			productArray[i] = nullptr;
		}

		fileName = nullptr;
		productItems = 0;
	}

	AidMan::AidMan(const char* fileName) : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		this->fileName = nullptr;

		if (fileName != nullptr) {
			this->fileName = new char[strlen(fileName) + 1];
			strcpy(this->fileName, fileName);
		}

		for (int i = 0; i < sdds_max_num_items; ++i) {
			productArray[i] = nullptr;
		}

		productItems = 0;
	}
	AidMan::~AidMan() {
		delete[] fileName;
		for (int i = 0; i < productItems; ++i) {
			delete productArray[i];
		}
		productItems = 0;
	}

	void AidMan::run() {
		int userInput;
		char contentForMenu[] = "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database";
		do {
			int tabCount = 0;
			bool flag = true;
			userInput = menu();
			if (userInput == 0) {
				cout << "Exiting Program!" << endl;
				ofstream outputFile(fileName);
				for (int i = 0; i < productItems; ++i) {
					productArray[i]->save(outputFile);
					outputFile << '\n';
				}
			}
			else {
				if (fileName == nullptr && userInput != 7) {
					userInput = 7;
				}
				for (int i = 0; i < contentLength && flag == true; i++) {
					if (contentForMenu[i] == '\t') {
						tabCount++;
					}
					if (tabCount == (userInput - 1)) {
						if (tabCount > 0) {
							i += 1;
						}
						cout << endl << "****";
						while (contentForMenu[i] != '\t' && contentForMenu[i] != '\0') {// Output the content until the next tab or the end of the string
							cout << contentForMenu[i];
							i++;
						}
						cout << "****" << endl;
						flag = false;  // Exit the loop once the desired tab content is printed
					}
				}
			}
			if (userInput == 7) {
				cout << "Enter file name: ";
				char* newFileName = new char[255];
				cin >> newFileName;
				delete[] fileName;
				if (newFileName != nullptr) {
					this->fileName = new char[strlen(newFileName) + 1];
					strcpy(this->fileName, newFileName);
				}
				ifstream inputFile(fileName);
				if (inputFile.is_open()) {
					string line;
					int lineCount = 0;

					while (getline(inputFile, line)) {
						lineCount++;
					}
					cout << lineCount << " records loaded!" << endl << endl;
					inputFile.close();
					load();
				}
				delete[] newFileName;
			}

			if (userInput == 1) {
				int numOfItems = list();
				if (numOfItems != 0) {
					int rowInput = 0;
					bool continueLoop = true;
					do {
						string input;
						cin.ignore(2000, '\n');
						cout << "Enter row number to display details or <ENTER> to continue:\n";
						cout << "> ";
						getline(std::cin, input);
						if (input.empty()) {
							continueLoop = false;
							cout << endl;
						}
						else {
							rowInput = std::stoi(input);
							if (rowInput < 1 || rowInput > numOfItems) {
								std::cout << "Invalid row number. Please enter a valid row number.\n";
							}
							else {
								productArray[rowInput - 1]->linear(false);
								productArray[rowInput - 1]->display(cout);
								cout << endl << endl;
								continueLoop = false;
							}
						}
					} while (continueLoop);
				}
			}
			if (userInput == 2) {
				if (productItems > sdds_max_num_items) {
					cout << "Database full!";
				}
				else {
					cout << "1- Perishable" << endl;
					cout << "2- Non-Perishable" << endl;
					cout << "-----------------" << endl;
					cout << "0- Exit" << endl;
					cout << "> ";

					int addItemChoice;
					cin >> addItemChoice;

					switch (addItemChoice) {
					case 1:
						++productItems;
						productArray[productItems - 1] = new Perishable();
						break;

					case 2:
						++productItems;
						productArray[productItems - 1] = new Item();
						break;

					case 0:
						cout << "Aborted" << endl;
						break;

					default:
						cout << "Enter correct option." << endl;
						continue;
					}

					if (addItemChoice != 0) {
						int skuInput = productArray[productItems - 1]->readSku(cin);
						int skuSearch = search(skuInput);
						if (skuSearch != -1) {
							cout << "Sku: " << skuInput << " is already in the system, try updating quantity instead." << endl << endl;
							delete productArray[productItems - 1];
							--productItems;
						}
						else {
							if (productArray[productItems - 1]) {
								productArray[productItems - 1]->read(cin);
								std::ofstream outputFile(fileName, std::ios::app); //append mode
								if (outputFile.is_open()) {
									productArray[productItems - 1]->save(outputFile);
									outputFile.close();
								}
							}
							else {
								productArray[productItems - 1]->display(cout);
								delete productArray[productItems - 1];
								--productItems;
							}
							cout << endl;
						}
					}
				}
			}

			if (userInput == 3 || userInput == 4) {
				cout << "Item description: ";
				cin.ignore(2000, '\n');
				char description[100]; 
				cin.getline(description, sizeof(description));
				int itemFound = list(description);
				if (itemFound != 0) {
					cout << "Enter SKU: ";
					int skuInput, skuSearch = -1;
					cin >> skuInput;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(2000, '\n');
					}
					else {
						skuSearch = search(skuInput);
					}
					if (skuSearch == -1) {
						cout << "SKU not found!" << endl;
					}
					else {
						if (userInput == 3) {
							cout << "Following item will be removed: " << endl;
							productArray[skuSearch]->linear(false);
							productArray[skuSearch]->display(cout);
							cout << endl;
							cout << "Are you sure?" << endl << "1- Yes!" << endl << "0- Exit" << endl << "> ";
							cin.ignore(2000, '\n');
							int addItemChoice;
							cin >> addItemChoice;
							switch (addItemChoice) {
							case 1:
								--productItems;
								remove(skuSearch);
								cout << "Item removed!" << endl;
								break;
							case 0:
								cout << "Aborted!" << endl;
								break;
							default:
								cout << "Invalid choice. Aborted!" << endl;
								break;
							}
						}
						if (userInput == 4) {
							cout << "1- Add" << endl << "2- Reduce" << endl;
							cout << "0- Exit" << endl << "> ";
							int userChoice;
							int quantityOnhand = productArray[skuSearch]->qty();
							int quantityNeeded = productArray[skuSearch]->qtyNeeded();
							int quantityDiff = quantityNeeded - quantityOnhand;
							cin >> userChoice;
							switch (userChoice) {
							case 1:
								if (quantityOnhand == quantityNeeded) {
									cout << "Quantity Needed already fulfilled!" << endl << endl;
									break;
								}
								cout << "Quantity to add: ";
								int quantityAdd;
								do {
									cin.ignore(2000, '\n');
									cin >> quantityAdd;
									if (cin.fail() || quantityAdd <= 0) {
										cin.clear();
										cin.ignore(2000, '\n');
										cout << "Enter a valid value" << endl;
									}
									else if (quantityOnhand + quantityAdd > quantityNeeded) {
										cout << "Value out of range [" << 1 << "<=val<=" << quantityDiff << "]: ";
									}
									else {
										productArray[skuSearch]->operator+=(quantityAdd);
										cout << quantityAdd << " items added!" << endl << endl;
									}
								} while (quantityAdd <= 0 || quantityOnhand + quantityAdd > quantityNeeded);
								break;

							case 2:
								cout << "Quantity to reduce: ";
								int quantityReduce;
								do {
									cin.ignore(2000, '\n');
									cin >> quantityReduce;
									if (cin.fail()|| quantityReduce <= 0) {
										cin.clear();
										cin.ignore(2000, '\n');
										cout << "Enter a valid value" << endl << endl;
									}
									else if (quantityOnhand - quantityReduce < 0) {
										cout << "Value out of range [" << 1 << "<=val<=" << quantityOnhand << "]: ";
									}
									else {
										productArray[skuSearch]->operator-=(quantityReduce);
										cout << quantityReduce << " items removed!" << endl << endl;
									}
								} while (quantityReduce <= 0 || quantityReduce > quantityOnhand);
								break;
							case 0:
								cout << "Aborted!" << endl << endl;
								break;
							default:
								cout << "Invalid choice. Aborted!" << endl << endl;
								break;
							}						
						}
					}
				}
				else {
					cout << "No matches found!" << endl;
				}
			}
			if (userInput == 5) {
				sort();
			}
			if (userInput == 6) {
				shipItem();
			}
		} while (userInput != 0);
	}

	void AidMan::save(){
		if (fileName != nullptr) {
			std::ofstream outputFile(fileName);
			if (outputFile.is_open()) {
				for (int i = 0; i < productItems; ++i) {
					productArray[i]->save(outputFile);
				}
			}
		
		}
	}

	bool AidMan::load(){
		ifstream inputFile(fileName);
		if (!(inputFile.is_open())) {
			cout << "Failed to open " << fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";
			int choice;
			cin >> choice;
			if (choice == 1) {
				ofstream newFile(fileName);
				newFile.close();
			}
			return false;
		}

			for (int i = 0; i < productItems; ++i) {
				delete productArray[i];
			}

			while (inputFile.peek() != EOF) {

				int firstChar = inputFile.peek();  // peek without consuming the character
				int skuNumber = 0;
				if (isdigit(firstChar)) {
					skuNumber = firstChar - '0';
				}

				if (skuNumber >= 1 && skuNumber < 4) {
					productArray[productItems] = new Perishable();
				}
				else {
					productArray[productItems] = new Item();
				}
				productArray[productItems]->load(inputFile);

				if (productArray[productItems]) {// Check if the loaded item is in a good state
					++productItems;
				}
				else {
					delete productArray[productItems];
				}
				inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			return true;
	}

	int AidMan::list(const char* sub_desc) {
		int numOfItem = 0;
		if (productItems == 0) {
			cout << "The list is empty!" << endl;
		}
		else {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
			if (sub_desc == nullptr) {		
				for (int i = 0; i < productItems; i++) {
					productArray[i]->linear(true);
					cout << "   " << i + 1 << " | ";
					productArray[i]->display(cout);
					cout << endl;
					numOfItem++;
				}
			}
			else {
				for (int i = 0; i < productItems; i++) {
					if (*productArray[i] == sub_desc) {
						cout << "   " << i + 1 << " | ";
						productArray[i]->linear(true);
						productArray[i]->display(cout);
						cout << endl;
						numOfItem++;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
		}

		return numOfItem;
	}

	int AidMan::search(int sku) const {
		int index = -1;

		for (int i = 0; i < productItems - 1; i++) {
			if (productArray[i] != nullptr && *productArray[i] == sku) {
				index = i;
			}
		}
		return index;
	}

	void AidMan::remove(int index) {
		delete productArray[index];
		for (int i = index; i <= productItems - 1; i++) {
			productArray[i] = productArray[i + 1];
		}
		--productItems;
		//cout << "Item removed!" << endl << endl;
	}

	void AidMan::sort() {
		for (int i = 0; i < productItems - 1; ++i) {
			for (int j = 0; j < productItems - i - 1; ++j) {
				int diffA = productArray[j]->qtyNeeded() - productArray[j]->qty();
				int diffB = productArray[j + 1]->qtyNeeded() - productArray[j + 1]->qty();
				if (diffA < diffB) {
					std::swap(productArray[j], productArray[j + 1]);
				}
			}
		}
		cout << "Sort completed!" << endl << endl;
	}

	void AidMan::shipItem() {
		ofstream shippingFile("shippingOrder.txt");
		int year, month, date;
		ut.getSystemDate(&year, &month, &date);

		shippingFile << "Shipping Order, Date: " << year << '/' << month << "/0" << date << "\n";
		shippingFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
		shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------\n";

		int shippedItemsCount = 0;

		for (int i = 0; i < productItems;) {
			int quantityOnhand = productArray[i]->qty();
			int quantityNeeded = productArray[i]->qtyNeeded();

			if (quantityOnhand == quantityNeeded) {
				productArray[i]->linear(true);
				shippingFile << "   " << shippedItemsCount + 1 << " | ";
				productArray[i]->display(shippingFile);
				shippingFile << endl;

				remove(i);
				++shippedItemsCount;
			}
			else {
				++i;   // increment i if the item was not removed
			}
		}

		shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
		shippingFile.close();
		cout << "Shipping Order for " << shippedItemsCount << " times saved!" << endl << endl;
	}
}
