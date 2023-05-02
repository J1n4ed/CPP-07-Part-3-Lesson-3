#pragma once

#include <iostream>
#include <string>

namespace jinx
{

class Dynarr
{
public:

	// PUBLIC PART

  // simple print
  void simple_print() const; 

  // get actual length
  int fullLength() const;

  // get logical length
  int length() const;

  // add to tail
  void append(int);

  // delete first element
  void cut_head();

  // access element (for pointers)
  int & get_element(int index);

  // ---- interators

  class iterator 
  {
  public:
	  iterator(int * ptr) : ptr(ptr) {}
	  iterator operator++() { ++ptr; return *this; }
	  bool operator!=(const iterator& other) const { return ptr != other.ptr; }
	  const int & operator*() const { return *ptr; }
  private:
	  int * ptr;
  };

  iterator begin() const { return iterator(arr); }
  iterator end() const { return iterator(arr + arr_logical_length); }

// Overloads

int & operator[](int index);

void operator=(Dynarr& other_arr);

// Constructor

Dynarr() = delete;

Dynarr(int logical_size, int actual_size);

// Destructor

~Dynarr();

protected:

	// PROTECTED PART

	// none yet

private:

	// PRIVATE PART

  int * arr = nullptr;
  int arr_logical_length = -1;
  int arr_actual_length = -1;
}; // END OF DYNARR CLASS

// ------------------------------------------------------------------------

// Func (?)

void print_dynamic_array(Dynarr * arr, int logical_size, int actual_size);

// EXCEPTIONS
class ArrayIndexOutOfBounds : public std::exception
{
public:
		const char* what() const noexcept override
		{
			return "\n > ОШИБКА: индекс элемента за пределами массива!";
		}
};

class ArrayIsNullPtr : public std::exception
{
public:
		const char* what() const noexcept override
		{
			return "\n > ОШИБКА: массив не существует!";
		}
};

class LogicalToActualSizeMismatch : public std::exception
{
public:
		const char* what() const noexcept override
		{
			return "\n > ОШИБКА: действительный размер не соотсветствует логическому!";
		}
};

class LogicalOrActualSizeLessThenZero : public std::exception
{
public:
		const char* what() const noexcept override
		{
			return "\n > ОШИБКА: логический или фактический размеры меньше нуля!";
		}
};

} // END OF JINX NAMESPACE