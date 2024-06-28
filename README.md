# C++ Project:Aid Management System

## Introduction
This project implements an Aid Management System in C++. It allows users to manage items, including listing, adding, removing, updating quantities, sorting, and shipping items.

## Files
- **main.cpp**: Contains the main function to run the program.
- **AidMan.cpp/h**: Implements the AidMan class, which manages the aid items.
- **Date.cpp/h**: Implements the Date class for handling dates.
- **Menu.cpp/h**: Implements the Menu class for displaying menus.
- **Status.cpp/h**: Implements the Status class for managing status descriptions.
- **Utils.cpp/h**: Implements utility functions for system date retrieval and other helper functions.
- **Item.cpp/h**: Defines and implements the Item class, handling the properties and behaviors of generic items.
- **Perishable.cpp/h**: Defines and implements the Perishable class, handling items with expiration dates.
- **iProduct.cpp/h**: Defines the iProduct interface, which Item and Perishable classes implement.

## Usage
1. Compile the source files using a C++ compiler.
2. Run the executable.
3. Follow the on-screen prompts to interact with the system.

## Features
- **Menu Interface**: Provides a user-friendly menu for navigating the system.
- **Item Management**: Allows users to list, add, remove, and update quantities of items.
- **Sorting**: Enables sorting of items based on quantity needed.
- **Shipping**: Generates a shipping order for items with fulfilled quantities.
- **System Date**: Utilizes utility functions for retrieving the system date.
- **Perishable Items**: Manages perishable items with handling instructions and expiry dates.
- **Persistent Storage**: Saves and loads items from files for persistent storage.

## Dependencies
- **Utils.h**: Contains utility functions for system date retrieval and other helper functions.

## Credits
Ziyang Wang: Implemented the project.
