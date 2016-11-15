//
//  LinkedList.cpp
//  PolyProject
//
//  Created by Roisin McLoughlin on 9/20/16.
//  Copyright © 2016 Roisin McLoughlin. All rights reserved.
//
#include <cmath>
#include <iostream>
#include <sstream>

#include "LinkedList.h"

using namespace std;

//*********** Term Class Definition ***********

Term::Term() {
    next = NULL;
}

Term::Term(Term& t) {
    coef = t.coef;
    exponent = t.exponent;
    next = NULL;
}

Term::Term(int co, int ex) {
    coef = co;
    exponent = ex;
    next = NULL;
}

string Term::toString() {
    stringstream ss;
    if (exponent == 0) {
        ss << coef;
        return ss.str();
    } else if (coef == 1) {
        ss << "x^" << exponent;
        return ss.str();
    }

    ss << coef << "x^" << exponent;
    return ss.str();
}

// ******** End Term Class Definition *********


// ******* Linked List Class Definition *******

LinkedList::LinkedList(const LinkedList& listToCopy) {
    head = NULL;
    tail = NULL;

    if(listToCopy.size == 0){
        return;
    }
    else {
        try {
            Term* ptr = listToCopy.head;
            while (ptr != NULL) {
                Term* t = new Term(*ptr);
                this->add(t);
                ptr = ptr->next;
            }
        
        } catch(bad_alloc err) {
            cout << "Bad allocation error." << endl;
        }
    }
}

//Overloaded default constructor
LinkedList::LinkedList() {
    size = 0;
    head = NULL;
    tail = NULL;
}

//Contructor that takes in a head term
LinkedList::LinkedList(Term* t) {
    size = 0;
    head = t;
    tail = t;
}

