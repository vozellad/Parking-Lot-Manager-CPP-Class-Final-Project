/*
 * Name: Demetrios Vozella
 * Final Project // TODO: edit this line on all
 * Course: CSI218 (Fall 2021)
 * Date: 12/17/2021
 * Description: Class represents a car TODO
 */

#pragma once
#include <iostream>
using std::cout;
using std::string;
using std::ostream;

class TicketedCar
{
public:
	// Default constructor
	TicketedCar();

	// Constructor for searching by ID
	TicketedCar(string newCarID);

	// Constructor
	// Takes car info.
	TicketedCar(const string newCarID, const int newTickerPrice,
		const int newTicketMinutes, const int newStartParkTime);

	// Copy constructor
	TicketedCar(const TicketedCar& other);

	// Nothing to deallocate for Destructor

	// Assignment operator
	TicketedCar& operator=(const TicketedCar& other);

	// Equality operator
	// for carID
	bool operator==(const TicketedCar& other) const;

	// Unequality operator
	// for carID
	bool operator!=(const TicketedCar& other) const;

	// Insertion operator
	// for outputing car info
	friend ostream& operator<<(ostream& stream, const TicketedCar& other);

	// ACCESSORS

	string getCarID() const;

	int getTicketPrice() const;

	int getTicketMinutes() const;

	int getStartParkTime() const;

	// Returns whether ticket expired.
	// Compares minutes car has with time passed in minutes.
	bool ticketExpired(const int currMin) const; // TODO: check in all files all that needs to be should be const

	// Knows if car in lot if no end park time has been assigned yet.
	// Car can't leave lot at 0 minutes.
	bool inLot() const;

	// Parameter used for when car is in lot.
	int getTimeParked(const int minPassed) const;

	// MUTATORS

	void setCarID(string const newCarID);

	void setTicketPrice(int const newTicketPrice);

	void setTicketMinutes(int const newTicketMinutes);

	void setEndParkTime(int const currMin);

private:
	string carID;

	int ticketPrice;
	int ticketMinutes;

	int startParkTime;
	int endParkTime;

};