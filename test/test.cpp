#include <iostream>
#include <vector>
#include "ClassTest.h"



void func(const std::vector<Test> t1)
{
	for (auto it = t1.begin(); it != t1.end(); ++it)
	{
		std::cout << it->x << std::endl;
	}
}

int main()
{
	Test_class c_t;

	func(c_t.func());

}