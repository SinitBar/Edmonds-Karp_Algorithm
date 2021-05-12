#pragma once
#pragma once
#include "Edge.h"
#include "Queue.h"
template <class name_type, class weight_type>
class Vertex
{
	name_type name; // name of the vertex
	Vertex* mark; // mark from where came here (empty when not set)
	Queue <Edge<name_type, weight_type>>* edges; // edges that starts from this vertex
public:
	Vertex() 
	{
		name = ' ';
		mark = nullptr;
		edges = new Queue <Edge<name_type, weight_type>>();
	}
	Vertex(name_type Name)
	{
		name = Name;
		mark = nullptr;
		edges = new Queue <Edge<name_type, weight_type>>();
	}
	name_type get_name() { return name; }
	Vertex* get_mark() { return mark; }
	void add_edge(Edge<char, double>* e)
	{
		edges->push(e);
	}
	friend class Graph;
};