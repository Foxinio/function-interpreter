#include <iostream>
#include <vector>
#include <memory>
#include <functional>

class Class {
public:
	int prop;
	int prop2;

	Class(int prop1, int prop2) : prop(prop1), prop2(prop2) { }
	Class() : prop(0), prop2(0) { }

};

Class Constructor(std::function<Class()> function) {
	return function();
}

int main() {
	using namespace std;

	auto var = Constructor(Class::);

	std::cout << "Hello World!\n";
}