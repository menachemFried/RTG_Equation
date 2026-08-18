/*
 * Equation.h
 *
 *  Created on: 17 באוג׳ 2026
 *      Author: מנחם פריד
 */

#ifndef EQUATION_H_
#define EQUATION_H_

#include <iomanip>
#include <iostream>


class Equation {
private:

	double m_a;
	double m_b;
	double m_c;
	
	
	double 		discriminant;
	double* 	solutions;
	std::size_t solutions_size;
	
	void 		update_solutions();
	void		calculate_discriminant();
	
public:

	Equation();
	Equation(const Equation &other);
	Equation(Equation &&other);
	Equation& operator=(const Equation &other);
	Equation& operator=(Equation &&other);
	~Equation();
	
	Equation(double a = 0, double b = 0, double c = 0);
	
		

	
	// Equation = Equation + Equation
	Equation operator - (const Equation &eq) {
	    return *this -= eq;
	}

	// Equation = Equation - double
	Equation operator - (const double c) {
	    return *this += (-c);
	}

	// Equation += Equation
	Equation& operator -= (const Equation &eq) {
		m_a -= eq.m_a;
		m_b -= eq.m_b;
		m_c -= eq.m_c;

		calculate_discriminant();
		update_solutions();

		return *this;
	}
	
	// Equation -= double
	Equation& operator -= (const double c)
	{
	    return *this += (-c);
	}
	
	// Equation = Equation + Equation
	Equation operator + (const Equation &eq) {
	    return *this += eq;
	}

	
	// Equation = Equation + double
	friend Equation operator +(const double c, Equation &eq) {
		return eq += c;
	}
	
	// Equation = double + Equation
	Equation operator + (const double c) {
	    return *this += c;
	}
	
	// Equation += Equation
	Equation& operator += (const Equation &eq)
	{
		if(m_a + eq.m_a == 0)
		{
			throw std::invalid_argument("A could not be Zero");
		}
		else 
		{
			m_a += eq.m_a;
			m_b += eq.m_b;
			m_c += eq.m_c;

			calculate_discriminant();
			update_solutions();
		}
		
	    return *this;
	}
	
	
	// Equation += double
	Equation& operator += (const double c)
	{
		m_c += c;
		
		calculate_discriminant();
		update_solutions();
		
	    return *this;
	}
	
	
	
	friend std::ostream& operator << (
	    std::ostream &out, Equation const &eq)
	{
		out << std::fixed << std::setprecision(1) << eq.get_a() << " X^2 + " << eq.get_b() << " X + " 
		<<  eq.get_c() << " = 0";
		return out;
	}
	
	
	
	void set_a(double);
	void set_b(double);
	void set_c(double);
		
	double get_a() const;
	double get_b() const;
	double get_c() const;
	
	std::size_t get_solutions_size();	// - returns solutions_size.
	double const * get_solutions();		// - returns solutions.

		
};

#endif /* EQUATION_H_ */
