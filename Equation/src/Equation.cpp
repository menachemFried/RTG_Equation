//============================================================================
// Name        : Equation.cpp
// Author      : Menachem Fried
// Version     :
// Copyright   : RTG Class Work
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cmath>
#include <stdexcept>
#include "Equation.h"


/* ---- PRIVATE functions ---- */

void Equation::calculate_discriminant()
{
	discriminant = m_b * m_b - 4 * m_a * m_c;
	
	if(discriminant < 0)
	{
		solutions_size = 0;
	} 
	else if(discriminant == 0)
	{
		solutions_size = 1;
	} 
	else
	{
		solutions_size = 2;
	}
}


void Equation::update_solutions()
{
	if(solutions != nullptr)
	{
		if(discriminant < 0)
		{
			solutions[0] = 0;
			solutions[1] = 0;
		} 
		else if(discriminant == 0)
		{
			solutions[0] = -m_b / (2 * m_a);
			solutions[1] = 0;
		} 
		else
		{
			solutions[0] = (-m_b + std::sqrt(discriminant))/ (2 * m_a);
			solutions[1] = (-m_b - std::sqrt(discriminant))/ (2 * m_a);
		}	
	}
}


/* ---- PUBLIC functions ---- */

Equation::Equation()
		: 	m_a(1), m_b(0), m_c(0),
			discriminant(0),
			solutions(new double [2]),
			solutions_size(0)
	{
		calculate_discriminant();
		update_solutions();
	}


Equation::~Equation() {
	delete [] solutions;
	solutions = nullptr;
}

Equation::Equation(const Equation &other)	
		: 	m_a(other.m_a), m_b(other.m_b), m_c(other.m_c),
			discriminant(0),
			solutions(new double [2]),
			solutions_size(0)
{
	if(m_a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	calculate_discriminant();
	update_solutions();
}
Equation::Equation(Equation &&other)	
		: 	m_a(other.m_a), m_b(other.m_b), m_c(other.m_c),
			discriminant(0),
			solutions(nullptr),
			solutions_size(0)
{
	if(m_a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	
	std::move(other.solutions,&(other.solutions[2]),solutions);
	calculate_discriminant();
	update_solutions();
}

Equation& Equation::operator=(const Equation &other)
{
	if(other.m_a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	else 
	{
		m_a = other.m_a;
		m_b = other.m_b;
		m_c = other.m_c;

		calculate_discriminant();
		update_solutions();
	}
	
	return *this;
}

Equation& Equation::operator=(Equation &&other) {
	if(other.m_a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	else 
	{
		m_a = other.m_a;
		m_b = other.m_b;
		m_c = other.m_c;

		std::move(other.solutions,&(other.solutions[2]),solutions);
		calculate_discriminant();
		update_solutions();
	}
		
	return *this;
}




Equation::Equation(double a, double b, double c)
		:	m_a(a), m_b(b), m_c(c),
			discriminant(0),
			solutions(new double [2]),
			solutions_size(0)
{
	if(a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	else 
	{
		calculate_discriminant();
		update_solutions();
	}
}





void Equation::set_a(double a)
{
	if(a == 0)
	{
		delete [] solutions;
		solutions = nullptr;
		throw std::invalid_argument("A could not be Zero");
	}
	else 
	{
		m_a = a;
	}
}

void Equation::set_b(double b)
{
	m_b = b;
}

void Equation::set_c(double c)
{
	m_c = c;
}
	
double Equation::get_a() const
{
	return m_a;
}

double Equation::get_b() const
{
	return m_b;
}

double Equation::get_c() const
{
	return m_c;
}


std::size_t Equation::get_solutions_size()
{
	return solutions_size;
}


double const * Equation::get_solutions()
{
	return solutions;
}


