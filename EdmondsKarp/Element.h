#pragma once
#pragma once
#include <iostream>
using namespace std;
template <class Value_Type>
class Element
{
	Element<Value_Type>* next;
	Value_Type* data;
	void set_next(Element<Value_Type>* new_element) { next = new_element; }
	void set_data(Value_Type* new_data) { data = new_data; }
	Element()
	{
		next = nullptr;
		data = nullptr;
	}
public:
	Element(Value_Type* data)
	{
		set_data(data);
		next = nullptr;
	}
	Element<Value_Type>* get_next() { return next; }
	Value_Type* get_data() { return data; }
	~Element() {}
	template <class Value_Type> friend class Queue;
	friend class Graph;
};