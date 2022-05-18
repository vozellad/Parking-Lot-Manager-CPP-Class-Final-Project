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
#include <vector>
#include "LimList.cpp"
#include "TicketedCar.h"
using std::vector;
using std::swap;

class LotLevels
{
public:
	// Default constructor
	LotLevels();

	// Constructor
	// Sets size at initialization so it can't be changed after.
	LotLevels(const int spacesPerLevel[], const int newNumLevels);

	// Copy constructor
	LotLevels(const LotLevels& other);

	// Destructor
	~LotLevels();

	// Assignment operator
	LotLevels& operator=(const LotLevels& other);

	// ACCESSORS

	// Outputs each level by sections.
	void output() const;

	// Checks if all levels of parking lot are full.
	bool full() const;

	// Checks if all levels of parking lot are empty.
	bool empty() const;

	// Checks whether given element is in parking lot.
	bool found(const TicketedCar element) const;

	// Returns requested car object. Returns default if not found.
	TicketedCar get(const TicketedCar element) const;

	// Returns lot size of all levels.
	int getCapacity() const;

	// Output all cars in lot with the time they spend in the lot.
	// Cars still in lot need current time for calculation.
	void outputAllTimeStayed(const int minPassed) const;

	// Checks whether ID is duplicate.
	bool isDuplicate(const string searchCarID) const;

	// MUTATORS

	// Add element to lot.
	// Returns level car was added.
	// Precondition: Lot is not full. Check with full()
	int addWithLevel(const TicketedCar element);

	// Remove element from lot.
	// Returns level car was removed.
	// Precondition: Car is not absent from lot. Check with found()
	int removeWithLevel(const TicketedCar element, const int currMin);

	// Removes expired cars from lot. Returns amount removed.
	int removeExpired(int currMin);

private:
	LimList<TicketedCar>* levels;
	int numLevels;
	vector<TicketedCar> carHistory; // Holds cars that have exited the lot.
};

