#include "Graph.h"

char source = 'S', target = 'T';

Graph::Graph() { V = new Queue<Vertex<char, double>>(); }

void Graph::clear_marks() // clear all marks that have vertexes from V
{
	Element<Vertex<char, double>>* v = V->get_tail();
	while (v != nullptr)
	{
		v->get_data()->mark = nullptr;
		v = v->get_next();
	}
}

void Graph::clear_flows() // clear all flows in graph (make every flow = 0)
{
	Element<Vertex<char, double>>* v = V->get_tail();
	while (v != nullptr)
	{
		Element<Edge<char, double>>* e = v->get_data()->edges->get_tail();
		while (e != nullptr)
		{
			e->get_data()->flow = 0;
			e = e->get_next();
		}
		v = v->get_next();
	}
}

Element<Vertex<char, double>>* Graph::search_vertex_on_name(char Name) // returns vertex from V with data name
{
	if (!V->is_empty())
	{
		Element<Vertex<char, double>>* current(V->get_tail());
		while (current != nullptr)
		{
			Vertex<char, double>* v = current->get_data();
			if (v->get_name() == Name)
				return current;
			current = current->get_next();
		}
	}
	return nullptr; // returns null when vertex doesn't exist
}

Element<Edge<char, double>>* Graph::search_edge(Vertex<char, double>* from, char to) // searches edge on vertexes
{
	Element<Edge<char, double>>* current = from->edges->get_tail();
	while (current != nullptr)
	{
		if (current->get_data()->get_vertex_to() == to)
			return current;
		current = current->get_next();
	}
	throw out_of_range("searching edge doesn't exist");
}

void Graph::read_from_file(string filename) // fill V and E from file
{
	ifstream in(filename);
	if (!in.is_open())
		throw out_of_range("data file couldn't be open");
	while (in.peek() != EOF)
	{
		char v_from, v_to;
		double max_flow;
		in >> v_from >> v_to >> max_flow;
		Edge<char, double>* e = new Edge<char, double>(v_from, v_to, max_flow);
		Element<Vertex<char, double>>* elem = search_vertex_on_name(v_from);

		if (elem == nullptr)
		{
			Vertex<char, double>* v = new Vertex<char, double>(v_from);
			v->add_edge(e);
			V->push_front(v);
		}
		else
		{
			Vertex<char, double>* v = elem->get_data();
			v->add_edge(e);
		}
		elem = search_vertex_on_name(v_to);
		if (elem == nullptr)
		{
			Vertex<char, double>* v = new Vertex<char, double>(v_to);
			V->push_front(v);
		}
	}
	in.close();
}

void Graph::print(string filename) // prints nodes with flow/capacity to the file with filename
{
	ofstream out(filename);
	if (!out.is_open())
		throw out_of_range("output file couldn't be open");

	Element<Vertex<char, double>>* v = V->get_tail();
	while (v != nullptr)
	{
		Element<Edge<char, double>>* e = v->get_data()->edges->get_tail();
		while (e != nullptr)
		{
			out << e->get_data()->get_vertex_from() << " " << e->get_data()->get_vertex_to() << " " << e->get_data()->get_flow() << "/" << e->get_data()->get_capacity() << endl;
			e = e->get_next();
		}
		v = v->get_next();
	}
	out.close();
}

double Graph::edmonds_karp() // returns max flow through the graph from 'S' to 'T'
{ // changes only flows on edges in the original graph, to clear flows use clear_flows() function
	double max_flow = 0;
	Queue<Vertex<char, double>>* queue = new Queue<Vertex<char, double>>();
	Element<Vertex<char, double>>* S = search_vertex_on_name(source); // source vertex
	queue->push(S->get_data()); // vertex is always the same and changing but elements containing this vertex are not similar
	Element<Vertex<char, double>>* current_vertex = new Element<Vertex<char, double>>();
	while (!queue->is_empty()) // when empty path doesn't exist
	{
		current_vertex = queue->pop();
		Element<Edge<char, double>>* current_edge = current_vertex->get_data()->edges->get_tail();
		while (current_edge != nullptr) // go through edges of current vertex
		{
			if (current_edge->get_data()->get_capacity() - current_edge->get_data()->get_flow() > 0)
			{ // if there is a possibility to push some flow through this edge
				Element<Vertex<char, double>>* adding_vertex = search_vertex_on_name(current_edge->get_data()->get_vertex_to()); // new to queue
				if (adding_vertex->get_data()->get_mark() == nullptr) // if it already has a mark we should save it
				{ // it has no mark yet
					adding_vertex->get_data()->mark = current_vertex->get_data();
					queue->push(adding_vertex->get_data());
					if (adding_vertex->get_data()->get_name() == target) // found min path
					{
						Queue<Edge<char, double>>* path = new Queue<Edge<char, double>>();
						double current_flow = current_edge->get_data()->get_capacity() - current_edge->get_data()->get_flow();

						while (current_vertex->get_data() != nullptr) // while the edge with source not mentioned
						{
							path->push(current_edge->get_data());
							if (current_flow > current_edge->get_data()->get_capacity() - current_edge->get_data()->get_flow())
								current_flow = current_edge->get_data()->get_capacity() - current_edge->get_data()->get_flow();
							// current edge is the edge from current vertex to adding vertex
							if (current_vertex->get_data()->get_name() == source)
								break;
							adding_vertex = current_vertex;
							current_vertex = search_vertex_on_name(current_vertex->get_data()->get_mark()->get_name());
							current_edge = search_edge(current_vertex->get_data(), adding_vertex->get_data()->get_name()); // go to previous edge in the path
						}
						max_flow += current_flow;
						while (!path->is_empty()) // change flow through chosen path
						{
							Edge<char, double>* e = path->pop()->get_data();
							e->flow = e->flow + current_flow;
						}
						clear_marks(); // clear all marks, refresh graph
						queue->~Queue(); // clear queue
						queue->push(S->get_data()); // go back to initial position
						break;
					}
				} // it has mark and to save it we go to the next vertex because this path is obviously longer
			}
			current_edge = current_edge->get_next();
		}

	}
	clear_marks();
	return max_flow;
}