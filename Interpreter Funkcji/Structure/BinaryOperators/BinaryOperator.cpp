#include <stdexcept>

#include "BinaryOperator.h"
#include "Multiplication.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Division.h"
#include "Exponential.h"

namespace Structure {

	double BinaryOperator::evaluate(VariablePackage package) {
		throw std::invalid_argument("Call to base class without further context.");
	}
	std::string BinaryOperator::to_string() {
		throw std::invalid_argument("Call to base class without further context.");
	}

	const std::vector<std::string> BinaryOperator::allBinaryOperators{
		"+", "-", "*", "/", "^", "%"
	};

	std::int32_t BinaryOperator::priorityFromString(std::string input) {
		if (input[0] == '-' || input[0] == '+') {
			return Addition;
		}
		else if (input[0] == '*' || input[0] == '/') {
			return Multiplication;
		}
		else if (input[0] == '^') {
			return Exponential;
		}
		throw std::invalid_argument("Unknown Operation");
	}

	BinaryOperator BinaryOperator::getBinaryOperator(std::string binaryOperator, Element first, Element second) {
		switch (binaryOperator[0]) {
		case '*':
			return Structure::Multiplication(first, second);
		case '/':
			return Structure::Division(first, second);
		case '-':
			return Structure::Subtraction(first, second);
		case '+':
			return Structure::Addition(first, second);
		case '^':
			return Structure::Exponential(first, second);
		default:
			throw std::invalid_argument("Not implemented");
		}
	}
}

