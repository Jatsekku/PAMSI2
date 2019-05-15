#ifndef MATRIX_MATRIX_HPP_
#define MATRIX_MATRIX_HPP_
#include <iostream>

template <typename T>
class Matrix
{
  private:
	T * _array;
	int n_curr;

  public:
	T operator()(int x, int y ) const {return _array[x + n_curr*y];};
	T& operator()(int x, int y) 	  {return _array[x + n_curr*y];};
	T* data();
	Matrix();
	~Matrix(void);
	int size(void);
	void resize(int N);

	void display();
};

template<typename T >
Matrix<T>::Matrix()
{
	this->n_curr = 3;

	_array = new T[n_curr * n_curr];
	for(int xy  = 0; xy < n_curr*n_curr; xy++)
		_array[xy] = 0;
}

template<typename T>
Matrix<T>::~Matrix(void)
{
	n_curr = 0;
	delete _array;
}

template<typename T>
int Matrix<T>::size(void) { return n_curr;}

template<typename T>
void Matrix<T>::resize(int n)
{
	if(n == n_curr)
		return;

	T* array_tmp = new T[n * n];				//Utworzenie nowej macierzy n*n

	for(int y = 0; y < n; y++)
		for(int x = 0; x < n; x++)
			if(x < n_curr && y < n_curr)
				array_tmp[y*n + x] = _array[y*n_curr + x];
			else
				array_tmp[y*n + x] = 0;

	delete this->_array;
	this->_array = array_tmp;
	this->n_curr= n;


}

template<typename T>
void Matrix<T>::display(void)
{
	cout << "Rozmiar: " <<  this->n_curr << endl;
	for(int y = 0; y < n_curr; y++)
	{
		for(int x = 0; x < n_curr; x++)
			cout << " " << _array[n_curr*y + x] << " ";
		cout << endl;
	}
}


template<typename T>
T* Matrix<T>::data(void)
{
	return this->_array;
}


#endif /* MATRIX_MATRIX_HPP_ */
