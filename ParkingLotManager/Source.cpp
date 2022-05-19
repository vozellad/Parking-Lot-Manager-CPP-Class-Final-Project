/*
 * Name: Demetrios Vozella
 * Final Project
 * Course: CSI218 (Fall 2021)
 * Date: 12/17/2021
 * Description: Keeps track of a parking lot with multiple levels and a
 *		queue of cars waiting for available space. Has ticket types
 *		with a price and a time amount. Main program simulates 
 *		a car attendant who adds and removes cars and can see current lot,
 *		queue, and record of time stayed all cars. Commands simulating that
 *		are read from file.
 *
 *		Hierarchy of program is TicketedCar -> LimList -> LotLevels -> main
 *		Although a TicketedCar object may be accessed from anywhere.
 *		TicketedCar is critical class. Holds car info (ID and ticket info).
 *			An object represents a car with a ticket.
 *		LimList (Size Limited Container) is a template class
 *			meant to be used as a list with a built in max size decided only
 *			at initialization.
 *			Also searches for object which triggers equality operator in
 *			TicketedCar.
 *		LotLevels (Parking Lot Levels/Floors/Sections/Locations)
 *			has dynamic array and expands functionality of LimList using
 *			TicketedCar as the data type. Uses array to represent multiple
 *			levels of parking lot.
 *			Has a vector to store history of cars.
 *			(Cars that have came and gone.)
 *			Can output all cars with the time spent in the lot.
 *			Sorts cars by most time spent before outputing
 *			with the help of algorithm functions.
 * 
 * Requirements: 
 *		Dynamic array:		levels in LimList.
 *		Template class:		LimList.
 *		Searching:		getElement() in LimList using equality operator in TicketedCar.
 *		STL Container:		carHistory as vector in LotLevels.
 *		Sorting:		outputAllTimeStayed() using selection sort in LotLevels.
 *		Algorithm function: 	remove_if() in LotLevels.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <Windows.h>
#include "TicketedCar.h"
#include "LotLevels.h"

using namespace std;
int main()
{
	// Creates a parking Lot with multiple levels 
	// with certain amount of spaces per level. 
	const int maxLevels = 2;
	const int spaces[maxLevels] = { 8, 5 };
	LotLevels parkingLot(spaces, maxLevels);
	// Takes what level had a car added to or removed from to output it. 
	int levelModified;
	// Lot does not track location of cars.
	// It only handles what cars are parked and limits the amount per level.

	// Queue of cars waiting for available space in lot.
	queue<string> carsQ;
	// Cast removing compiler warning of possible lost data. 
	srand(static_cast<unsigned int>(time(NULL)));

	cout << "Logged in as Parking Attendant.\n\n";

	// Display ticket info.
	const int tAmt = 3;
	const int tickets[tAmt][2] = { { 10, 15 }, {20, 30}, {30, 60} };
	for (int i = 0; i < tAmt; i++)
		cout << "Ticket " << i + 1 << ": $" << tickets[i][0]
			<< " - " << tickets[i][1] << " minutes\n";
	cout << "\n";


	// Takes information from file.

	// Commands are meant to be entered by person, 
	// but this will be simulate with lines from file.

	// Will store lines from file.
	// All inputs are simulated instead.
	string line;
	queue<string> fileLines;
	ifstream file;
	// file.txt and file2.txt available for testing.
	file.open("file.txt");
	// Exit program and show error if failed to open file.
	if (!file.is_open())
	{
		cerr << "Exception opening/reading file\n";
		exit(EXIT_FAILURE);
	}
	while (getline(file, line))
	{
		// Skips new lines to allow them in files
		if (line != "")
			fileLines.push(line);
	}
	file.close();
	int minPassed = -1;

	// while (true)
	while (!fileLines.empty())
	{
		// Handling tickets.
		// Simulation code. 1 second represents 1 minute.
		Sleep(1000); // Comment out to speed up commands.
		minPassed++;
		int numRemoved = parkingLot.removeExpired(minPassed);
		if (numRemoved > 0)
		{
			cout << numRemoved << " removed due to expired tickets."
				<< "\nPassed minutes: " << minPassed << "\n\n";
		}

		string command = "", carID = "";
		int ticSel; // Ticket Selected.

		cout << "Enter command (\"help\" to lists commands): ";
		// cin >> command;
		command = fileLines.front();
		fileLines.pop();
		cout << command << "\n";

		if (command == "help")
		{
			cout << "add\t(Adds car to lot.)\n"
				<< "remove\t(Removes car from lot.)\n"
				<< "parked\t(Shows all parked cars in lot.)\n"
				<< "queue\t(Shows all cars waiting for available space in lot.)\n"
				<< "stayed\t(Shows time parked of all cars.)\n\n";
		}
		else if (command == "add")
		{
			cout << "Car ID: ";
			carID = fileLines.front();
			fileLines.pop();
			cout << carID << "\n";

			// Checks whether ID is duplicate.
			if (parkingLot.isDuplicate(carID))
			{
				cout << "Car ID is taken\n\n";
				continue;
			}

			cout << "Ticket type (1, 2, 3): ";
			// cin >> ticSel;
			try
			{
				ticSel = stoi(fileLines.front());
			}
			// Unhandled exception. String could not be converted to int.
			catch (...)
			{
				// Program ends because it's currently a simulation 
				// that can't re-prompt for user input.
				cout << "\n\n\nTicket type must be a number. Ending program.\n";
				system("pause");
				return -1;
			}
			fileLines.pop();
			cout << ticSel << "\n";
			ticSel--;

			// Checks if full before adding.
			// If full, adds car to queue.
			if (parkingLot.full())
			{
				carsQ.push(carID);
				cout << "Lot is full. Added car to queue.\n";
			}
			else
			{
				// Adds car to lot and gets level in which it was added to display it.
				levelModified = parkingLot.addWithLevel(TicketedCar(carID,
					tickets[ticSel][0], tickets[ticSel][1], minPassed));
				cout << "Car added to level " << levelModified << ".\n";
			}
			cout << "\n";
		}
		else if (command == "remove")
		{
			// Checks if empty before removing car.
			if (parkingLot.empty())
			{
				cout << "No car to remove.\n\n";
				continue;
			}

			// Gets car to remove by ID.
			cout << "Car ID: ";
			// cin >> carID;
			carID = fileLines.front();
			fileLines.pop();
			cout << carID << "\n";

			// Checks if car is in lot. Exits scope if not.
			if (!parkingLot.found(carID))
			{
				cout << "Car not found.\n\n";
				continue;
			}

			// Removes car from lot and gets level it was removed from to output it.
			levelModified = parkingLot.removeWithLevel(TicketedCar(carID), minPassed);
			cout << "Car removed from level " << levelModified << ".\n";

			// Now that lot has open space, 
			// add car to lot from queue if queue not empty. 
			if (!carsQ.empty())
			{
				cout << "Accepting car from queue.\n";
				carID = carsQ.front();
				cout << "Ticket type (1, 2, 3): ";
				// cin >> ticSel;
				try
				{
					ticSel = stoi(fileLines.front());
				}
				// Unhandled exception. String could not be converted to int.
				catch (...)
				{
					// Program ends because it's currently a simulation 
					// that can't re-prompt for user input.
					cout << "\n\n\nTicket type must be a number. Ending program.\n";
					system("pause");
					return -1;
				}
				fileLines.pop();
				cout << ticSel << "\n";
				ticSel--;
				levelModified = parkingLot.addWithLevel(TicketedCar(carID,
					tickets[ticSel][0], tickets[ticSel][1], minPassed));
				carsQ.pop();

				cout << "Added car from queue to level " << levelModified << ".\n";
			}
			cout << "\n";
		}
		else if (command == "parked")
		{ // Outputs all parked cars.
			if (parkingLot.empty())
				cout << "Parking Lot empty.\n";
			else
				parkingLot.output();
			cout << "\n";
		}
		else if (command == "queue")
		{ // Outputs all cars in queue.
			if (carsQ.empty())
			{
				cout << "No cars in queue.\n\n";
				continue;
			}
			// Must use copy of queue to traverse without losing elements.
			queue<string> outQ = carsQ;
			while (!outQ.empty())
			{
				cout << "Car ID: " << outQ.front() << "\n";
				outQ.pop();
			}
			cout << "\n";
		}
		else if (command == "stayed")
		{
			parkingLot.outputAllTimeStayed(minPassed);
		}
		else
		{ // Default case.
			cout << "Command not recognized.\n\n";
		}
	}


	cout << "\nSimulation complete.\n";
	system("pause");
	return 0;
}
