#ifndef AND_H
#define AND_H
#include "gate.h"

class AND: public Gate
{
	public:
		bool * left;
		bool * right;
		AND(Gate *, Gate *);
		void update();
};

#endif