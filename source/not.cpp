#include "../headers/not.h"

NOT::NOT(Gate * g)
{
	inputs = 1;
	state = false;
	input = &(g->state);
	matrix[g->num][num] = true;
}
void NOT::update()
{
	state = !(*input);
}