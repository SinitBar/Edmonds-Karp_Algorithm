#pragma once
#pragma once
#include "Element.h"
template <class Value_Type>
class Queue
{
private:
	Element<Value_Type>* head; // the first in queue, leaves first
	Element<Value_Type>* tail; // the last, new in queue
	void set_head(Element<Value_Type>* new_data) { head->set_data(new_data); }
	void set_tail(Element<Value_Type>* new_data) { tail->set_data(new_data); }
public:

	Queue()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool is_empty() // returns true if queue is empty
	{
		if (tail == nullptr)
			return true;
		return false;
	}
	int size() // return a number of elements in queue
	{
		if (is_empty())
			return 0;
		int size = 1;
		for (Element<Value_Type>* now = tail; now->get_next() != nullptr; now = now->get_next())
			size++;
		return size;
	}
	Element<Value_Type>* top() // to know who will leave first
	{
		return head;
	}

	Element<Value_Type>* get_tail() // to know who is the last
	{
		return tail;
	}

	void push(Value_Type* data) // to add in the end of the queue the element with key-data and return it to user
	{
		Element<Value_Type>* new_element = new Element<Value_Type>(data);
		if (is_empty())
			head = tail = new_element;
		else
		{
			new_element->set_next(tail);
			tail = new_element;
		}
	}

	void push_front(Value_Type* data)
	{
		Element<Value_Type>* new_element = new Element<Value_Type>(data);
		if (is_empty())
			head = tail = new_element;
		else
		{
			head->set_next(new_element);
			head = new_element;
		}
	}

	Element<Value_Type>* pop() // to delete first in queue and return it to user
	{
		if (is_empty())
			throw out_of_range("the queue is empty");
		Element<Value_Type>* to_delete(head);
		if (size() == 1)
		{
			head = tail = nullptr;
		}
		else
		{
			for (Element<Value_Type>* now(tail); now->get_next() != nullptr; now = now->get_next())
				head = now;
			head->next = nullptr;
		}
		return to_delete;
	}

	~Queue()
	{
		while (!is_empty())
			pop();
	}
};
