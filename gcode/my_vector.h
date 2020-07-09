/**************************************************************************
	FileName		[ my_vector.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ A Simple Implement of stl::vector ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

template <class T>
class vector
{
public:
	vector() : _data(0), _size(0), _capacity(0) {};
	~vector() { delete []_data; }

	bool empty() const { return !_size; }
	size_t size() const { return _size; }

	T& operator [] (size_t i) { return _data[i]; }
	const T& operator [] (size_t i) const { return _data[i]; }

	void push_back(const T& x) {
		if(_size == _capacity)
			expand();
		_data[_size] = x;
		_size++;
	}
	void pop_back() { if(!empty()) _size--; }

	void clear() { _size = 0; }

private:
	T*				_data;
	size_t			_size;       // number of valid elements
	size_t			_capacity;   // max number of elements

	// [OPTIONAL TODO] Helper functions; called by public member functions
	void expand() {
		if(_capacity == 0){
			_capacity++;
			_data = new T [_capacity];
		}
		else{
			_capacity *= 2;
			auto new_data = new T [_capacity];
			for(size_t i = 0; i < _capacity/2; i++)
				new_data[i] = _data[i];
			auto tmp = _data;
			_data = new_data;
			delete [] tmp;
		}
	}

};