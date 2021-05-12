#pragma once
#pragma once
#include "Vertex.h"
#include <fstream>

class Graph
{
	Queue<Vertex<char, double>>* V; // list of vertexes, every vertex has a list of edges starting from it

public:
	Graph();

	void clear_marks(); // clear all marks that have vertexes from V

	void clear_flows(); // clear all flows in graph (make every flow = 0)

	Element<Vertex<char, double>>* search_vertex_on_name(char); // returns vertex from V with data name

	Element<Edge<char, double>>* search_edge(Vertex<char, double>*, char); // searches edge on vertexes from and to

	void read_from_file(string); // fill V and E from file with filename

	void print(string); // prints nodes with flow/capacity to the file with filename

	double edmonds_karp(); // returns max flow through the graph from 'S' to 'T'
};