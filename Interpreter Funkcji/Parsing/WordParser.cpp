#include <regex>

#include "Parsing.h"

#include "../Structure/UnaryOperators/UnaryOperator.h"
#include "../Structure/Functions/Function.h"

std::list<std::string> Parsing::parseWord(const std::string& wordToParse) {
	std::list<std::string> result{};
	std::regex functionRegex{ Structure::Function::getRegex() + "|" + Structure::UnaryOperator::getRegex() };

	std::smatch regex_result;

	auto input_iter = wordToParse.cbegin();

	if (std::regex_search(wordToParse, regex_result, functionRegex)) {

		for (auto match_iter : regex_result) {

			while (input_iter != match_iter.first) {
				result.push_back({ 1,*input_iter });
				result.push_back("*");
				++input_iter;
			}

			result.push_back({ match_iter.first, match_iter.second });

			input_iter = match_iter.second;
		}
	}

	while (input_iter != std::cend(wordToParse)) {
		result.push_back({ 1,*input_iter });
		result.push_back("*");
		++input_iter;
	}

	return result;
}