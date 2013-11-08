#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Gate
{
	public:
		virtual void update() = 0;
		bool state;
		int num;
		int inputs;
};

class AND: public Gate
{
public:
	bool * left;
	bool * right;
	AND(Gate * l, Gate * r, int n)
	{
		num = n;
		inputs = 2;
		state = false;
		left = &(l->state);
		right = &(r->state);
	}
	void update()
	{
		state = (*left) & (*right);
	}
};

class OR: public Gate
{
public:
	bool * left;
	bool * right;
	OR(Gate * l, Gate * r, int n)
	{
		num = n;
		inputs = 2;
		state = false;
		left = &(l->state);
		right = &(r->state);
	}
	void update()
	{
		state = (*left) | (*right);
	}
};

class XOR: public Gate
{
public:
	bool * left;
	bool * right;
	XOR(Gate * l, Gate * r, int n)
	{
		num = n;
		inputs = 2;
		state = false;
		left = &(l->state);
		right = &(r->state);
	}
	void update()
	{
		state = (*left) ^ (*right);
	}
};

class NOT: public Gate
{
public:
	bool * input;
	NOT(Gate * g, int n)
	{
		num = n;
		inputs = 1;
		state = false;
		input = &(g->state);
	}
	void update()
	{
		state = !(*input);
	}
};

//I choose to make values gates because it makes my life more sane.
class ON: public Gate
{
public:
	ON(int n)
	{
		num = n;
		inputs = 0;
		state = true;
	}
	void update()
	{
		;
	}
};

class OFF: public Gate
{
public:
	OFF(int n)
	{
		num = n;
		inputs = 0;
		state = false;
	}
	void update()
	{
		;
	}
};

bool matrix [4][4];
vector <Gate *> gates;

//The following function is written by the proceeding author

// Sean Szumlanski
// COP 3503, Fall 2013

vector <Gate *> topoSort()
{
	vector <Gate *> toRet;
	int incoming [4];
	
	for(int i = 0; i < 4; ++i)
		incoming[i] = 0;
	
	int cnt = 0;

	// Count the number of incoming edges incident to each vertex. For sparse
	// graphs, this could be made more efficient by using an adjacency list.

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(matrix[i][j])
				incoming[j]++;
		}
	}

	queue <Gate *> q;

	// Any vertex with zero incoming edges is ready to be visited, so add it to
	// the queue.
	for (int i = 0; i < 4; i++)
	{
		if (incoming[i] == 0)
		{
			q.push(gates[i]);
		}
	}


	while (!q.empty())
	{
		// Pull a vertex out of the queue and add it to the topological sort.
		Gate * node = q.front();
		toRet.push_back(q.front());
		q.pop();

		// Count the number of unique vertices we see.
		++cnt;


		// All vertices we can reach via an edge from the current vertex should
		// have their incoming edge counts decremented. If one of these hits
		// zero, add it to the queue, as it's ready to be included in our
		// topological sort.
		for (int i = 0; i < 4; i++)
		{
			if (matrix[node->num][i] && --incoming[i] == 0)
			{
				q.push(gates[i]);
			}
		}
	}

	// If we pass out of the loop without including each vertex in our
	// topological sort, we must have a cycle in the graph.
	if (cnt != 4)
	{
		cout << cnt << endl;
		cout << "Error: Graph contains a cycle!" << endl;
	}

	return toRet;
}

int main()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			matrix[i][j] = false;

	ON term1(0);
	gates.push_back(&term1);

	ON term2(1);
	gates.push_back(&term2);

	XOR sum (&term1, &term2, 2);
	gates.push_back(&sum);
	
	AND carry (&term1, &term2, 3);
	gates.push_back(&carry);

	//Term1 is adjacent to sum
	matrix[0][2] = true;
	//Term2 is adjacent to sum
	matrix[1][2] = true;


	//Term1 is adjacent to carry
	matrix[0][3] = true;
	//Term2 is adjacent to carry
	matrix[1][3] = true;

	vector<Gate *> order = topoSort();

	for(Gate * g: order)
		g->update();
	
	cout << "Term1 is: " << term1.state << endl;
	cout << "Term2 is: " << term2.state << endl;
	cout << "Sum is: " << sum.state << endl;
	cout << "Carry is: " << carry.state << endl;

}