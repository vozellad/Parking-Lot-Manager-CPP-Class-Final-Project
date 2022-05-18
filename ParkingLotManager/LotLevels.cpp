/*
 * Name: Demetrios Vozella
 * Final Project
 * Course: CSI218 (Fall 2021)
 * Date: 12/17/2021
 * Description: Class that uses dynamic array to
 *		represent different floors or sections of a parking lot.
 *		Builds upon on LimList class to be parking lot,
 *		and uses TicketedCar as the car for the parking lot.
 */
#pragma once
#include "LotLevels.h"
#include "TicketedCar.h"

 // Default constructor
LotLevels::LotLevels()
	: levels(NULL), numLevels(0)
{ }

// Constructor
// Sets size at initialization so it can't be changed after.
LotLevels::LotLevels(const int spacesPerLevel[], const int newNumLevels)
	: numLevels(newNumLevels)
{
	// creates parking levels
	levels = new LimList<TicketedCar>[numLevels];
	for (int i = 0; i < numLevels; i++)
		// sets level to given size
		levels[i] = LimList<TicketedCar>(spacesPerLevel[i]);
}

// Copy constructor
LotLevels::LotLevels(const LotLevels& other)
	: numLevels(other.numLevels)
{
	carHistory = other.carHistory;
	levels = new LimList<TicketedCar>[numLevels];

	for (int i = 0; i < numLevels; i++)
		levels[i] = other.levels[i];
}

// Destructor
LotLevels::~LotLevels()
{
	delete[] levels;
	levels = NULL;
	numLevels = 0;
}

// Assignment operator
LotLevels& LotLevels::operator=(const LotLevels& other)
{
	if (this != &other)
	{
		delete[] levels;
		carHistory = other.carHistory;
		numLevels = other.numLevels;
		levels = new LimList<TicketedCar>[numLevels];
		for (int i = 0; i < numLevels; i++)
			levels[i] = other.levels[i];
	}
	return *this;
}

// ACCESSORS

// Outputs each level by sections.
void LotLevels::output() const
{
	for (int i = 0; i < numLevels; i++)
	{
		// Does not show level if parking lot 
		// doesn't deal with different locations.
		// Will only iterate once if so. 
		if (numLevels == 1)
			cout << "~Capacity: " << levels[i].getCapacity() << "~\n";
		// Shows capacity for each level. 
		else
			cout << "~Level " << i + 1
				<< " (Capacity: " << levels[i].getCapacity() << ")~\n";
		if (levels[i].empty())
			cout << "Empty.\n";
		else
			levels[i].output();
	}
}

// Checks if all levels of parking lot are full.
bool LotLevels::full() const
{
	for (int i = 0; i < numLevels; i++)
		if (!levels[i].full())
			return false;
	return true;
}

// Checks if all levels of parking lot are empty.
bool LotLevels::empty() const
{
	for (int i = 0; i < numLevels; i++)
		if (!levels[i].empty())
			return false;
	return true;
}

// Checks whether given element is in parking lot.
bool LotLevels::found(const TicketedCar element) const
{
	// Depends on get() as it searches and gets a car.
	// get() will return default car if not found,
	// so must check if is still the element needed.
	return get(element) == element;
}

// Returns requested car object. Returns default if not found.
TicketedCar LotLevels::get(const TicketedCar element) const
{
	// Searches levels.
	for (int i = 0; i < numLevels; i++)
	{
		// Returns if found.
		if (levels[i].getElememt(element) == element)
			return levels[i].getElememt(element);
	}
	return TicketedCar();
}

// Returns lot size of all levels.
int LotLevels::getCapacity() const
{
	int totalCapacity = 0;
	for (int i = 0; i < numLevels; i++)
		totalCapacity += levels[i].getCapacity();
	return totalCapacity;
}

// Output all cars in lot with the time they spend in the lot.
// Cars still in lot need current time for calculation.
void LotLevels::outputAllTimeStayed(const int minPassed) const
{
	// Get both previous and current cars. Current cars gotten in loop.
	vector<TicketedCar> allCars = carHistory;
	for (int currL = 0; currL < numLevels; currL++)
		for (int i = 0; i < levels[currL].getNumStored(); i++)
			allCars.push_back(levels[currL].getByIndex(i));

	// Removes cars with virtually no parking time.
	// lambda
	auto noTimeParkedLambda = [minPassed](const TicketedCar& c)
	{ return c.getTimeParked(minPassed) < 2; };
	// auto gets iterator to be used in erase function.
	auto last = remove_if(allCars.begin(), allCars.end(), noTimeParkedLambda);
	// Removes unwanted elements moved to the back of the array.
	allCars.erase(last, allCars.end());

	// Sort cars by time stayed (descending).
	// Selection sort.
	for (int i = 0; i < allCars.size(); i++)
	{
		int currLowIndex = i;
		for (int j = i + 1; j < allCars.size(); j++)
		{
			if (allCars[currLowIndex].getTimeParked(minPassed) 
				< allCars[j].getTimeParked(minPassed))
				currLowIndex = j;
		}
		swap(allCars[i], allCars[currLowIndex]);
	}

	// Output all history of cars with their time parked.
	for (TicketedCar car : allCars)
	{
		cout << "Car ID: " << car.getCarID() << " - Time Parked: "
			<< car.getTimeParked(minPassed) << " minutes.\n";
	}
	if (allCars.size() == 0)
		cout << "No cars to show.\n";
	cout << "\n";
}

// Checks whether ID is duplicate.
bool LotLevels::isDuplicate(const string searchCarID) const
{
	return get(TicketedCar(searchCarID)) != TicketedCar();
}

// MUTATORS

// Add element to list.
// Returns level car was added.
// Precondition: Lot is not full. Check with full()
int LotLevels::addWithLevel(const TicketedCar element)
{
	int i;
	for (i = 0; i < numLevels; i++)
	{
		if (!levels[i].full())
		{
			levels[i].add(element);
			break;
		}
	}
	return i + 1;
}

// Remove element from lot.
// Returns level car was removed.
// Precondition: Car is not absent from lot. Check with found()
int LotLevels::removeWithLevel(const TicketedCar element, const int currMin)
{
	int i;
	for (i = 0; i < numLevels; i++)
	{
		// Needs to find which level the car is in before removing it. 
		if (levels[i].found(element))
		{
			TicketedCar deleteCar = levels[i].getElememt(element);
			deleteCar.setEndParkTime(currMin);
			// Gets car with all info to store in history.
			carHistory.push_back(deleteCar);

			levels[i].remove(deleteCar);
			break;
		}
	}
	return i + 1;
}

// Removes expired cars from lot. Returns amount removed.
int LotLevels::removeExpired(int currMin)
{
	// Increment per car removal.
	int numRemoved = 0;
	// Iterates lot levels.
	for (int currL = 0; currL < numLevels; currL++)
	{
		// Inner iterates cars in current level.
		for (int i = 0; i < levels[currL].getNumStored(); i++)
		{
			// Gets current car object from container to analyze.
			// Remove if ticket expired. Also records car in history.
			TicketedCar deleteCar = levels[currL].getByIndex(i);
			if (deleteCar.ticketExpired(currMin))
			{
				// Store car in history.
				deleteCar.setEndParkTime(currMin);
				carHistory.push_back(deleteCar);

				levels[currL].remove(deleteCar);
				numRemoved++;
			}
		}
	}

	return numRemoved;
}