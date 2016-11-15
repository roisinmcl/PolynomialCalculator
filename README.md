# PolynomialCalculator

### Linked List Polynomial Calculator

...by Roisin McLoughlin
...rem99 at georgetown dot edu
...Last Modified 10/5/16

Adds, subtracts, multiples, exponentiates, and evaluates polynomials using a linked list.

-----------------------
Running the Program

`g++ LinkedList.cpp main.cpp [inputFile.txt]`

arguements:

* `inputFile` - File containing positive or negative integers separated by spaces
  * Contains two lines of integers representing the two polynomials to be evaluated. Listed as a series of coefficients and exponents seperated by spaces. Only accepts positive or zero exponents.

-----------------------
Implementation

A Linked List of Term nodes, containing a coefficient and exponent.
