#include "../headers/or.h"

OR::OR(Gate * l, Gate * r)
{
	inputs = 2;
	state = false;
	left = &(l->state);
	right = &(r->state);
	matrix[r->num][num] = true;
	matrix[l->num][num] = true;
}
void OR::update()
{
	state = (*left) | (*right);
}