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
#include "LimList.h"

 // Default constructor
template<class T>
LimList<T>::LimList()
	: firstP(NULL), lastP(NULL), capacity(1), numStored(0)
{ }

// Constructor
// Takes max size.
template<class T>
LimList<T>::LimList(const int newCapacity)
	: firstP(NULL), lastP(NULL), capacity(newCapacity), numStored(0)
{ }

// Copy constructor
template<class T>
LimList<T>::LimList(
	const LimList<T>& other)
	: firstP(NULL), lastP(NULL), capacity(other.capacity), numStored(other.numStored)
{
	append(other);
}

// Destructor
template<class T>
LimList<T>::~LimList()
{
	clear();
}

// Assignment operator
template<class T>
LimList<T>& LimList<T>::operator=(
	const LimList<T>& other)
{
	if (this != &other)
	{
		capacity = other.capacity;
		numStored = other.numStored;

		clear();
		append(other);
	}

	return *this;
}

// ACCESSORS

// Outputs each element on new line. 
template<class T>
void LimList<T>::output() const
{
	// Iterates using both nodes and amount stored.
	Node* traverseP = firstP;
	int i = 0;
	while ((traverseP != NULL) && (i < numStored))
	{
		cout << traverseP->info << "\n";

		traverseP = traverseP->linkP;
		i++;
	}
}

// Checks whether list size limit reached.
template<class T>
bool LimList<T>::full() const
{
	return numStored == capacity;
}

// Checks whether no element in list. 
template<class T>
bool LimList<T>::empty() const
{
	return numStored == 0;
}

// Checks whether given element is in list.
template<class T>
bool LimList<T>::found(const T element) const
{
	// Depends on get() as it searches and gets an element.
	// get() will return default value of T if not found, 
	// so must check if is still the element needed.
	return getElememt(element) == element;
}

// Returns requested element. Returns default if not found. 
template<class T>
T LimList<T>::getElememt(const T element) const
{
	// Searches list.
	for (Node* traverseP = firstP;
		traverseP != NULL;
		traverseP = traverseP->linkP)
	{
		// Returns if found.
		if (traverseP->info == element)
			return traverseP->info;
	}
	return T();
}

// Returns element by index. Returns default if index not within range.
template<class T>
T LimList<T>::getByIndex(const int index) const
{
	if (index < 0 || index > numStored - 1)
		return T();

	Node* traverseP = firstP;
	for (int i = 0; i < index; i++)
		traverseP = traverseP->linkP;
	return traverseP->info;
}

// Returns list size.
template<class T>
int LimList<T>::getCapacity() const
{
	return capacity;
}

// Returns number of elements.
template<class T>
int LimList<T>::getNumStored() const
{
	return numStored;
}

// MUTATORS

// Add element to list.
// Precondition: List is not full. Check with full()
template<class T>
void LimList<T>::add(const T element)
{
	// Make new node with given info to add to list.
	Node* newCarNode = new Node;
	newCarNode->linkP = NULL;
	newCarNode->info = element;

	// Must check if list is empty to know whether to 
	// make element beginning of list or add to end of list.
	if (firstP == NULL)
		firstP = newCarNode;
	else
		lastP->linkP = newCarNode;
	lastP = newCarNode;

	numStored++;
}

// Remove element from list.
// Precondition: Element is not absent from list. Check with found()
template<class T>
void LimList<T>::remove(const T element)
{
	// Action needed depends on number of elements 
	// and whether given element is found in middle or edge of list. 
	// numStored gets decremented as well when Node is removed.

	if (numStored == 1) // Just clear since nothing to save. 
	{
		clear();
		numStored--;
	}
	else if (numStored == 2) // Handles two Nodes. 
	{
		if (firstP->info == element)
		{ // If element found in first node.
			Node* deleteP = firstP;
			firstP = firstP->linkP;
			delete deleteP;
		}
		else if (firstP->linkP->info == element)
		{ // If element found in second Node.
			Node* deleteP = lastP;
			lastP = firstP;
			delete deleteP;
			firstP->linkP = NULL;
		}
		numStored--;
	}
	else if (numStored > 2)
	{
		// Need 3 Nodes to handle links of Nodes. 
		// Can't only delete Node when found.
		Node* beforeP = firstP;
		Node* middleP = beforeP->linkP;
		Node* afterP = middleP->linkP;
		if (beforeP->info == element)
		{ // If found in first Node.
			// Second Node becomes first Node. 
			// Previous first Node is removed. 
			firstP = middleP;
			delete beforeP;
			numStored--;
			return;
		}
		// Like a do-while loop with the exit condition in the middle.
		while (true)
		{
			if (middleP->info == element)
			{ // If element found in middle.
				// Node before middle gets linked to Node after middle.
				// Middle gets removed.
				beforeP->linkP = afterP;
				delete middleP;
				numStored--;
				return;
			}

			if (afterP->linkP == NULL)
				// If element not found at every Node but the last
				// go to next if statement.
				break;

			beforeP = beforeP->linkP;
			middleP = middleP->linkP;
			afterP = afterP->linkP;
		}
		if (afterP->info == element)
		{ // If element found at last Node.
			// Second-last Node becomes last.
			// Previous last gets removed. 
			middleP->linkP = NULL;
			lastP = middleP;
			delete afterP;
		}
		numStored--;
	}
}


// Clear list of elements.
template<class T>
void LimList<T>::clear()
{
	while (firstP != NULL)
	{
		Node* deleteP = firstP;
		firstP = firstP->linkP;
		delete deleteP;
	}
	lastP = NULL;
}

// Append elements to list.
template<class T>
void LimList<T>::append(const LimList<T>& other)
{
	for (Node* traverseP = other.firstP;
		traverseP != NULL;
		traverseP = traverseP->linkP)
	{
		add(traverseP->info);
	}
}