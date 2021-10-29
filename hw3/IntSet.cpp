// NAME: Gary Tou
// FILE: IntSet.cpp
// DESCRIPTION: Implementation of the IntSet class.

#include <iostream>
#include <cstdlib>
using namespace std;

#include "IntSet.h"

// Constructor: the argument represents the largest possible integer the set
// can have in its domain.  If the argument is 5, then the domain of the set
// is the integers 1-5.  The set that is being constructed however is empty.
IntSet::IntSet(int sizeArg)
{
	this->size = sizeArg;

	// Determine size of array needed
	int numBitstrings = sizeArg / this->INT_BIT_LENGTH;
	if (sizeArg % INT_BIT_LENGTH != 0)
	{
		numBitstrings++;
	}

	// Create bitstring array and save it's size for easy access
	bits = new bitstring[numBitstrings];
	bitsSize = numBitstrings;
}

// Copy constructor
IntSet::IntSet(const IntSet &src)
{
	this->bits = new bitstring[src.bitsSize];
	*this->bits = *src.bits;
	this->bitsSize = src.bitsSize;
	this->size = src.size;
}

// Destructor
IntSet::~IntSet()
{
	delete[] this->bits;
	this->bits = NULL;
}

// Adds the specified integer to the set if not already an element.
void IntSet::addElement(int num)
{
	// Get index of respective bitstring and shift amount
	const int arrayIndex = this->bitsArrayIndex(num);
	const int bitstringIndex = this->bitsBitstringIndex(num);
	bitstring newElement = 1 << bitstringIndex;
	// bitwise 'OR' to add the new element to the existing set
	bits[arrayIndex] = bits[arrayIndex] | newElement;
}

// Removes the specified integer if it is in the set.  Note that nothing happens
// if the element is in the domain but not in the set.
void IntSet::removeElement(int num)
{
	// If element is not in the set, do nothing (return)
	if (!this->isElement(num))
	{
		return;
	}

	// Get index of respective bitstring and shift amount
	const int arrayIndex = this->bitsArrayIndex(num);
	const int bitstringIndex = this->bitsBitstringIndex(num);

	// Create mask
	bitstring mask = 0;
	// Add powers of 10 to fill in '1's until reaching max bit length (while
	// skipping over the element we want to remove; that will remain a zero).
	//
	// === Example ===
	// If we are trying to remove the number 3, the mask will look like:
	// ...0100    (left padded with '0's until `INT_BIT_LENGTH` is reached)
	for (int i = 0; i < this->INT_BIT_LENGTH; i++)
	{
		if (i != bitstringIndex)
		{
			mask += (1 << i);
		}
	}

	// use bitwise 'AND' to apply the mask
	bits[arrayIndex] = bits[arrayIndex] & mask;
}

// Returns true if the specified integer is in the set.  Returns false otherwise.
bool IntSet::isElement(int num) const
{
	// Get location of element
	const int arrayIndex = this->bitsArrayIndex(num);
	const int bitstringIndex = this->bitsBitstringIndex(num);

	// Get bitstring which element is located in
	bitstring bstring = bits[arrayIndex];
	// Create a mask to isolate the element
	bitstring mask = 1 << bitstringIndex;

	// Deteremine if the element exists using the mask
	bool exists = (bstring & mask) > 0;
	return exists;
}

// Displays the set to the screen in the format: {1, 3, 4}
void IntSet::display() const
{
	// Tracks whether first element has been found. Used as condition for printing
	// delimiters.
	bool foundFirstElement = false;

	// Print opening bracket
	cout << "{";

	// Loop though all possible elements of the set (the domain)
	for (int i = 1; i <= this->size; i++)
	{
		// Check if the integer is within the set
		if (this->isElement(i))
		{
			// Prefix with delimiter, if necessary
			if (foundFirstElement)
			{
				// Print some formatting (delimiter)
				cout << this->DISPLAY_DELIMITER;
			}
			else
			{
				// First element has now been found
				foundFirstElement = true;
				// There will be no delimiter prefixed to this element since it is the
				// first within the set.
			}

			// Print the element
			cout << i;
		}
	}

	if (!foundFirstElement)
	{
		// This means there are no elements in the set.
		// Print a space between the opening and closing braces for better formatting
		cout << " ";
	}

	// Add closing bracket
	cout << "}";
}

// Returns the number of elements in the set.
int IntSet::numElements() const
{
	// Set up a counter for the number of elements in the set
	int counter = 0;

	// Loop through all possible elements (the domain)
	for (int i = 1; i < this->size; i++)
	{
		// Add '1' to the counter if the element exists in the set
		if (this->isElement(i))
		{
			counter++;
		}
	}

	return counter;
}

