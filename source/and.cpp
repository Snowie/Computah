#include "../headers/and.h"

AND::AND(Gate * l, Gate * r)
{
	inputs = 2;
	state = false;
	left = &(l->state);
	right = &(r->state);
	matrix[r->num][num] = true;
	matrix[l->num][num] = true;
}
void AND::update()
{
	state = (*left) & (*right);
}