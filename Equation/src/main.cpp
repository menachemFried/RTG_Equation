/*
 * main.cpp
 *
 *  Created on: 18 באוג׳ 2026
 *      Author: מנחם פריד
 */


 #include <iostream>
 #include "Equation.h"



 int main() {
 	
 	using namespace std;
 	Equation eq(10,20,30);
 	cout << eq << endl;
 	//should print: 10X^2 + 20X + 30 = 0
 	
 	cout << eq.get_solutions_size() << endl;
 	//should print 0
 	
 	eq = -20 + eq;
 	cout << eq << endl;
 	//should print: 10X^2 + 20X + 10 = 0
 	cout << eq.get_solutions_size() << endl;
 	//should print 1
 	cout << eq.get_solutions()[0] << endl;
 	//should print -1
 	
 	
 	cout << Equation(1,5,3) + Equation(2,6,4) << endl;
 	//should print: 3X^2 + 11X + 7 = 0
 	eq = Equation(1,3,-4);
 	cout << eq << endl;
 	//should print 1X^2 + 3X + -4 = 0
 	cout << eq.get_solutions_size() << endl;
 	//should print 2
 	cout << "X1 = " << eq.get_solutions()[0] << endl;
 	//should print: X1 = 1
 	cout << "X2 = " << eq.get_solutions()[1] << endl;
 	//should print: X2 = -4
 	
 	
	cout << Equation(1,5,3) - Equation(1,1,1) << endl;
	//should print: 3X^2 + 11X + 7 = 0
	eq = Equation(1,3,-4);
	cout << eq << endl;
	//should print 1X^2 + 3X + -4 = 0
	cout << eq.get_solutions_size() << endl;
	//should print 2
	cout << "X1 = " << eq.get_solutions()[0] << endl;
	//should print: X1 = 1
	cout << "X2 = " << eq.get_solutions()[1] << endl;
	//should print: X2 = -4
	
 	return 0;
 }

