
#pragma once

#include "Qbit.hpp"
#include "Matrix.hpp"

class Gate
{
	public:
		void	ApplyHGate(Qbit &q);
		void	ApplyXGate(Qbit &q);
		void	ApplyYGate(Qbit &q);
		void	ApplyZGate(Qbit &q);
	private:
		const Matrix HGate((1,0), (1,0), (1,0), (-1,0));
		const Matrix XGate((0,0), (1,0), (1,0), (0,0));
		const Matrix YGate((0,0), (0,-1), (0,1), (0,0));
		const Matrix ZGate((1,0), (0,0), (0,0), (-1,0));
};



