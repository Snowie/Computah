#include "../headers/gate.h"

vector<vector<bool>> matrix;
vector<Gate *> gates;

int Gate::id = -1;

Gate::Gate()
{
	int toResize = matrix.size() + 1;
	for(unsigned int i = 0; i < matrix.size(); ++i)
	{
		matrix[i].resize(toResize);
		matrix[i].back() = false;
	}
			
	matrix.resize(toResize);
	matrix.back().resize(toResize);

	for(unsigned int i = 0; i < matrix.back().size(); ++i)
		matrix.back()[i] = false;

	num = ++id;

	gates.push_back(this);
}