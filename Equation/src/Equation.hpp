/**
 * @file Equation.hpp
 * @brief Header file for the Equation class representing a Quadratic Equation.
 *
 * Task 1 - C++ Final Assignment (v1.3.2)
 * Defines the Quadratic Equation class of the form A * X^2 + B * X + C = 0.
 */

#ifndef EQUATION_HPP_
#define EQUATION_HPP_

#include <cstddef>
#include <iostream>

/**
 * @class Equation
 * @brief Represents a quadratic equation of the form A * X^2 + B * X + C = 0.
 *
 * Manages the equation coefficients (a, b, c) and dynamically computes its real solutions.
 * Enforces that coefficient 'a' is non-zero, throwing std::invalid_argument if zero.
 * Implements the Rule of Five for dynamic memory management of solutions array.
 */
class Equation {
private:
    double m_a;                 ///< Coefficient A (must not be 0)
    double m_b;                 ///< Coefficient B
    double m_c;                 ///< Coefficient C

    double discriminant;        ///< Discriminant (B^2 - 4*A*C)
    double* solutions;          ///< Dynamically allocated array for two double solutions
    std::size_t solutions_size; ///< Size of solutions array containing valid roots (0, 1, or 2)

    /**
     * @brief Calculates the discriminant (B^2 - 4AC) and updates solutions_size.
     */
    void calculate_discriminant();

    /**
     * @brief Computes equation real roots based on the discriminant and coefficients.
     */
    void update_solutions();

public:
    /**
     * @brief Default constructor. Constructs Equation with default A=1.0, B=0.0, C=0.0.
     */
    Equation();

    /**
     * @brief Parametric constructor.
     * @param a Coefficient A (must not be zero).
     * @param b Coefficient B.
     * @param c Coefficient C.
     * @throws std::invalid_argument if a == 0.
     */
    Equation(double a, double b, double c);

    /**
     * @brief Copy constructor (Rule of Five).
     * @param other Equation instance to copy.
     */
    Equation(const Equation &other);

    /**
     * @brief Move constructor (Rule of Five).
     * @param other Equation instance to move from.
     */
    Equation(Equation &&other) noexcept;

    /**
     * @brief Copy assignment operator (Rule of Five).
     * @param other Equation instance to copy.
     * @return Equation& Reference to this object.
     */
    Equation& operator=(const Equation &other);

    /**
     * @brief Move assignment operator (Rule of Five).
     * @param other Equation instance to move from.
     * @return Equation& Reference to this object.
     */
    Equation& operator=(Equation &&other) noexcept;

    /**
     * @brief Destructor (Rule of Five). Deallocates dynamic memory.
     */
    ~Equation();

    // Accessors (Getters)
    /**
     * @brief Gets coefficient A.
     * @return double Value of A.
     */
    double get_a() const;

    /**
     * @brief Gets coefficient B.
     * @return double Value of B.
     */
    double get_b() const;

    /**
     * @brief Gets coefficient C.
     * @return double Value of C.
     */
    double get_c() const;

    /**
     * @brief Gets the number of valid real solutions (0, 1, or 2).
     * @return std::size_t Number of solutions.
     */
    std::size_t get_solutions_size() const;

    /**
     * @brief Gets the pointer to the array of solutions.
     * @return double const* Pointer to solutions array.
     */
    double const* get_solutions() const;

    // Mutators (Setters)
    /**
     * @brief Sets coefficient A and recalculates solutions.
     * @param a New value for coefficient A.
     * @throws std::invalid_argument if a == 0.
     */
    void set_a(double a);

    /**
     * @brief Sets coefficient B and recalculates solutions.
     * @param b New value for coefficient B.
     */
    void set_b(double b);

    /**
     * @brief Sets coefficient C and recalculates solutions.
     * @param c New value for coefficient C.
     */
    void set_c(double c);

    // Compound Assignment Operators
    /**
     * @brief In-place addition of two equations.
     * @param eq Equation to add.
     * @return Equation& Reference to this object.
     * @throws std::invalid_argument if resulting A == 0.
     */
    Equation& operator+=(const Equation &eq);

    /**
     * @brief In-place addition of a double value to coefficient C.
     * @param val Constant to add to C.
     * @return Equation& Reference to this object.
     */
    Equation& operator+=(double val);

    /**
     * @brief In-place subtraction of two equations.
     * @param eq Equation to subtract.
     * @return Equation& Reference to this object.
     * @throws std::invalid_argument if resulting A == 0.
     */
    Equation& operator-=(const Equation &eq);

    /**
     * @brief In-place subtraction of a double value from coefficient C.
     * @param val Constant to subtract from C.
     * @return Equation& Reference to this object.
     */
    Equation& operator-=(double val);

    // Binary Operators
    /**
     * @brief Adds two equations and returns a new Equation.
     * @param eq Equation to add.
     * @return Equation Result of addition.
     */
    Equation operator+(const Equation &eq) const;

    /**
     * @brief Adds a constant to coefficient C of an Equation.
     * @param val Constant to add.
     * @return Equation Result of addition.
     */
    Equation operator+(double val) const;

    /**
     * @brief Subtracts an equation from this equation and returns a new Equation.
     * @param eq Equation to subtract.
     * @return Equation Result of subtraction.
     */
    Equation operator-(const Equation &eq) const;

    /**
     * @brief Subtracts a constant from coefficient C of an Equation.
     * @param val Constant to subtract.
     * @return Equation Result of subtraction.
     */
    Equation operator-(double val) const;

    /**
     * @brief Global operator for adding a constant to an Equation (double + Equation).
     * @param val Constant value.
     * @param eq Equation object.
     * @return Equation Result of addition.
     */
    friend Equation operator+(double val, const Equation &eq);

    /**
     * @brief Global operator for subtracting an Equation from a constant (double - Equation).
     * @param val Constant value.
     * @param eq Equation object.
     * @return Equation Result of subtraction.
     */
    friend Equation operator-(double val, const Equation &eq);

    /**
     * @brief Stream insertion operator for printing Equation.
     * Outputs format: "%.1f X^2 + %.1f X + %.1f = 0"
     * @param out Output stream.
     * @param eq Equation to print.
     * @return std::ostream& Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream &out, const Equation &eq);
};

#endif /* EQUATION_HPP_ */
