/**
 * @file main.cpp
 * @brief Demonstration and test program for Task 1 (Equation class).
 */

#include <iostream>
#include <stdexcept>
#include "Equation.hpp"

int main() {
    using namespace std;

    cout << "=== Task 1 Demonstration ===" << endl;

    Equation eq(10, 20, 30);
    cout << eq << endl;
    // should print: 10.0 X^2 + 20.0 X + 30.0 = 0

    cout << eq.get_solutions_size() << endl;
    // should print 0

    eq = -20 + eq;
    cout << eq << endl;
    // should print: 10.0 X^2 + 20.0 X + 10.0 = 0

    cout << eq.get_solutions_size() << endl;
    // should print 1

    cout << eq.get_solutions()[0] << endl;
    // should print -1.0

    cout << Equation(1, 5, 3) + Equation(2, 6, 4) << endl;
    // should print: 3.0 X^2 + 11.0 X + 7.0 = 0

    eq = Equation(1, 3, -4);
    cout << eq << endl;
    // should print 1.0 X^2 + 3.0 X + -4.0 = 0

    cout << eq.get_solutions_size() << endl;
    // should print 2

    cout << "X1 = " << eq.get_solutions()[0] << endl;
    // should print: X1 = 1.0

    cout << "X2 = " << eq.get_solutions()[1] << endl;
    // should print: X2 = -4.0

    cout << "\n=== Exception Handling Tests ===" << endl;

    try {
        Equation zero_a(0, 2, 3);
    } catch (const std::invalid_argument &e) {
        cout << "Caught expected exception on constructor: " << e.what() << endl;
    }

    try {
        Equation valid_eq(1, 2, 3);
        valid_eq.set_a(0);
    } catch (const std::invalid_argument &e) {
        cout << "Caught expected exception on set_a: " << e.what() << endl;
    }

    try {
        Equation eq1(5, 2, 3);
        Equation eq2(-5, 1, 1);
        Equation result = eq1 + eq2;
    } catch (const std::invalid_argument &e) {
        cout << "Caught expected exception on addition resulting in A=0: " << e.what() << endl;
    }

    cout << "\nTask 1 execution finished successfully." << endl;
    return 0;
}
