/*
 * priority_queue2.hpp
 *
 *  Created on: 13.05.2019
 *      Author: Jatsekku
 */

#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE2_HPP_
#define PRIORITY_QUEUE_PRIORITY_QUEUE2_HPP_

/*
template<typename K, typename T>
struct pq_node_t{
	int key;
	T data;

	pq_node_t(K _key, T _data) : key(_key), data(_data){};
	pq_node_t(){ key = 0; data = 0;};

	bool operator> ( pq_node_t r)
	{
		 return (key > r.key) ? true : false;
	}

	bool operator< ( pq_node_t r)
	{
		 return (key < r.key) ? true : false;
	}

	void display(void)
	{
		std::cout << "Key: " << key << " Data: " << data << endl;
	}
};

template<typename T>
class priority_queue
{
  public:
	priority_queue(int capcity);
	~priority_queue(void);
	T top(void);
	bool empty(void);
	int push(T value);
	void pop(void);
	int size(void);
	void display(void);
	void display_idx(void);
	void replaceKey(int index,T new_key );
	void heapify(int i);
	int left(int i){return 2*i;}
	int right(int i){return 2*i+1;}


	void swap(int idx1, int idx2);
	int _size;
	int _capacity;
	T* _heap;
};

template <typename T>
void priority_queue<T>::display_idx(void){
	for(int i=1; i<_size+1;i++)cout<<" indeks : "<< i << "val : "<< _heap[i]<<endl;
}
template <typename T>
priority_queue<T>::priority_queue(int capacity)
{
	this->_capacity = capacity;
	this->_size = 0; //bylo 0 ale chyba zle
	this->_heap = new T[capacity+1];
}

template <typename T>
priority_queue<T>::~priority_queue()
{
	delete[] this->_heap;
}

template <typename T>
int priority_queue<T>::size(void)
{
	return this->_size;
}

template <typename T>
bool priority_queue<T>::empty()
{
	return (this->_size > 0) ? false : true;
}


template<typename T >
void priority_queue<T>::heapify(int i){
	int l =left(i);
	int r=right(i);
	int sml;
	 if(l<=_size && _heap[l]<_heap[i]) sml=l;
	 else sml=i;
	 if(r<=_size &&_heap[r]<_heap[i]) sml=r;
	 if(sml!=i){
		 swap(i,sml);
		 heapify(sml);
	 }
}

template <typename T>
void priority_queue<T>::replaceKey(int index,T new_val)
{
	int idx=_size;
	int tmp;
	_heap[index] = new_val;

	while(_heap[idx] < _heap[idx/2] && idx/2 != 0)
	{
		tmp = idx/2;
		cout << "PUSH INDEKS PUSHA : "<< tmp<< endl;
		swap(idx, idx/2);
		idx = idx/2;
	}
}

template <typename T>
int priority_queue<T>::push(T value)
{
	int tmp;
	if(this->_size < this->_capacity)
	{
		_heap[++_size] = value;
		int idx = _size;
        tmp=idx;
		while(_heap[idx] < _heap[idx/2] && idx/2 != 0)
		{
			tmp = idx/2;
			cout << "PUSH INDEKS PUSHA : "<< tmp<< endl;
			swap(idx, idx/2);
			idx = idx/2;
		}
	}
	return tmp;
}



template <typename T>
void priority_queue<T>::pop(void)
{
	if(!empty())
	{
		_heap[1] = _heap[_size];
		_size--;
		int idx = 1;
		int sm_child;
		while(2*idx < _size && (_heap[idx] > _heap[idx*2] || _heap[idx] > _heap[2*idx +1]))
		{
			if(_heap[2*idx] < _heap[2*idx+1])
				sm_child = 2*idx;
			else
				sm_child = 2*idx+1;

			swap(idx, sm_child);
			idx = sm_child;
		}
	}
}

template <typename T>
void priority_queue<T>::swap(int idx1, int idx2)		//Swapping two choosen elements of array
{
	T element_tmp = _heap[idx1];
	_heap[idx1] = _heap[idx2];
	_heap[idx2] = element_tmp;
}

template <typename T>
void priority_queue<T>::display(void)
{
	std::cout << "rozmiar: " << _size << endl;
	for(int i = 1; i < _size+1; i++)
		_heap[i].display();
}

template <typename T>
T priority_queue<T>::top(void)
{
	return _heap[1];
}

*/
#endif /* PRIORITY_QUEUE_PRIORITY_QUEUE2_HPP_ */
