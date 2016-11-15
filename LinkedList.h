//
//  LinkedList.h
//  PolyProject
//
//  Created by Roisin McLoughlin on 9/20/16.
//  Copyright © 2016 Roisin McLoughlin. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdio.h>

class Term {

private:
    short coef;
    short exponent;

public:
    Term* next;
    Term();
    Term(Term& t);
    Term(int co, int exp);
    int getExponent() { return exponent; };
    int getCoef() { return coef; };
    void setExponent(int exp) { exponent = exp; };
    void setCoef(int co) { coef = co; };
    std::string toString();
};

class LinkedList {

private:
    int size;

public:
    Term* head;
    Term* tail;
    LinkedList();
    LinkedList(const LinkedList& ll);
    LinkedList(Term* head);
    ~LinkedList();
    void add(Term* t);
    void add_combine_terms(Term* t);
    void printList();
    LinkedList operator+(const LinkedList&);
    LinkedList operator-(const LinkedList&);
    LinkedList operator*(const LinkedList&);
    LinkedList operator=(const LinkedList&);
    LinkedList exponent(int exp);
    int evaluate(int x);
    void copyList(const LinkedList& ll);

};

#endif /* LinkedList_h */
