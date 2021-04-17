#include "UnaryOperator_pch.h"


namespace Structure {

	double UnaryOperator::evaluate(VariablePackage package) {
		throw std::invalid_argument("Call to base class without further context.");
	}
	std::string UnaryOperator::to_string() {
		throw std::invalid_argument("Call to base class without further context.");
	}

	std::string UnaryOperator::getRegex() {
		std::string result = std::accumulate(
			std::begin(allUnaryOperators),
			std::end(allUnaryOperators),
			std::string(),
			[](std::string init, std::string elem) {
				return init + elem + "|";
			});
		return result.substr(0, result.length() - 1);
	}

	bool UnaryOperator::isUnaryOperator(std::string string) {
		using std::string_literals::operator""s;
		return std::regex_match(string, std::regex("^("s + getRegex() + ")$"));
	}

	UnaryOperator::UnaryOperatorType UnaryOperator::getType(std::string unaryOperatorName) {
		if (std::find(allUnaryOperators.begin(), allUnaryOperators.end(), unaryOperatorName) != allUnaryOperators.end()) {
			using std::string_literals::operator""s;
			throw std::invalid_argument("Unknown UnaryOperator: "s + unaryOperatorName);
		}
		return stringToTypeConverter.at(unaryOperatorName);
	}



	const std::vector<std::string> UnaryOperator::allUnaryOperators{
		"-",
		"!",
		"sinh",
		"sech",
		"cosh",
		"csch",
		"ctgh",
		"tgh",
		"sin",
		"sec",
		"cos",
		"csc",
		"ctg",
		"tg",
		"asin",
		"asec",
		"acos",
		"acsc",
		"actg",
		"atg",
		"ln",
		"exp",
		"log",
		"sqrt",
		"cbrt",
		"sign",
		"floor",
		"ceil",
		"round",
		"fact",
		"abs"
	};

	const std::unordered_map<std::string, UnaryOperator::UnaryOperatorType> UnaryOperator::stringToTypeConverter{
		{"-",			UnaryOperator::UnaryOperatorType::negative},
		{"!",			UnaryOperator::UnaryOperatorType::fact},
		{"sinh",		UnaryOperator::UnaryOperatorType::sinh},
		{"sech",		UnaryOperator::UnaryOperatorType::sech},
		{"cosh",		UnaryOperator::UnaryOperatorType::cosh},
		{"csch",		UnaryOperator::UnaryOperatorType::csch},
		{"ctgh",		UnaryOperator::UnaryOperatorType::ctgh},
		{"tgh",		UnaryOperator::UnaryOperatorType::tgh},
		{"sin",		UnaryOperator::UnaryOperatorType::sin},
		{"sec",		UnaryOperator::UnaryOperatorType::sec},
		{"cos",		UnaryOperator::UnaryOperatorType::cos},
		{"csc",		UnaryOperator::UnaryOperatorType::csc},
		{"ctg",		UnaryOperator::UnaryOperatorType::ctg},
		{"tg",		UnaryOperator::UnaryOperatorType::tg},
		{"asin",		UnaryOperator::UnaryOperatorType::asin},
		{"asec",		UnaryOperator::UnaryOperatorType::asec},
		{"acos",		UnaryOperator::UnaryOperatorType::acos},
		{"acsc",		UnaryOperator::UnaryOperatorType::acsc},
		{"actg",		UnaryOperator::UnaryOperatorType::actg},
		{"atg",		UnaryOperator::UnaryOperatorType::atg},
		{"ln",		UnaryOperator::UnaryOperatorType::ln},
		{"exp",		UnaryOperator::UnaryOperatorType::exp},
		{"log",		UnaryOperator::UnaryOperatorType::log},
		{"sqrt",		UnaryOperator::UnaryOperatorType::sqrt},
		{"cbrt",		UnaryOperator::UnaryOperatorType::cbrt},
		{"sign",		UnaryOperator::UnaryOperatorType::sign},
		{"floor",	UnaryOperator::UnaryOperatorType::floor},
		{"ceil",		UnaryOperator::UnaryOperatorType::ceil},
		{"round",	UnaryOperator::UnaryOperatorType::round},
		{"fact",		UnaryOperator::UnaryOperatorType::fact},
		{"abs",		UnaryOperator::UnaryOperatorType::abs}
	};

	UnaryOperator& UnaryOperator::getUnaryOperator(std::string unaryOperator, Element arg) {
		switch (UnaryOperator::getType(unaryOperator)) {
		case UnaryOperator::UnaryOperatorType::sin:
			return Sin(arg);
		case UnaryOperator::UnaryOperatorType::cos:
			return Cos(arg);

		default:
			throw std::invalid_argument("Function " + unaryOperator + " not implemented");
		}


	}
}