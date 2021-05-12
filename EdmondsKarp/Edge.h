#pragma once
#pragma once
#include <iostream>
using namespace std;
template <class name_type, class weight_type>
class Edge
{
	name_type from; // name of the vertex from
	name_type to; // name of the vertex to
	weight_type flow; // the flow that goes through the edge
	weight_type capacity; // max flow through the edge 
public:
	Edge() 
	{
		from = ' ';
		to = ' ';
		flow = 0;
		capacity = 0;
	}
	Edge(name_type From, name_type To, weight_type Capacity)
	{
		from = From;
		to = To;
		capacity = Capacity;
		flow = 0;
	}
	name_type get_vertex_from() { return from; }
	name_type get_vertex_to() { return to; }
	weight_type get_flow() { return flow; }
	weight_type get_capacity() { return capacity; }
	friend class Graph;
};