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

template <class T>
class vector
{
public:
	vector() : _size(0) {
		// super dirty
		_data_1 = T();
		_data_2 = T();
		_data_3 = T();
		_data_4 = T();
	}
	~vector() {};

	bool empty() const { return !_size; }
	size_t size() const { return _size; }

	T& operator [] (size_t i) {
		switch(i) {
			case 0:
				return _data_1;
			case 1:
				return _data_2;
			case 2:
				return _data_3;
			case 3:
				return _data_4;
			default:
				#ifdef Cpp_Mode
					cout << "Warning: vector out of range" << endl;
				#else
					Serial.println("Warning: vector out of range");
				#endif

				return _data_4;
		}
	}
	const T& operator [] (size_t i) const {
		switch(i) {
			case 0:
				return _data_1;
			case 1:
				return _data_2;
			case 2:
				return _data_3;
			case 3:
				return _data_4;
			default:
				#ifdef Cpp_Mode
					cout << "Warning: vector out of range" << endl;
				#else
					Serial.println("Warning: vector out of range");
				#endif
				
				return _data_4;
		}
	}

	vector<T> operator = (const vector<T>& v){
		_data_1 = v._data_1;
		_data_2 = v._data_2;
		_data_3 = v._data_3;
		_data_4 = v._data_4;
		_size = v._size;

		return *this;
	}

	void push_back(const T& x) {
		switch(_size){
			case 0:
				_data_1 = x;
				break;
			case 1:
				_data_2 = x;
				break;
			case 2:
				_data_3 = x;
				break;
			case 3:
				_data_4 = x;
				break;
			default:
				#ifdef Cpp_Mode
					cout << "Warning: vector out of range" << endl;
				#else
					Serial.println("Warning: vector out of range");
				#endif

				return;
		}
		_size++;
	}
	void pop_back() { if(!empty()) _size--; }

	void clear() { _size = 0; }

	void print(){
		#ifdef Cpp_Mode
			cout << "[ ";
			if(_size >= 1)
				cout << _data_1;
			if(_size >= 2)
				cout << ", " << _data_2;
			if(_size >= 3)
				cout << ", " << _data_3;
			if(_size >= 4)
				cout << ", " << _data_4;
			cout << " ]" << endl;
		#else
			Serial.print("[ ");
			if(_size >= 1){
				Serial.print(_data_1);
			}
			if(_size >= 2){
				Serial.print(", ");
				Serial.print(_data_2);
			}
			if(_size >= 3){
				Serial.print(", ");
				Serial.print(_data_3);
			}
			if(_size >= 4){
				Serial.print(", ");
				Serial.print(_data_4);
			}
			Serial.print(" ]\n");
		#endif
	}

private:
	T 		_data_1;
	T 		_data_2;
	T 		_data_3;
	T 		_data_4;
	size_t	_size;       // number of valid elements
};