//Destructor
LinkedList::~LinkedList() {
    bool debug = false;
    Term* ptr = head;
    while (ptr != NULL) {
        Term* tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

//Copies a LinkedList to replace an existing LinkedList
void LinkedList::copyList(const LinkedList& ll) {
    head = NULL;
    tail = NULL;

    if (ll.size == 0){
        return;
    } else {
        try {
            Term* ptr = ll.head;
            while (ptr != NULL) {
                Term* t = new Term(*ptr);
                this->add(t);
                ptr = ptr->next;
            }

        } catch(bad_alloc err) {
            cout << "Bad allocation error." << endl;
        }
    }
}

//Overloaded assignment operator
LinkedList LinkedList::operator=(const LinkedList& ll) {
    LinkedList tmp_list;
    tmp_list.copyList(ll);
    return tmp_list;
}

//Adds a term to a LinkedList
//Does not combine terms
//Adds terms in descending order of exponent magnitude
void LinkedList::add(Term* t2) {
    size++;
    if (head == NULL) {
    //List is empty, add term to the front
        head = t2;
        tail = t2;
    
    } else {
    //List is not empty, find where it should be inserted
        if (head->next == NULL) {
        //Only one Term exists in the list
            if (t2->getExponent() < head->getExponent()) {
            //t2 will be inserted last
                head->next = t2;
                tail = t2;
                return;
            } else {
            //t2 should be the head
                Term* ptr = head;
                tail = ptr;
                head = t2;
                t2->next = ptr;
                return;
            }
        } else {
          //More than one term in list, finding location to insert term
            Term* ptr = head;
            while (ptr != NULL && ptr->next != NULL) {
                //while more terms exist after ptr
                if (t2->getExponent() > ptr->getExponent()) {
                    head = t2;
                    t2->next = ptr;
                    return;
                }
                if (t2->getExponent() < ptr->getExponent() &&
                    t2->getExponent() > ptr->next->getExponent()) {
                    //if t2 is less than the current node and greater than the node after
                    Term* tmp = ptr->next;
                    ptr->next = t2;
                    t2->next = tmp;
                    return;
                }
                ptr = ptr->next;
            }
            if (t2->getExponent() < tail->getExponent()) {
            //t2 should be the last term in the list
                Term* tmp = tail;
                tmp->next = t2;
                tail = t2;
                t2->next = NULL;
                return;
            }
        }
    }
}

//Adds terms to an existing list
//If a term with same exponent exists, combines terms
//Inserts in descending order of exponent magnitude
void LinkedList::add_combine_terms(Term* t2) {
    if (head == NULL) {
        //If the list is empty, add the term to the front
        head = t2;
        tail = t2;
        size++;
    } else {
        //If the list is not empty, find where it should be inserted
        if (head->next == NULL) {
            //ptr is the second to last term
            if (t2->getExponent() == head->getExponent()) {
                //exponents are equal. Combining terms
                int coef_sum = t2->getCoef() + head->getCoef();
                head->setCoef(coef_sum);
                return;
            }
            if (t2->getExponent() < head->getExponent()) {
                size++;
                //if t2 should be last
                head->next = t2;
                tail = t2;
                return;
            } else {
                size++;
                //if t2 should be the head
                Term* ptr = head;
                head->next = ptr;
                tail = ptr;
                head = t2;
                return;
            }
        } else {
          //More than one term in list, finding location to insert term
            Term* ptr = head;
            while (ptr != NULL) {
                if (t2->getExponent() == ptr->getExponent()) {
                    //Exponents are equal, combining terms
                    int coef_sum = t2->getCoef() + ptr->getCoef();
                    ptr->setCoef(coef_sum);
                    return;
                } else if (ptr->next != NULL) {
                    //while more terms exist after ptr
                    if (t2->getExponent() > ptr->getExponent()) {
                        head = t2;
                        t2->next = ptr;
                        size++;
                        return;
                    }
                    if (t2->getExponent() < ptr->getExponent() &&
                        t2->getExponent() > ptr->next->getExponent()) {
                        //if t2 is less than the current node and greater than the node after
                        size++;
                        Term* tmp = ptr->next;
                        ptr->next = t2;
                        t2->next = tmp;
                        return;
                    }
                }
                ptr = ptr->next;
            }
            if (t2->getExponent() < tail->getExponent()) {
            //Last term in list, inserting t2 as last
                size++;
                Term* tmp = tail;
                tmp->next = t2;
                tail = t2;
                t2->next = NULL;
            }
        }
    }
}

void LinkedList::printList() {
    Term* ptr = head;
    if (head == NULL) {
        cout << "Printing empty list." << endl;
        return;
    }
    while (size > 0 && ptr != NULL) {
        cout << ptr->toString();
        if (ptr->next != NULL) {
            cout << " + ";
        }
        ptr = ptr->next;
    }
    cout << endl;
    
}

LinkedList LinkedList::operator+(const LinkedList& ll) {
    Term* list1 = head;
    Term* list2 = ll.head;
    LinkedList result;

    while (list1 != NULL || list2 != NULL) {
        if (list1 == NULL) {
            //End of list1. Adding a remaining value of list2
            Term* t = new Term(list2->getCoef(), list2->getExponent());
            result.add(t);
            list2 = list2->next;
        } else if (list2 == NULL) {
            //End of list2. Adding a remaining value of list1
            Term* t = new Term(list1->getCoef(), list1->getExponent());
            result.add(t);
            list1 = list1->next;
        } else if (list1->getExponent() == list2->getExponent()) {
            //Coefficients are equal. Combining terms
            int coef = list1->getCoef() + list2->getCoef();
            Term* t = new Term(coef, list1->getExponent());
            result.add(t);
            list1 = list1->next;
            list2 = list2->next;
        } else if (list1->getExponent() > list2->getExponent()) {
            //l1's exponent larger than l2's
            //adding value of l1 and incrementing l1
            Term* t = new Term(list1->getCoef(), list1->getExponent());
            result.add(t);
            list1 = list1->next;
        } else if (list1->getExponent() < list2->getExponent()) {
            //l2's exponent larger than l1's
            //adding value of l2 and incrementing l2
            Term* t = new Term(list2->getCoef(), list2->getExponent());
            result.add(t);
            list2 = list2->next;
        }
    }
    return result;
}

LinkedList LinkedList::operator-(const LinkedList& ll) {
    Term* list1 = head;
    Term* list2 = ll.head;
    LinkedList result;

    while (list1 != NULL || list2 != NULL) {
        if (list1 == NULL) {
            //End of list1. Subtracting a remaining value of list2
            Term* t = new Term(-(list2->getCoef()), list2->getExponent());
            result.add(t);
            list2 = list2->next;
        } else if (list2 == NULL) {
            //End of list2. Subtracting a remaining value of list1
            Term* t = new Term(-(list1->getCoef()), list1->getExponent());
            result.add(t);
            list1 = list1->next;
        } else if (list1->getExponent() == list2->getExponent()) {
            //Exponents equal. Combining terms
            int coef = list1->getCoef() - list2->getCoef();
            if (coef != 0) {
                Term* t = new Term(coef, list1->getExponent());
                result.add(t);
            }
            list1 = list1->next;
            list2 = list2->next;
        } else if (list1->getExponent() > list2->getExponent()) {
            //l1's exponent is larger than l2
            //Subtracting l1 and incrementing l1
            Term* t = new Term(-(list1->getCoef()), list1->getExponent());
            result.add(t);
            list1 = list1->next;
        } else if (list1->getExponent() < list2->getExponent()) {
            //l2's exponent is larger than l1
            //Subtracting l2 and incrementing l2
            Term* t = new Term(-(list2->getCoef()), list2->getExponent());
            result.add(t);
            list2 = list2->next;
        }
    }
    return result;
}

LinkedList LinkedList::operator*(const LinkedList& ll) {
    Term* list1 = head;
    Term* list2 = ll.head;
    LinkedList result;
    
    while (list1 != NULL) {
        while (list2 != NULL) {
            int coef_product = list1->getCoef() * list2->getCoef();
            int exp_sum = list1->getExponent() + list2->getExponent();
            Term* t = new Term(coef_product, exp_sum);
            result.add_combine_terms(t);
            list2 = list2->next;
        }
        list2 = ll.head;
        list1 = list1->next;
    }
    
    return result;
}

LinkedList LinkedList::exponent(int exp) {
    if (exp < 0) {
        cout << "Cannot evaluate a negative exponent." << endl;
        cout << "Returning original list: " << endl;
        return (*this);
    }

    if (exp == 0) {
        //Exponent is zero: result is 1x^0
        LinkedList result;
        Term* t = new Term(1,0);
        result.add(t);
        return result;
    }

    LinkedList listCopy(*this);
    LinkedList final(*this);
    for(int i = 1; i < exp; i++) {
	LinkedList tmp(final * listCopy);
        final.copyList(tmp);
    }
    final.printList();
    return final;
}

int LinkedList::evaluate(int x) {
    Term* ptr = head;
    int sum = 0;
    try {
        while (ptr != NULL) {
            int term_eval = pow(x, ptr->getExponent()) * ptr->getCoef();
            sum += term_eval;
            ptr = ptr->next;
        }
    } catch (string error) {
        cout << error << endl;
        return 0;
    }
    return sum;
}

// **** End Linked List Class Definition *****
