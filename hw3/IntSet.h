// NAME: 
// FILE: IntSet.h
// DESCRIPTION: Definition of the IntSet class.

#ifndef INTSET_H
#define INTSET_H

// Represents a set of integers from 1 to size.
//
class IntSet {

public:
  // Constructor: the argument represents the largest possible integer the set
  // can have in its domain.  If the argument is 5, then the domain of the set
  // is the integers 1-5.  The set that is being constructed however is empty.
  IntSet(int size);

  // Copy constructor
  IntSet(const IntSet& src);

  // Destructor
  ~IntSet();

  // Adds the specified integer to the set if not already an element.  
  void addElement(int num);

  // Removes the specified integer if it is in the set.  Note that nothing happens
  // if the element is in the domain but not in the set.
  void removeElement(int num);

  // Returns true if the specified integer is in the set.  Returns false otherwise.
  bool isElement(int num) const;

  // Displays the set to the screen in the format: {1, 3, 4}
  void display() const;

  // Returns the number of elements in the set.
  int numElements() const;

  // Returns a set that is the union of the invoking set and the set operand.
  IntSet unions(const IntSet& operand) const;

  // Returns a set that is the intersection of the invoking set and the set operand.
  IntSet intersect(const IntSet& operand) const;

  // Returns a set that is the difference between the invoking set (call it A)
  // and the set operand (call it B).  In other words, compute A-B. 
  IntSet difference(const IntSet& operand) const;

  // Returns the complement of the set.
  IntSet complement() const;

  // Returns true if the invoking set is equal to the set operand.
  bool isEqual(const IntSet& operand) const;

private:
  // TODO: Complete the private section of the class.
};

#endif
