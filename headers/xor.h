#ifndef XOR_H
#define XOR_H
#include "gate.h"
class XOR: public Gate
{
	public:	
		bool * left;
		bool * right;
		XOR(Gate *, Gate *);
		void update();
};
#endif