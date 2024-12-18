#include <iostream>

#include "task.h"

int main() {
	binary_int a(8);
	binary_int b(10);
	std::cout << a + b << std::endl;
	std::cout << a - b << std::endl;
	std::cout << a * b << std::endl;

	binary_int x(50);
	std::cout << ++x << std::endl;
	std::cout << x++ << std::endl;
	std::cout << --x << std::endl;
	std::cout << x-- << std::endl;

	binary_int y(-2);
	std::cout << (y << 1) << std::endl;
	std::cout << (y >> 1) << std::endl;

	std::cout << binary_int(-15) << std::endl;

	auto split = binary_int(-15).split();
	std::cout << split.first << " " << split.second << std::endl;
}