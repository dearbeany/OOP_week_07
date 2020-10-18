#include <iostream>
#include <stdexcept>

bool funcA() {
	int c;
	std::cout << "input(number) : ";
	std::cin >> c;
	if (c < 10) {
		throw std::out_of_range("Invalid Input!!");
	}
	return true;
}

void main() {
	try {
		funcA();
	}
	catch (std::out_of_range& e) {
		std::cout << "Exception :" << e.what() << std::endl;
	}
}