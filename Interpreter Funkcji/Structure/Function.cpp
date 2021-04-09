#include "Function.h"
namespace Structure {







	const std::vector<std::string> Function::allFunctions{
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

	const std::unordered_map<std::string, Function::FunctionType> Function::stringToTypeConverter{
		{"sinh",		Function::FunctionType::sinh},
		{"sech",		Function::FunctionType::sech},
		{"cosh",		Function::FunctionType::cosh},
		{"csch",		Function::FunctionType::csch},
		{"ctgh",		Function::FunctionType::ctgh},
		{"tgh",		Function::FunctionType::tgh},
		{"sin",		Function::FunctionType::sin},
		{"sec",		Function::FunctionType::sec},
		{"cos",		Function::FunctionType::cos},
		{"csc",		Function::FunctionType::csc},
		{"ctg",		Function::FunctionType::ctg},
		{"tg",		Function::FunctionType::tg},
		{"asin",		Function::FunctionType::asin},
		{"asec",		Function::FunctionType::asec},
		{"acos",		Function::FunctionType::acos},
		{"acsc",		Function::FunctionType::acsc},
		{"actg",		Function::FunctionType::actg},
		{"atg",		Function::FunctionType::atg},
		{"ln",		Function::FunctionType::ln},
		{"exp",		Function::FunctionType::exp},
		{"log",		Function::FunctionType::log},
		{"sqrt",		Function::FunctionType::sqrt},
		{"cbrt",		Function::FunctionType::cbrt},
		{"sign",		Function::FunctionType::sign},
		{"floor",	Function::FunctionType::floor},
		{"ceil",		Function::FunctionType::ceil},
		{"round",	Function::FunctionType::round},
		{"fact",		Function::FunctionType::fact},
		{"abs",		Function::FunctionType::abs}
	};
}