/**
 * @file Equation.cpp
 * @brief Implementation file for the Equation class representing a Quadratic Equation.
 *
 * Task 1 - C++ Final Assignment (v1.3.2)
 * Contains method definitions for dynamic resource management, equation solving,
 * const-correct accessors/mutators, and operator overloading.
 */

#include "Equation.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>

/* ------------------------------------------------------------------------- */
/*                             PRIVATE METHODS                               */
/* ------------------------------------------------------------------------- */

/**
 * @brief Calculates discriminant B^2 - 4AC and updates solutions_size.
 */
void Equation::calculate_discriminant() {
    discriminant = m_b * m_b - 4.0 * m_a * m_c;

    if (discriminant < 0.0) {
        solutions_size = 0;
    } else if (discriminant == 0.0) {
        solutions_size = 1;
    } else {
        solutions_size = 2;
    }
}

/**
 * @brief Computes real solution roots based on calculated discriminant.
 */
void Equation::update_solutions() {
    if (solutions == nullptr) {
        return;
    }

    if (solutions_size == 0) {
        solutions[0] = 0.0;
        solutions[1] = 0.0;
    } else if (solutions_size == 1) {
        solutions[0] = -m_b / (2.0 * m_a);
        solutions[1] = 0.0;
    } else {
        double sqrt_d = std::sqrt(discriminant);
        solutions[0] = (-m_b + sqrt_d) / (2.0 * m_a);
        solutions[1] = (-m_b - sqrt_d) / (2.0 * m_a);
    }
}

/* ------------------------------------------------------------------------- */
/*                             CONSTRUCTORS & DESTRUCTOR                     */
/* ------------------------------------------------------------------------- */

/**
 * @brief Default constructor (1.0 * X^2 + 0.0 * X + 0.0 = 0).
 */
Equation::Equation()
    : m_a(1.0),
      m_b(0.0),
      m_c(0.0),
      discriminant(0.0),
      solutions(new double[2]{0.0, 0.0}),
      solutions_size(0) {
    calculate_discriminant();
    update_solutions();
}

/**
 * @brief Parametric constructor. Validates that coefficient A is non-zero.
 */
Equation::Equation(double a, double b, double c)
    : m_a(a),
      m_b(b),
      m_c(c),
      discriminant(0.0),
      solutions(nullptr),
      solutions_size(0) {
    // Validate coefficient A before allocating dynamic memory to prevent memory leaks
    if (a == 0.0) {
        throw std::invalid_argument("Coefficient A cannot be zero.");
    }

    solutions = new double[2]{0.0, 0.0};
    calculate_discriminant();
    update_solutions();
}

/**
 * @brief Copy constructor performing deep copy of solutions array.
 */
Equation::Equation(const Equation &other)
    : m_a(other.m_a),
      m_b(other.m_b),
      m_c(other.m_c),
      discriminant(other.discriminant),
      solutions(new double[2]{other.solutions[0], other.solutions[1]}),
      solutions_size(other.solutions_size) {
}

/**
 * @brief Move constructor transferring pointer ownership.
 */
Equation::Equation(Equation &&other) noexcept
    : m_a(other.m_a),
      m_b(other.m_b),
      m_c(other.m_c),
      discriminant(other.discriminant),
      solutions(other.solutions),
      solutions_size(other.solutions_size) {
    other.solutions = nullptr;
    other.solutions_size = 0;
}

/**
 * @brief Copy assignment operator with self-assignment check and deep copy.
 */
Equation& Equation::operator=(const Equation &other) {
    if (this != &other) {
        m_a = other.m_a;
        m_b = other.m_b;
        m_c = other.m_c;
        discriminant = other.discriminant;
        solutions_size = other.solutions_size;

        if (solutions == nullptr) {
            solutions = new double[2];
        }
        solutions[0] = other.solutions[0];
        solutions[1] = other.solutions[1];
    }
    return *this;
}

