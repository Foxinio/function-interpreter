#include "Function.h"
namespace Structure {

	const std::vector<std::string> Function::allFunctions{
		"log"
	};

	const std::unordered_map<std::string, Function::FunctionType> Function::stringToTypeConverter{
		{"log", Function::FunctionType::log}
	};
}