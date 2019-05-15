#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_
#include <cmath>

template<typename K, typename T >
class priority_queue
{
	struct pq_node_t
	{
		K key;
		T data;

		/*
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
		*/

	};

  public:
	priority_queue(int capcity);
	~priority_queue(void);
	T top(void);
	bool empty(void);
	int insert(K key, T value);
	T removeMin(void);
	int size(void);
	void display(void);
	void replaceKey(int location, K new_key);

	void heapify(int index );
	int left(int i){return 2*i;}
	int right(int i){return 2*i+1;}
    int parent( int i){return floor(i/2);}
  private:
	void swap(int idx1, int idx2);
	int _size;
	int _capacity;
	pq_node_t* _heap;
};


template<typename K, typename T >
priority_queue<K,T>::priority_queue(int capacity)
{
	this->_capacity = capacity;
	this->_size = 0;
	this->_heap = new pq_node_t[capacity+1];
}

template<typename K, typename T >
priority_queue<K,T>::~priority_queue()
{
	delete[] this->_heap;
}

template<typename K, typename T >
int priority_queue<K,T>::size(void)
{
	return this->_size;
}

template<typename K, typename T >
bool priority_queue<K,T>::empty()
{
	return (this->_size > 0) ? false : true;
}

template<typename K, typename T >
void priority_queue<K,T>::heapify(int i){
	cout<<"Heapify wywolano dla : "<< i <<endl;
	int l =left(i);
	int r=right(i);
	int sml;
	 if(l<=_size && _heap[l].key<_heap[i].key) sml=l;
	 else sml=i;
	 if(r<=_size &&_heap[r].key<_heap[i].key) sml=r;
	 if(sml!=i){
		 swap(i,sml);
		 heapify(sml);
	 }
}

template<typename K, typename T >
void priority_queue<K,T>::replaceKey(int location, K new_key)
{
	  	_heap[location].key = new_key;
	  	pq_node_t _tmp;
	  	//cout << "_heap[location].key  "<< _heap[location].key << " new_key " << new_key<< endl;
	  while(location>1 &&_heap[location].key< _heap[parent(location)].key ) {
		  _tmp = _heap[parent(location)];
		  cout << "poszlo dla parenta key :   " << _heap[location].key <<" poszlo dla parenta location " <<location << endl;
		  _heap[parent(location)]= _heap[location];
		  _heap[location]=_tmp;
		  location=parent(location);
	  }


}

template<typename K, typename T >
int priority_queue<K,T>::insert(K key, T value)
{
	pq_node_t node;
	node.key = key;
	node.data = value;
	int location;

	if(this->_size < this->_capacity)
	{
		_heap[++_size] = node;
		int idx = _size;
		location=idx;
		while(_heap[idx].key < _heap[idx/2].key && idx/2 != 0)
		{
			location = idx/2;
			swap(idx, idx/2);
			idx = idx/2;
		}
		return location;
	}
	return -1;
}

template<typename K, typename T >
T priority_queue<K,T>::removeMin(void)
{
	if(!empty())
	{
		T node_tmp = _heap[1].data;

		_heap[1] = _heap[_size];
		_size--;
		int idx = 1;
		int sm_child;
		while(2*idx < _size && (_heap[idx].key > _heap[idx*2].key || _heap[idx].key > _heap[2*idx +1].key))
		{
			if(_heap[2*idx].key < _heap[2*idx+1].key)
				sm_child = 2*idx;
			else
				sm_child = 2*idx+1;

			swap(idx, sm_child);
			idx = sm_child;
		}
		return node_tmp;
	}
	return -1;

}

template<typename K, typename T >
void priority_queue<K,T>::swap(int idx1, int idx2)		//Swapping two choosen elements of array
{
	pq_node_t element_tmp = _heap[idx1];
	_heap[idx1] = _heap[idx2];
	_heap[idx2] = element_tmp;
}

template<typename K, typename T >
void priority_queue<K,T>::display(void)
{

	for(int i = 1; i < _size+1; i++)
		cout <<"Location " << i <<" Key: " << _heap[i].key << " Data: " << _heap[i].data << endl;
}

template<typename K, typename T >
T priority_queue<K,T>::top(void)
{
	return _heap[1];
}

#endif /* PRIORITY_QUEUE_HPP_ */
