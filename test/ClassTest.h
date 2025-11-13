#pragma once
#include <vector>

struct Test {
	int x;
};
class Test_class
{
private:
	std::vector<Test> c_test0;
public:
	std::vector<Test> func() {
		c_test0.push_back({ 0 });
		c_test0.push_back({ 1 });
		return c_test0;
	}
};