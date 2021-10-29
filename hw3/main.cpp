// NAME: Gary Tou
// FILE: main.cpp
// DESCRIPTION: Tests IntSet class

#include <iostream>
using namespace std;

#include "IntSet.h"

int main()
{
  IntSet a(100);
  IntSet b(100);

  a.addElement(11);
  a.addElement(44);
  a.addElement(77);
  a.addElement(99);
  b.addElement(22);
  b.addElement(44);
  b.addElement(66);
  b.addElement(99);

  IntSet c = a.unions(b);
  c.display();
  cout << endl;

  return 0;
}
