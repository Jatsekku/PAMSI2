#ifndef LIST_SLIST_HPP_
#define LIST_SLIST_HPP_
#include <iostream>

using namespace std;




template <typename T>
struct slinklist_node_t
{
	T data;
	struct slinklist_node_t<T>* next;
};

template <typename T>
class slinklist
{

  public:
	class slinklist_iterator;

	slinklist_iterator begin(){return slinklist_iterator(head);}
	slinklist_iterator end(){return slinklist_iterator(nullptr);}

	slinklist();
	void push_front(T value);
	void pop_front(void);
	T front(void);
	bool empty(void);
	void display(void);
	T acces(int pos);
	int size(void);

	class slinklist_iterator
	{
	  public:
		slinklist_iterator() : current_node(head) {};
		slinklist_iterator(const slinklist_node_t<T>* node_tmp) : current_node(node_tmp) {};

		slinklist_iterator& operator=(slinklist_node_t<T>* node_tmp)
		{
			this->current_node = node_tmp;
			return *this;
		}

		slinklist_iterator& operator++()
		{
			if(current_node != nullptr)
				current_node=current_node->next;
			return *this;
		}


		slinklist_iterator operator++(int)
		{
			slinklist_iterator it_tmp = *this;
			++*this;
			return it_tmp;
		}

		bool operator!=(const slinklist_iterator& iterator)
		{
			return current_node != iterator.current_node;
		}

		T operator*()
		{
			return current_node->data;
		}

	  private:
		const slinklist_node_t<T>* current_node;
	};

  private:
	slinklist_node_t<T> *head;
	int _size;
};

template <typename T>
slinklist<T>::slinklist()
{
	this->_size = 0;
	this->head = nullptr;
}

template <typename T>
void slinklist<T>::push_front(T value)
{
	slinklist_node_t<T>* node = new slinklist_node_t<T>;
	node->data = value;
	node->next = this->head;
	this->head = node;
	this->_size++;
}

template <typename T>
void slinklist<T>::pop_front(void)
{
	slinklist_node_t<T>* node = head->next;
	delete head;
	this->head = node;

	_size--;
}

template <typename T>
T slinklist<T>::front(void)
{
	return head->data;
}

template <typename T>
T slinklist<T>::acces(int pos)
{
	slinklist_node_t<T>* node_tmp = this->head;
	while(pos--)
	{
		if(node_tmp != nullptr)
			node_tmp = node_tmp->next;
	}
	return node_tmp->data;
}

template <typename T>
int slinklist<T>::size(void)
{
	return this->_size;
}


#endif /* LIST_SLIST_HPP_ */
