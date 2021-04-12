#include <list>
#include <string>
#include <iostream>

#include "Parsing.h"
#include"../Structure/Element.h"

Structure::Element Parsing::parse(std::string input) {

	try {
		std::list<std::string> splitedString = Parsing::split(input);

		Parsing::validate(splitedString);

		return Parsing::makeTree(std::begin(splitedString), std::end(splitedString));
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		throw std::invalid_argument("Parsing failed");
	}
}
