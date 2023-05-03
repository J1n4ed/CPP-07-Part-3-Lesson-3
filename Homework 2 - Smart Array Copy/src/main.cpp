// main.cpp

/*
  02.05.2023
  Часть 3 - Продвинутое программирование на C++
  Занятие 3 - Жизненный цикл объекта. RAII
  Задача 2 - Копирование умных массивов
  CPP-07
  Горюнов Илья
*/

/*
Оказалось что что-то подобное было сделано к предыдущему блоку занятий

файлы:

src/dynarr.cpp
headers/dynarr.h

в этой версии дописан итератор и исправлена функция перегрузки =
*/

// INCLUDES

#include "..\headers\dynarr.h"
#include <iostream>
#include <Windows.h>

int main(int argc, char** argv)
{
	// TERMINAL SETTINGS

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// VARIABLES

	int actual_size = 1;
	int logical_size = 0;

	// BODY

	try
	{
		// actual_size должен быть по крайней мере 1 и больше или равен logical_size
		jinx::Dynarr smart_arr(logical_size, actual_size);	

		// Второй массив

		jinx::Dynarr new_arr(logical_size, actual_size);

/*
smart_array arr(5);
arr.add_element(1);
arr.add_element(4);
arr.add_element(155);

smart_array new_array(2);
new_array.add_element(44); 
new_array.add_element(34);

arr = new_array
*/

		smart_arr.append(5);
		smart_arr.append(1);
		smart_arr.append(4);
		smart_arr.append(155);

		new_arr.append(44);
		new_arr.append(34);

		// Print

		std::cout << "array 1:\n";

		for (const int& i : smart_arr)
		{
			std::cout << i << ' ';
		}

		std::cout << "\narray 2:\n";

		for (const int& i : new_arr)
		{
			std::cout << i << ' ';
		}

		// equation

		smart_arr = new_arr;

		// sec print

		std::cout << "\nresult array:\n";

		for (const int& i : smart_arr)
		{
			std::cout << i << ' ';
		}

		// tests for review

		jinx::Dynarr test_arr(new_arr);

		test_arr.append(9);
		test_arr.append(8);
		test_arr.append(7);
		test_arr.append(6);
		test_arr.append(5);
		test_arr.append(4);
		test_arr.append(3);
		test_arr.append(2);
		test_arr.append(1);

		std::cout << "\ntest array:\n";

		for (const int& i : test_arr)
		{
			std::cout << i << ' ';
		}

		// equation

		smart_arr = test_arr;

		std::cout << "\nsmart array after eq:\n";

		for (const int& i : smart_arr)
		{
			std::cout << i << ' ';
		}

		std::cout << std::endl;
	}
	catch (const jinx::ArrayIndexOutOfBounds& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	catch (const jinx::ArrayIsNullPtr& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	catch (const jinx::LogicalToActualSizeMismatch& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	catch (const jinx::LogicalOrActualSizeLessThenZero& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}

	// CLOSE & EXIT

	std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;

} // END OF main()

