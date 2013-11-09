#ifndef GATE_H
#define GATE_H

#include <vector>
using namespace std;

class Gate;

//God forgive me for this.
extern vector<vector<bool>> matrix;
extern vector<Gate *> gates;

class Gate
{
	public:
		static int id;
		bool state;
		int num;
		int inputs;
		Gate();
		virtual void update() = 0;
};

#endif