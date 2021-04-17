#include <list>
#include <string>
#include <iostream>

#include "Parsing.h"
#include"../Structure/Element.h"

Structure::Element Parsing::parse(std::string input) {
	if (input.length() == 0) {
		using std::string_literals::operator""s;
		throw std::invalid_argument("Parsing failed: input can't be empty.");
	}

	try {
		std::list<std::string> splitedString = Parsing::split(input);

		auto validList = Parsing::validate(splitedString);

		return Parsing::makeTree(std::begin(validList), std::end(validList));
	}
	catch (std::exception& e) {
		using std::string_literals::operator""s;
		throw std::invalid_argument("Parsing failed: "s + e.what());
	}
}
