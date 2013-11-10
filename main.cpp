#include <vector>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>

#include "headers/gates.h"

/*The following function is a modification of a function written by the
 *proceeding author.*/

// Sean Szumlanski
// COP 3503, Fall 2013

/*The modifications changed the nodes to be of type gate rather than int,
 *dynamically sized arrays, switching to C++ from Java, and returning a sorted
 *vector rather than printing the order.*/

class Clock : public Gate
{
	public:
		bool threadingSafety;
		Clock(float hertz)
		{
			frequency = hertz;
			state = false;
			threadingSafety = state;
		}

		void update()
		{
			;
		}

		void start()
		{
			std::thread t(&Clock::cycle, this);
			t.detach();
		}
	private:
		void cycle()
		{
			int arg = int(1000.0/frequency);
			std::chrono::milliseconds dura( arg );
			while(true)
			{
				std::this_thread::sleep_for( dura );
				state = !state;
				threadingSafety = state;
			}
		}

		float frequency;

};

class TQ : public Gate
{
	public:
		bool * in;
		bool * clk;
		bool safety;
		bool stateNext;
		bool seenClock;
		TQ(Gate * in, Clock * clk)
		{
			safety = false;
			this->in = &(in->state);
			this->clk = &(clk->state);
			matrix[in->num][num] = true;
			matrix[clk->num][num] = true;
			state = false;
			stateNext = false;
			seenClock = false;
		}
		void update()
		{
			if(safety)
			{
				if(!seenClock)
				{
					state = stateNext;
					stateNext = state ^ (*in);
					seenClock = true;
				}
			}
			else
			{
				seenClock = false;
			}
		}

};

vector <Gate *> topoSort()
{
	vector <Gate *> toRet;
	vector <int> incoming;
	incoming.resize(matrix.size());
	
	for(unsigned int i = 0; i < incoming.size(); ++i)
		incoming[i] = 0;
	
	int cnt = 0;

	// Count the number of incoming edges incident to each vertex. For sparse
	// graphs, this could be made more efficient by using an adjacency list.

	for(unsigned int i = 0; i < matrix.size(); ++i)
		for(unsigned int j = 0; j < matrix[i].size(); ++j)
			if(matrix[i][j])
				++incoming[j];

	queue <Gate *> q;

	// Any vertex with zero incoming edges is ready to be visited, so add it to
	// the queue.
	for (int i = 0; i < matrix.size(); i++)
		if (incoming[i] == 0)
			q.push(gates[i]);

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
		for (int i = 0; i < matrix.size(); i++)
			if (matrix[node->num][i] && --incoming[i] == 0)
				q.push(gates[i]);
	}

	// If we pass out of the loop without including each vertex in our
	// topological sort, we must have a cycle in the graph.
	if (cnt != matrix.size())
		cout << "Error: Graph contains a cycle!" << endl;

	return toRet;
}

void init()
{
	//Read in each line of input

	//Initialize each gate per line

	//Example input line:
	//AND and3 : on1 on2
}

int main()
{
	ON on1;
	Clock clk(3);
	TQ tq1(&on1, &clk);
	TQ tq2(&tq1, &clk);

	AND and1(&tq1, &tq2);
	
	TQ tq3(&and1, &clk);
	
	AND and2(&tq3, &and1);
	
	TQ tq4(&and2, &clk);

	/*ON term1;

	ON term2;

	XOR sum (&term1, &term2);
	
	AND carry (&term1, &term2);*/

	vector<Gate *> order = topoSort();
	
	/*cout << "Term1 is: " << term1.state << endl;
	cout << "Term2 is: " << term2.state << endl;
	cout << "Sum is: " << sum.state << endl;
	cout << "Carry is: " << carry.state << endl;*/

	clk.start();

	int num = -1;

	while(true)
	{
		int newNum = int(tq1.state) + int(tq2.state)*2 + int(tq3.state)*4 + int(tq4.state)*8;
		
		if(newNum != num)
		{
			cout << "Num changed to: " << newNum << endl;
			num = newNum;
		}

		bool safetyDance = clk.threadingSafety;

		tq1.safety = safetyDance;
		tq2.safety = safetyDance;
		tq3.safety = safetyDance;
		tq4.safety = safetyDance;

		for(Gate * g: order)
			g->update();
	}

	return 0;
}