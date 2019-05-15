#ifndef LIST_LIST_HPP_
#define LIST_LIST_HPP_
#include <iostream>

using namespace std;

template <typename T>
struct dlinklist_node_t
{
	T data;
	struct dlinklist_node_t<T>* next;
	struct dlinklist_node_t<T>* prev;
};

template <typename T>
class dlinklist
{

  public:
	class dlinklist_iterator;

	dlinklist_iterator begin(void) {return dlinklist_iterator(head);}
	dlinklist_iterator end(void)
	{
		if(head == nullptr)
			return dlinklist_iterator(nullptr);
		return dlinklist_iterator(tail->next);
	}



	dlinklist();
	~dlinklist();

	void push_front(T value);
	void push_back(T value);
	void pop_front(void);
	void pop_back(void);

	dlinklist_iterator insert(const dlinklist_iterator& pos, T value)
	{
		dlinklist_node_t<T>* node_cur = pos.node();

        if(node_cur == head)
        	push_front(value);
        else if(node_cur == tail->next)
			push_back(value);
		else
		{
			dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
			node_tmp->data = value;
			node_tmp->next = node_cur->next;
			node_tmp->prev = node_cur;
			node_cur->next = node_tmp;
			node_cur->next->prev = node_tmp;
		}

		this->_size++;
		return pos;
	};


	dlinklist_iterator erase(dlinklist_iterator pos)
	{
		dlinklist_node_t<T>* node_cur = pos.node();

		if(!empty())
		{
			if(node_cur == head)
				pop_front();
			else if(node_cur == tail->next)
				pop_back();
			else
			{
				node_cur->next->prev = node_cur->prev;
				node_cur->prev->next = node_cur->next;
				delete node_cur;
			}
		}
		this->_size--;
		return pos;
	};

	void display_list(){ //display list leci od head do tail jak w stl

		dlinklist_node_t<T> *node_tmp = head;
		for(int i=0;i<_size ;i++){
		cout<<node_tmp->data<<endl;
		node_tmp=node_tmp->next;
		if(node_tmp==nullptr)cout<< "poza lista"<<endl;
		}
	}

	dlinklist_node_t<T>* GetHead() {return this->head;};
	dlinklist_node_t<T>* GetTail() {return this->tail;};


	T front(void);
	T back(void);

	bool empty(void);
	void display(void);
	int size(void);

	class dlinklist_iterator
	{
	  public:
		dlinklist_iterator() : current_node(head) {};
		dlinklist_iterator( dlinklist_node_t<T>* node_tmp) : current_node(node_tmp) {};

		dlinklist_node_t<T>* node() const{return current_node;};

		dlinklist_iterator& operator=(dlinklist_node_t<T>* node_tmp)
		{
			this->current_node = node_tmp;
			return *this;
		}

		dlinklist_iterator& operator++()
		{ // przy takich begin i end curr_node jest
			if(current_node !=nullptr ){
				current_node=current_node->next;//przechodzimy od h do t i jedyny kierunek to jest next
				}
			return *this;
		}


		dlinklist_iterator operator++(int)
		{
			dlinklist_iterator it_tmp = *this;
			++*this;
			return it_tmp;
		}

		dlinklist_iterator& operator--(int)
		{
			if(current_node !=nullptr ){
				current_node=current_node->prev;//przechodzimy od h do t i jedyny kierunek to jest next
				}
			return *this;
		}

		bool operator!=(const dlinklist_iterator& iterator)
		{
			return current_node != iterator.current_node;
		}

		bool operator==(const dlinklist_iterator& iterator)
			{
				return current_node == iterator.current_node;
			}

		T operator*()
		{
			return current_node->data;
		}

	  private:
		dlinklist_node_t<T>* current_node;
	};

  private:
	dlinklist_node_t<T>* head;
	dlinklist_node_t<T>* tail;
	int _size;
};

template <typename T>
dlinklist<T>::dlinklist()
{
	this->_size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
dlinklist<T>::~dlinklist()
{

}


template <typename T>
void dlinklist<T>::push_front(T value)
{
	dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
	node_tmp->data = value;
	node_tmp->prev =nullptr;
	node_tmp->next =nullptr;

	if(head==nullptr)
	{
		head = node_tmp;
		tail = node_tmp;
	}
	else
	{
		head->prev=node_tmp;
		node_tmp->next = head;
		head = node_tmp;
	}

	this->_size++;
}

template <typename T>
void dlinklist<T>::push_back(T value)
{
	dlinklist_node_t<T>* node_tmp = new dlinklist_node_t<T>;
	node_tmp->data = value;
	node_tmp->prev =nullptr;
	node_tmp->next =nullptr;


	if (tail == nullptr)
	{
		head = node_tmp;
		tail = node_tmp;
	}
	else
	{
		tail->next = node_tmp;
		node_tmp->prev = tail;
		tail = node_tmp;

	}

	_size++;
}

template <typename T>
void dlinklist<T>::pop_front(void)
{
	if(!empty())
	{
		dlinklist_node_t<T>* node_tmp = head;

		if(head == tail)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			head = head->next;
			head->prev = nullptr;
		}

		delete node_tmp;
		_size--;
	}
}

template<typename T>
void dlinklist<T>::pop_back(void)
{
	if(!empty())
	{
		dlinklist_node_t<T>* node_tmp = tail;

		if(tail == head)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			tail = tail->prev;
			tail->prev = nullptr;
		}

		delete node_tmp;
		_size--;
	}
}

template <typename T>
T dlinklist<T>::front(void) {return head->data;}

template <typename T>
T dlinklist<T>::back(void) {return tail->head;}

template <typename T>
bool dlinklist<T>::empty(void)
{
	if(this->_size > 0)
		return false;
	return true;

}

template <typename T>
int dlinklist<T>::size(void)
{
	return this->_size;
}


#endif /* LIST_LIST_HPP_ */
