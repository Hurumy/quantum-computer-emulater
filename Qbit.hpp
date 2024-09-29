
#pragma once

#include <complex>

class Qbit
{
	private:
		int		seed;
		bool	broken; // is this bit read
		bool	value;
		std::complex<double>	amp_a;
		std::complex<double>	amp_b;
		double					phase;
		
		// It is the 
		bool	calculateValue();
		
	protected:
	
	public:
		void	setAmp_a(double real, double imag);
		void	setAmp_b(double real, double imag);
		void	setPhase(double p);
		const std::complex<double>	&getAmp_a() const;
		const std::complex<double>	&getAmp_b() const;
		double	getPhase() const;
		bool	getValue();
};


