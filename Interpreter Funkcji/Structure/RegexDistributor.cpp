#include <string>

std::string ElementRegex() {
	//return "[a-zA-Z0-9\\+\\-/\\(\\)";
}

std::string NumberRegex() {
	return "[[:digit:]]+?(\.[[:digit:]]+?)?";
}

std::string FunctionRegex() {
	return "[[:Fun:]]\([[:Expr:]](,[[:Expr:]])+\)";
}