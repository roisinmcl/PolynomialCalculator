//
//  main.cpp
//  PolyProject
//
//  Created by Roisin McLoughlin on 9/20/16.
//  Copyright © 2016 Roisin McLoughlin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "LinkedList.h"

int main(int argc, const char * argv[]) {

    //***************** File Input *****************************
    
    if (argc != 2) {
        cout << "Please provide a file name." << endl;
        return 0;
    }
    
    LinkedList poly1;
    LinkedList poly2;
    bool first = true;
    
    try {
        ifstream inFile(argv[1], ios::in);
        if (!inFile) {
            cout << argv[0] << endl;
            cout << "Input: " << argv[1] << endl;
            string error = "Cannot open file. Exiting program...";
            throw error;
        }
        
        while (!inFile.eof()) {
            string str;
            while (getline(inFile, str)) {
                istringstream ss(str);
                short coef, exp;
                while (ss >> coef) {
                    ss >> exp;
                    if (first) {
                        Term* t = new Term(coef, exp);
                        //poly1.add(Term(coef, exp));
                        poly1.add(t);
                    } else {
                        Term* t = new Term(coef, exp);
                        //poly2.add(Term(coef, exp));
                        poly2.add(t);
                    }
                }
                first = false;
            }
        }
        
        inFile.close();
        
    } catch(string error) {
        cout << error << endl;
        return 0;
    }


    //**************** Test Cases and Output ************************

    //Print and evaluate the first polynomial for x = 1, 2, 3, 10
    cout << endl;
    cout << "Polynomial 1: ";
    poly1.printList();
    cout << "x = 1: " << poly1.evaluate(1) << endl;
    cout << "x = 2: " << poly1.evaluate(2) << endl;
    cout << "x = 3: " << poly1.evaluate(3) << endl;
    cout << "x = 10: " << poly1.evaluate(10) << endl;
    
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;
    
    cout << "Polynomial 2: ";
    poly2.printList();
    cout << "x = 1: " << poly2.evaluate(1) << endl;
    cout << "x = 2: " << poly2.evaluate(2) << endl;
    cout << "x = 3: " << poly2.evaluate(3) << endl;
    cout << "x = 10: " << poly2.evaluate(10) << endl;
    
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

    cout << "Polynomial 1 + 2: " << endl;
    LinkedList sum = poly1 + poly2;
    sum.printList();
    cout << "x = 1: " << sum.evaluate(1) << endl;
    cout << "x = 2: " << sum.evaluate(2) << endl;
    cout << "x = 3: " << sum.evaluate(3) << endl;
    cout << "x = 10: " << sum.evaluate(10) << endl;
    
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;
    
    cout << "Polynomial 1 - 2: " << endl;
    LinkedList diff = poly1 - poly2;
    diff.printList();
    cout << "x = 1: " << diff.evaluate(1) << endl;
    cout << "x = 2: " << diff.evaluate(2) << endl;
    cout << "x = 3: " << diff.evaluate(3) << endl;
    cout << "x = 10: " << diff.evaluate(10) << endl;

    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;
    
    cout << "Polynomial 1 * 2: " << endl;
    LinkedList product = poly1 * poly2;
    product.printList();
    cout << "x = 1: " << product.evaluate(1) << endl;
    cout << "x = 2: " << product.evaluate(2) << endl;
    cout << "x = 3: " << product.evaluate(3) << endl;
    cout << "x = 10: " << product.evaluate(10) << endl;

    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

    cout << "Polynomial 1 ^5: " << endl;
    LinkedList p1fifth = poly1.exponent(5);
    (p1fifth).printList();
    cout << "x = 1: " << p1fifth.evaluate(1) << endl;
    cout << "x = 2: " << p1fifth.evaluate(2) << endl;
    cout << "x = 3: " << p1fifth.evaluate(3) << endl;
    cout << "x = 10: " << p1fifth.evaluate(10) << endl;
    
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

    cout << "Polynomial 1 ^ (Polynomail 2 evaluated for x = 5): " << endl;
    LinkedList p1top2at5 = poly1.exponent(poly2.evaluate(5));
    (p1top2at5).printList();
    cout << "x = 1: " << p1top2at5.evaluate(1) << endl;
    cout << "x = 2: " << p1top2at5.evaluate(2) << endl;
    cout << "x = 3: " << p1top2at5.evaluate(3) << endl;
    cout << "x = 10: " << p1top2at5.evaluate(10) << endl;

    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;
    
    cout << "Polynomial 1 ^5 evaluated for x = 2: " << endl;
    int p1to5at2 = (poly1.exponent(5)).evaluate(2);
    cout << "x = 2: " <<  p1to5at2 << endl;
    cout << endl;
    cout << "--------------------------------------------" << endl;
    
    return 0;
}
