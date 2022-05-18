/*
 * Name: Demetrios Vozella
 * Final Project
 * Course: CSI218 (Fall 2021)
 * Date: 12/17/2021
 * Description: TicketedCar is critical class. Holds car info (ID and ticket info).
 *		An object represents a car with a ticket.
 */

#pragma once
#include <iostream>
#include "TicketedCar.h"

 // Default constructor
TicketedCar::TicketedCar()
	: carID(""), ticketPrice(0),
	ticketMinutes(0), startParkTime(0), endParkTime(0)
{ }

// Constructor for searching by ID
TicketedCar::TicketedCar(string newCarID)
	: carID(newCarID), ticketPrice(0),
	ticketMinutes(0), startParkTime(0), endParkTime(0)
{ }

// Constructor
// Takes car info.
TicketedCar::TicketedCar(const string newCarID, const int newTickerPrice,
	const int newTicketMinutes, const int newStartParkTime)
	: carID(newCarID), ticketPrice(newTickerPrice),
	ticketMinutes(newTicketMinutes),
	startParkTime(newStartParkTime), endParkTime(0)
{ }

// Copy constructor
TicketedCar::TicketedCar(const TicketedCar& other)
	: carID(other.carID), ticketPrice(other.ticketPrice),
	ticketMinutes(other.ticketMinutes),
	startParkTime(other.startParkTime), endParkTime(other.endParkTime)
{ }

// Assignment operator
TicketedCar& TicketedCar::operator=(const TicketedCar& other)
{
	if (this != &other)
	{
		carID = other.carID;
		ticketPrice = other.ticketPrice;
		ticketMinutes = other.ticketMinutes;
		startParkTime = other.startParkTime;
		endParkTime = other.endParkTime;
	}
	return *this;
}

// Equality operator
// for carID
bool TicketedCar::operator==(const TicketedCar& other) const
{
	return carID == other.carID;
}

// Unequality operator
// for carID
bool TicketedCar::operator!=(const TicketedCar& other) const
{
	return !(*this == other);
}

// Insertion operator
// for outputing car info
ostream& operator<<(ostream& stream, const TicketedCar& outCar)
{
	stream << "Car ID: " << outCar.carID
		<< ", Ticket: (Price: " << outCar.ticketPrice
		<< ", Minutes: " << outCar.ticketMinutes
		<< ", Parked since: " << outCar.startParkTime << ")";
	return stream;
}

// ACCESSORS


string TicketedCar::getCarID() const
{
	return carID;
}

int TicketedCar::getTicketPrice() const
{
	return ticketPrice;
}

int TicketedCar::getTicketMinutes() const
{
	return ticketMinutes;
}

int TicketedCar::getStartParkTime() const
{
	return startParkTime;
}

// Returns whether ticket expired.
// (current time has hit or passed expiration time)
// Compares minutes car has with time passed in minutes.
bool TicketedCar::ticketExpired(const int currMin) const
{
	return (ticketMinutes + startParkTime) <= currMin;
}

// Knows if car in lot if no end park time has been assigned yet.
// Car can't leave lot at 0 minutes.
bool TicketedCar::inLot() const
{
	return endParkTime == 0;
}

// Parameter used for when car is in lot.
int TicketedCar::getTimeParked(const int minPassed) const
{
	if (inLot()) // return current time in lot.
		return minPassed - startParkTime;
	else // not in lot, return time spent in lot.
		return endParkTime - startParkTime;
}

void TicketedCar::setCarID(string const newCarID)
{
	carID = newCarID;
}

void TicketedCar::setTicketPrice(int const newTicketPrice)
{
	ticketPrice = newTicketPrice;
}

void TicketedCar::setTicketMinutes(int const newTicketMinutes)
{
	ticketMinutes = newTicketMinutes;
}

void TicketedCar::setEndParkTime(int const currTime)
{
	endParkTime = currTime;
}