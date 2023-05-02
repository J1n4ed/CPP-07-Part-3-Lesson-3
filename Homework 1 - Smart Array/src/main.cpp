// main.cpp

/*
  02.05.2023
  ����� 3 - ����������� ���������������� �� C++
  ������� 3 - ��������� ���� �������. RAII
  ������ 1 - ����� ������
  CPP-07
  ������� ����
*/

/*
��������� ��� ���-�� �������� ���� ������� � ����������� ����� �������

�����:

src/dynarr.cpp
headers/dynarr.h
*/

// INCLUDES

#include "..\headers\dynarr.h"
#include <iostream>

int main(int argc, char** argv)
{
	// TERMINAL SETTINGS

	setlocale(LC_ALL, "Russian");

	// VARIABLES

	int actual_size = 1;
	int logical_size = 0;

	// BODY

	try
	{
		// actual_size ������ ���� �� ������� ���� 1 � ������ ��� ����� logical_size
		jinx::Dynarr arr(logical_size, actual_size);

		/*
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		*/

		// ������������� � Dynarr �������� ����� append(int)

		arr.append(1);
		arr.append(4);
		arr.append(155);
		arr.append(14);
		arr.append(15);

		std::cout << "element 1: " << arr.get_element(1) << "\n\nwhole array:\n";

		arr.simple_print();

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

