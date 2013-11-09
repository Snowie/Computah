#ifndef NOT_H
#define NOT_H
#include "gate.h"
class NOT: public Gate
{
	public:
		bool * input;
		NOT(Gate *);
		void update();
};
#endif