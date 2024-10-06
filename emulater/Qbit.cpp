
#include "Qbit.hpp"
#include <complex>
#include <math>
#include <cstdlib>

void	Qbit::setAmp_a(double real, double imag)
{
	amp_a.real = real;
	amp_a.imag = imag;
}

void	Qbit::setAmp_b(double real, double imag)
{
	amp_b.real = real;
	amp_b.imag = imag;
}

void	Qbit::setPhase(double p)
{
	phase = p;
}

const std::complex<double>	&Qbit::getAmp_a() const
{
	return (amp_a);
}

const std::complex<double>	&Qbit::getAmp_b() const
{
	return (amp_b);
}

double	Qbit::getPhase() const
{
	return (phase);
}

bool	Qbit::calculateValue()
{
	
	value = amp_a;
}

bool	Qbit::getValue()
{
	calculateValue();
	broken = true;
	return (value);
}




