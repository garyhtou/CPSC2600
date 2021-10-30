// NAME: Gary Tou
// FILE: main.cpp
// DESCRIPTION: Tests IntSet class

#include <iostream>
using namespace std;

#include "IntSet.h"

// Helper function for printing seperator headers
void printHeader(string header)
{
  cout << "\n\n===== " << header << " =====" << endl;
}

// Helper function for printing Set data for Question #3
void printQuestion3(string setName, IntSet &set)
{
  cout << setName << ": ";
  set.display();
  cout << "Number of Elements: " << set.numElements() << "\n"
       << endl;
}

int main()
{
  printHeader("ORIGINAL `main.cpp` TEST CODE");
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

  printHeader("ASSIGNMENT PART 2");

  // ========== QUESTION 1 ==========
  IntSet A(100);
  IntSet B(100);
  IntSet C(100);
  // Loop through all positive integers less than or equal to 100
  for (int i = 1; i <= 100; i++)
  {
    // If `i` is even (divisible by 2), add to A IntSet
    if (i % 2 == 0)
    {
      A.addElement(i);
    }

    // If `i` is even (divisible by 5), add to B IntSet
    if (i % 5 == 0)
    {
      B.addElement(i);
    }

    // If `i` is even (divisible by 10), add to C IntSet
    if (i % 10 == 0)
    {
      C.addElement(i);
    }
  }

  // ========== QUESTION 2 ==========
  IntSet D = A.complement();
  IntSet E = A.unions(B);
  IntSet F = A.intersect(B);
  IntSet G = B.difference(A);
  IntSet H = B.intersect(C);

  // ========== QUESTION 3 ==========
  printQuestion3("A", A);
  printQuestion3("B", B);
  printQuestion3("C", C);
  printQuestion3("D", D);
  printQuestion3("E", E);
  printQuestion3("F", F);
  printQuestion3("G", G);
  printQuestion3("H", H);

  // ========== QUESTION 4 ==========
  cout << "a. " << (A.isElement(15) ? "True" : "False") << endl;
  cout << "b. " << (A.isElement(26) ? "True" : "False") << endl;
  cout << "c. " << (B.isEqual(G) == 1 ? "True" : "False") << endl;
  cout << "d. " << (F.isEqual(H) == 1 ? "True" : "False") << endl;

  return 0;
}
