/**************************************************************************
	FileName		[ my_vector.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ A Dirty Implement of vector ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#define MAX_SIZE 8

template <class T>
class vector
{
public:
	vector() : _size(0) {
		for (int i = 0; i < MAX_SIZE; ++i)
			_data[i] = T();
	}
	~vector() {};

	bool empty() const { return !_size; }
	size_t size() const { return _size; }

	T& operator [] (size_t i) {
		if (i > _size){
			Serial.print("Error: Vector out of size !!\n");
			return _data[0];
		}
		return _data[i];
	}

	const T& operator [] (size_t i) const {
		if (i > _size){
			Serial.print("Error: Vector out of size !!\n");
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
			Serial.print("Error: Vector out of capacity !!\n");
			return;
		}
	}
	void pop_back() { if(!empty()) _size--; }

	void clear() { _size = 0; }

	void print(){
		Serial.print("[ ");
		for (int i = 0; i < _size; ++i){
			Serial.print("\"");
			Serial.print(_data[i]);
			Serial.print("\" ");
		}
		Serial.print("]\n");
	}

private:
	T		_data[MAX_SIZE];
	size_t	_size;
};