/**
 * @brief Move assignment operator transferring dynamic memory ownership.
 */
Equation& Equation::operator=(Equation &&other) noexcept {
    if (this != &other) {
        delete[] solutions;

        m_a = other.m_a;
        m_b = other.m_b;
        m_c = other.m_c;
        discriminant = other.discriminant;
        solutions = other.solutions;
        solutions_size = other.solutions_size;

        other.solutions = nullptr;
        other.solutions_size = 0;
    }
    return *this;
}

/**
 * @brief Destructor releasing dynamic array memory.
 */
Equation::~Equation() {
    delete[] solutions;
    solutions = nullptr;
}

/* ------------------------------------------------------------------------- */
/*                             ACCESSORS & MUTATORS                          */
/* ------------------------------------------------------------------------- */

double Equation::get_a() const {
    return m_a;
}

double Equation::get_b() const {
    return m_b;
}

double Equation::get_c() const {
    return m_c;
}

std::size_t Equation::get_solutions_size() const {
    return solutions_size;
}

double const* Equation::get_solutions() const {
    return solutions;
}

void Equation::set_a(double a) {
    if (a == 0.0) {
        throw std::invalid_argument("Coefficient A cannot be zero.");
    }
    m_a = a;
    calculate_discriminant();
    update_solutions();
}

void Equation::set_b(double b) {
    m_b = b;
    calculate_discriminant();
    update_solutions();
}

void Equation::set_c(double c) {
    m_c = c;
    calculate_discriminant();
    update_solutions();
}

/* ------------------------------------------------------------------------- */
/*                             COMPOUND ASSIGNMENT OPERATORS                 */
/* ------------------------------------------------------------------------- */

Equation& Equation::operator+=(const Equation &eq) {
    if (m_a + eq.m_a == 0.0) {
        throw std::invalid_argument("Resulting coefficient A cannot be zero.");
    }
    m_a += eq.m_a;
    m_b += eq.m_b;
    m_c += eq.m_c;
    calculate_discriminant();
    update_solutions();
    return *this;
}

Equation& Equation::operator+=(double val) {
    m_c += val;
    calculate_discriminant();
    update_solutions();
    return *this;
}

Equation& Equation::operator-=(const Equation &eq) {
    if (m_a - eq.m_a == 0.0) {
        throw std::invalid_argument("Resulting coefficient A cannot be zero.");
    }
    m_a -= eq.m_a;
    m_b -= eq.m_b;
    m_c -= eq.m_c;
    calculate_discriminant();
    update_solutions();
    return *this;
}

Equation& Equation::operator-=(double val) {
    m_c -= val;
    calculate_discriminant();
    update_solutions();
    return *this;
}

/* ------------------------------------------------------------------------- */
/*                             BINARY OPERATORS                              */
/* ------------------------------------------------------------------------- */

Equation Equation::operator+(const Equation &eq) const {
    return Equation(m_a + eq.m_a, m_b + eq.m_b, m_c + eq.m_c);
}

Equation Equation::operator+(double val) const {
    return Equation(m_a, m_b, m_c + val);
}

Equation Equation::operator-(const Equation &eq) const {
    return Equation(m_a - eq.m_a, m_b - eq.m_b, m_c - eq.m_c);
}

Equation Equation::operator-(double val) const {
    return Equation(m_a, m_b, m_c - val);
}

Equation operator+(double val, const Equation &eq) {
    return eq + val;
}

Equation operator-(double val, const Equation &eq) {
    return Equation(-eq.m_a, -eq.m_b, val - eq.m_c);
}

/* ------------------------------------------------------------------------- */
/*                             STREAM OPERATORS                              */
/* ------------------------------------------------------------------------- */

std::ostream& operator<<(std::ostream &out, const Equation &eq) {
    out << std::fixed << std::setprecision(1)
        << eq.m_a << " X^2 + " << eq.m_b << " X + " << eq.m_c << " = 0";
    return out;
}
