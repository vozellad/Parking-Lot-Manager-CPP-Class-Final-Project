/*
 * Name: Demetrios Vozella
 * Final Project
 * Course: CSI218 (Fall 2021)
 * Date: 12/17/2021
 * Description: LimList (Size Limited Container) is a template class
 *		meant to be used as a list with a built in max size decided only
 *		at initialization.
 */

#pragma once
#include "TicketedCar.h"
template<class T>
class LimList // Size Limited List
{
public:
	// Default constructor
	LimList();

	// Constructor
	// Takes max size.
	LimList(const int newCapacity);

	// Copy constructor
	LimList(const LimList<T>& other);

	// Destructor
	~LimList();

	// Assignment operator
	LimList& operator=(const LimList<T>& other);

	// ACCESSORS

	// Outputs each element on new line. 
	void output() const;

	// Checks whether list size limit reached.
	bool full() const;

	// Checks whether no element in list. 
	bool empty() const;

	// Checks whether given element is in list.
	bool found(const T element) const;

	// Returns requested element.
	T getElememt(const T element) const;

	// Returns element by index. Returns default if not found.
	T getByIndex(const int index) const;

	// Returns list size.
	int getCapacity() const;

	// Returns number of elements.
	int getNumStored() const;

	// MUTATORS

	// Add element to list.
	// Precondition: List is not full. Check with full()
	void add(const T element);

	// Remove element from list.
	// Precondition: Element is not absent from list. Check with found()
	void remove(const T element);

private:
	// Linked list to keep track of elements.
	struct Node
	{
		T info;
		Node* linkP;
	};
	Node* firstP;
	Node* lastP;
	int capacity;  // Max size given my program.
	int numStored; // Current number of elements in list.

	// Clear list of elements.
	void clear();

	// Append elements to list.
	void append(const LimList<T>& other);
};

