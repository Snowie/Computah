#ifndef OR_H
#define OR_H
#include "gate.h"
class OR: public Gate
{
	public:	
		bool * left;
		bool * right;
		OR(Gate *, Gate *);
		void update();
};
#endif