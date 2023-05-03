#include "../headers/dynarr.h"

// Overloads

int & jinx::Dynarr::operator[](int index) 
{
  if ((index <= arr_logical_length) && (index >= 0)) {
    if (arr != nullptr)
      return arr[index];
    else {
      throw jinx::ArrayIsNullPtr();
    }
  }
  throw jinx::ArrayIndexOutOfBounds();
}

jinx::Dynarr & jinx::Dynarr::operator=(jinx::Dynarr & other_arr)
{
    if (this != &other_arr) 
    {

        if (this->length() < other_arr.length())
        {
            delete[] this->arr;
            this->arr_actual_length = other_arr.arr_actual_length;
            this->arr_logical_length = other_arr.arr_logical_length;
            arr = new int[arr_actual_length] {0};

            for (int i = 0; i < arr_logical_length; ++i)
            {
                this->arr[i] = other_arr[i];
            }
        }
        else if (this->length() > other_arr.length())
        {
            for (int i = 0; i < other_arr.length(); ++i)
            {
                this->arr[i] = other_arr[i];
            }
        }

    } // END OF if this != &other_arr

    return *this;
}

// Constructor

jinx::Dynarr::Dynarr(const jinx::Dynarr & other_arr)
{
    arr_logical_length = other_arr.length();
    arr_actual_length = other_arr.fullLength();
    this->arr = new int[arr_logical_length] {0};    

    for (int i = 0; i < arr_logical_length; ++i)
    {
        this->arr[i] = other_arr.arr[i];
    }
}

jinx::Dynarr::Dynarr(int logical_size, int actual_size) {
  if (actual_size < logical_size) 
  {
    throw jinx::LogicalToActualSizeMismatch();
  } 
  else if (actual_size < 0 || logical_size < 0)
  {
    throw jinx::LogicalOrActualSizeLessThenZero();
  }
  else 
  {
    arr = new int[actual_size]{0};
    arr_logical_length = logical_size;
    arr_actual_length = actual_size;
  }
}

// Destructor

jinx::Dynarr::~Dynarr() {
  delete[] arr;
  arr = nullptr;
}

//  simple class print
void jinx::Dynarr::simple_print() const
  {
    for (int i = 0; i < arr_actual_length; ++i)
      {
        if (i < arr_logical_length)
        {
          std::cout << arr[i];
        }
        else
        {
          std::cout << '_';
        }

        if ( (i < arr_actual_length - 1) && (arr_actual_length > 0) )
        {
          std::cout << '\t';
        }

        if (i % 10 == 0 && i != 0 && i != 1)
          std::cout << '\n';
      }
  }

// get actual length
int jinx::Dynarr::fullLength() const
{
  return arr_actual_length;
}

  // get logical length
int jinx::Dynarr::length() const
{
  return arr_logical_length;
}

// add to tail
void jinx::Dynarr::append(int num)
{
  /*
Если логический размер массива равен его фактическому размеру, тогда создаётся новый массив размером в 2 раза больше. В него перекладываются элементы из старого массива вместе с новым элементом в конце. Фактический и логический размеры массива изменяют своё значение. Логический размер увеличивается на единицу, фактический размер увеличивается в два раза, старый массив уничтожается. Далее программа должна работать уже с новым массивом.
  */

  if (arr_logical_length == arr_actual_length)
  {
    int * tmp = new int[arr_actual_length];
    
    for (int i = 0; i < arr_logical_length; ++i)
      {
        tmp[i] = arr[i];
      }
    
    delete [] arr;

    // Количество докидываемых элементов
    
    if (arr_actual_length < 10)
      arr_actual_length *= 2;
    if (arr_actual_length >= 10 && arr_actual_length < 100)
      arr_actual_length += 10;
    if (arr_actual_length >= 100 && arr_actual_length < 1000)
      arr_actual_length += 100;
    if (arr_actual_length >= 1000 && arr_actual_length < 10000)
      arr_actual_length += 1000;
    if (arr_actual_length >= 10000)
      arr_actual_length += 5000;
      
    arr = new int[arr_actual_length];
    
    for (int i = 0; i < arr_logical_length; ++i)
      {
        arr[i] = tmp[i];
      }
    
    delete [] tmp;
    tmp = nullptr;    
  }

  arr[arr_logical_length] = num;
  arr_logical_length += 1;  
}

// delete first element
void jinx::Dynarr::cut_head()
{

if (arr_logical_length == 0)
{
  // do nothing
}
else
{
  if ( (arr_actual_length / arr_logical_length) < 3 )
  {
    for (int i = 0; i < (arr_logical_length - 1); ++i)
      {
        arr[i] = arr[i+1]; 
      }
    arr_logical_length -= 1;
  }
  else // >= 3
  {
    int * tmp = new int[arr_logical_length];

    for (int i = 0; i < arr_logical_length; ++i)
      {
        tmp[i] = arr[i];
      }
    
    delete [] arr;

    // Количество докидываемых элементов
    
    if (arr_actual_length < 10)
      arr_actual_length = arr_logical_length + 2;
    if (arr_actual_length >= 10 && arr_actual_length < 100)
      arr_actual_length = arr_logical_length + 5;
    if (arr_actual_length >= 100 && arr_actual_length < 1000)
      arr_actual_length = arr_logical_length + 10;
    if (arr_actual_length >= 1000 && arr_actual_length < 10000)
      arr_actual_length = arr_logical_length + 20;
    if (arr_actual_length >= 10000)
      arr_actual_length = arr_logical_length + 40;
      
    arr = new int[arr_actual_length];

    arr_logical_length -= 1;
    
    for (int i = 0; i < arr_logical_length; ++i)
      {
        arr[i] = tmp[i + 1];
      }
    
    delete [] tmp;
    tmp = nullptr;  
    
  }
} 
  
}

void jinx::print_dynamic_array(jinx::Dynarr * arr, int logical_size, int actual_size)
{
  if (logical_size < actual_size)
    if (logical_size > 0)
      arr->simple_print();
}

// access element (for pointers)
int & jinx::Dynarr::get_element(int index)
{
  if ((index <= arr_logical_length) && (index >= 0)) {
    if (arr != nullptr)
      return arr[index];
    else {
      throw jinx::ArrayIsNullPtr();
    }
  }
  throw jinx::ArrayIndexOutOfBounds();
}