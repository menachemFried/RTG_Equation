/**
 * @file main.cpp
 * @brief Demonstration, test program, and Memory Leak Detector for Task 1 (Equation class).
 */

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include "Equation.hpp"

/* ------------------------------------------------------------------------- */
/*                   WINDOWS MEMORY LEAK TRACKER OVERRIDES                  */
/* ------------------------------------------------------------------------- */

static std::size_t g_active_allocations = 0;
static std::size_t g_total_allocations = 0;

void* operator new[](std::size_t size) {
    g_active_allocations++;
    g_total_allocations++;
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

void operator delete[](void* p) noexcept {
    if (p) {
        if (g_active_allocations > 0) {
            g_active_allocations--;
        }
        std::free(p);
    }
}

void operator delete[](void* p, std::size_t) noexcept {
    operator delete[](p);
}

/* ------------------------------------------------------------------------- */
/*                               MAIN FUNCTION                               */
/* ------------------------------------------------------------------------- */

int main() {
    using namespace std;

    {
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

        cout << "\n=== Rule of Five & Memory Stress Test ===" << endl;
        {
            Equation original(2, 5, 2);
            Equation copy_constructed(original);
            Equation move_constructed(std::move(original));

            Equation copy_assigned(1, 1, -2);
            copy_assigned = copy_constructed;

            Equation move_assigned(1, 1, -2);
            move_assigned = std::move(copy_assigned);
        }
    } // All Equation objects destroyed here!

    cout << "\n==============================================" << endl;
    cout << "           MEMORY LEAK TRACKER REPORT         " << endl;
    cout << "==============================================" << endl;
    cout << " Total dynamic allocations (new[])  : " << g_total_allocations << endl;
    cout << " Unfreed active allocations         : " << g_active_allocations << endl;
    if (g_active_allocations == 0) {
        cout << " SUCCESS: 0 MEMORY LEAKS DETECTED! ALL MEMORY FREED." << endl;
    } else {
        cout << " ERROR: MEMORY LEAK DETECTED!" << endl;
    }
    cout << "==============================================" << endl;

    return 0;
}
