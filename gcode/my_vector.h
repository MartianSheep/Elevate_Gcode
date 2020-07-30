/**************************************************************************
	FileName		[ my_vector.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ A Simple Implement of stl::vector ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

// #define Cpp_Mode

#ifdef Cpp_Mode
	#include <iostream>
	using namespace std;
#endif

#define MAX_SIZE 20

void printing(const char msg[]){
	#ifdef Cpp_Mode
		cout << msg;
	#else
		Serial.print(msg);
	#endif
}

template <class T>
class vector
{
public:
	vector() : _size(0) {
		// super dirty
		for (int i = 0; i < MAX_SIZE; ++i)
			_data[i] = T();
	}
	~vector() {};

	bool empty() const { return !_size; }
	size_t size() const { return _size; }

	T& operator [] (size_t i) {
		if (i > _size){
			printing("Error: Vector out of size !!\n");
			return _data[0];
		}
		return _data[i];
	}

	const T& operator [] (size_t i) const {
		if (i > _size){
			printing("Error: Vector out of size !!\n");
			return _data[0];
		}
		return _data[i];
	}

	vector<T> operator = (const vector<T>& v){
		_size = v._size;

		for(int i = 0; i < _size; ++i)
			_data[i] = v._data[i];

		return *this;
	}

	void push_back(const T& x) {
		if(_size < MAX_SIZE){
			_data[_size] = x;
			++_size;
		}
		else{
			printing("Error: Vector out of capacity !!\n");
			return;
		}
	}
	void pop_back() { if(!empty()) _size--; }

	void clear() { _size = 0; }

	void print(){
		printing("[ ");
		for (int i = 0; i < _size; ++i){
			printing("\"");
			#ifdef Cpp_Mode
				cout << _data[i];
			#else
				Serial.print(_data[i]);
			#endif
			printing("\" ");
		}

		printing("]\n");
	}

private:
	T		_data[MAX_SIZE];
	size_t	_size;       // number of valid elements
};