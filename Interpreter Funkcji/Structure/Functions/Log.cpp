#include <algorithm>

#include "Log.h"

namespace Structure {
	const unsigned int Log::aridity = 2;


	double Log::evaluate(VariablePackage package) {
		return log(arguments[0]->evaluate(package)) / log(arguments[1]->evaluate(package));
	}

	std::string Log::to_string() {
		using std::string_literals::operator""s;
		std::string result = "log(";
		std::for_each(std::begin(arguments), std::end(arguments), [&result](std::shared_ptr<Element> elem) {
			result += elem->to_string() + ",";
			});
		result[result.length() - 1] = ')';
		return result;
	}
}