// Returns a set that is the union of the invoking set and the set operand.
IntSet IntSet::unions(const IntSet &operand) const
{
	// Finds the largest and smallest set (if equal, invoked set defaults to
	// largest)
	bool invokedIsLarger = this->size >= operand.size;
	IntSet largerSet = invokedIsLarger ? *this : operand;
	IntSet smallerSet = invokedIsLarger ? operand : *this;

	// Create new IntSet to store the results (union of invoked and operand sets)
	IntSet results(largerSet.size);

	// Loop through all bitstrings in the IntSet (loop through all elements of
	// the array)
	for (int i = 0; i < largerSet.bitsSize; i++)
	{
		// If this is out of range of the smaller set, just copy the larger set's
		// bitstring to the results. This is the set identity law (A ∪ Ø = A).
		if (i >= smallerSet.bitsSize)
		{
			results.bits[i] = largerSet.bits[i];
		}
		else
		{
			// Use bitwise 'OR' to union the bitstrings
			results.bits[i] = largerSet.bits[i] | smallerSet.bits[i];
		}
	}

	return results;
}

// Returns a set that is the intersection of the invoking set and the set operand.
IntSet IntSet::intersect(const IntSet &operand) const
{
	// Finds the largest and smallest set (if equal, invoked set defaults to
	// largest)
	bool invokedIsLarger = this->size >= operand.size;
	IntSet largerSet = invokedIsLarger ? *this : operand;
	IntSet smallerSet = invokedIsLarger ? operand : *this;

	// Create new IntSet to store the results (intersection of invoked and operand
	// sets). Using the larger size here because the larger numbers are within the
	// overall domain.
	IntSet results(largerSet.size);

	// Loop through all bitstrings in the smaller IntSet. We only need the smaller
	// set because the elements outside of the domain of the smaller set can not
	// be a result of the intersection.
	for (int i = 0; i < largerSet.bitsSize; i++)
	{
		// Use bitwise `AND` to intersect the bitstrings
		results.bits[i] = largerSet.bits[i] & smallerSet.bits[i];
	}

	return results;
}

// Returns a set that is the difference between the invoking set (call it A)
// and the set operand (call it B).  In other words, compute A-B.
IntSet IntSet::difference(const IntSet &operand) const
{
	// Create new IntSet to store the results. We are using the size of the invoked
	// set because that is what the domain of results will be.
	IntSet results(this->size);

	// Loop through all bitstrings in the invoked IntSet. We are only looping
	// through the domain of the invoked set because elements outside of that
	// domain can not be within the resulting difference.
	for (int i = 0; i < this->bitsSize; i++)
	{
		if (i >= operand.bitsSize)
		{
			// We have exceded the domain of operand set, therefore, everything beyond
			// this can just be copied over from the invoked set.
			results.bits[i] = this->bits[i];
			continue;
		}

		// Since we can only remove elements which already exist in the set, we will
		// start by computing the intersection of the two sets.
		// Note: Because this is simpily intersecting two bitstrings, we will use
		// the bitwise 'AND', instead of 'IntSet::intersect'.
		bitstring intersection = this->bits[i] & this->bits[i];

		// The algebraic subtraction of the invoked bitstring and the intersection
		// (of the invoked and operand sets) will result in the difference.
		results.bits[i] = this->bits[i] - intersection;
	}

	return results;
}

// Returns the complement of the set.
IntSet IntSet::complement() const
{
	// Create new IntSet to store the results
	IntSet results(this->size);

	// Loop through all possible elements in the set (the domain)
	for (int i = 1; i < this->size; i++)
	{
		// If the current element IS NOT an element of the current set, add it as an
		// element of the resulting set
		if (!this->isElement(i))
		{
			results.addElement(i);
		}
	}

	return results;
}

// Returns true if the invoking set is equal to the set operand.
bool IntSet::isEqual(const IntSet &operand) const
{
	// Finds the largest and smallest set (if equal, invoked set defaults to
	// largest)
	bool invokedIsLarger = this->size >= operand.size;
	IntSet largerSet = invokedIsLarger ? *this : operand;
	IntSet smallerSet = invokedIsLarger ? operand : *this;

	// Loop through all bitstrings in the IntSet (loop through all elements of
	// the array)
	for (int i = 0; i < largerSet.bitsSize; i++)
	{
		// If the larger set has elements outside of the domain of the smaller set,
		// the two sets can not be equal. So, we return false.
		if ((i >= smallerSet.bitsSize) && (largerSet.bits[i] != 0))
		{
			return false;
		}
		else
		{
			// The bitwise 'XOR' allows us to determine if there is a difference in
			// the bits. Any number greater than (or not equal to) '0' signifies at
			// least one bit difference. Therefore, we would return false.
			if ((largerSet.bits[i] ^ smallerSet.bits[i]) != 0)
			{
				return false;
			}
		}
	}

	// No differing bits were found, therefore the sets are equal!
	return true;
}

// ========== PRIVATE ==========

// Returns the array element index of which an element is in.
// Assumes highest elements in index 0, and lowest elements in index (size - 1)
// Zero-indexed
int IntSet::bitsArrayIndex(const int element) const
{
	return (bitsSize - 1) - ((element - 1) / INT_BIT_LENGTH);
}

// Returns the element index in the array which an element is in.
// Assumes lowest element is on the right.
// Zero-indexed
int IntSet::bitsBitstringIndex(const int element) const
{
	return ((element - 1) % INT_BIT_LENGTH);
}