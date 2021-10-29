// NAME: 
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
}

// Copy constructor
IntSet::IntSet(const IntSet& src)
{
}

// Destructor
IntSet::~IntSet()
{
}

// Adds the specified integer to the set if not already an element.
void IntSet::addElement(int num)
{
}

// Removes the specified integer if it is in the set.  Note that nothing happens
// if the element is in the domain but not in the set.
void IntSet::removeElement(int num)
{
}

// Returns true if the specified integer is in the set.  Returns false otherwise.
bool IntSet::isElement(int num) const
{
}

// Displays the set to the screen in the format: {1, 3, 4}
void IntSet::display() const
{
}

// Returns the number of elements in the set.
int IntSet::numElements() const
{
}

// Returns a set that is the union of the invoking set and the set operand.
IntSet IntSet::unions(const IntSet& operand) const
{
}

// Returns a set that is the intersection of the invoking set and the set operand.
IntSet IntSet::intersect(const IntSet& operand) const
{
}

// Returns a set that is the difference between the invoking set (call it A)
// and the set operand (call it B).  In other words, compute A-B.
IntSet IntSet::difference(const IntSet& operand) const
{
}

// Returns the complement of the set.
IntSet IntSet::complement() const
{
}

// Returns true if the invoking set is equal to the set operand.
bool IntSet::isEqual(const IntSet& operand) const
{
}
