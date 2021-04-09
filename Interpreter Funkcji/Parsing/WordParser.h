#pragma once

#include <vector>

#include "UnvalidatedElement.h"

namespace Parsing {
	std::vector<UnvalidatedElement> ParseWord(std::string wordToParse) {
		std::vector<UnvalidatedElement> result{};
		std::regex functionRegex = { UnvalidatedFunction::getRegex() };

		std::smatch regex_result;

		std::regex_search(wordToParse, regex_result, functionRegex);

		auto input_iter = wordToParse.cbegin();
		for (auto match_iter : regex_result) {
			while (input_iter != match_iter.first) {
				result.push_back(UnvalidatedVariable({ 1,*input_iter }));
				result.push_back(UnvalidatedFunction("*"));
				++input_iter;
			}

			result.push_back(UnvalidatedFunction({ match_iter.first, match_iter.second }));
				
			input_iter = match_iter.second;
		}
		while (input_iter != std::cend(wordToParse)) {
			result.push_back(UnvalidatedVariable({ 1,*input_iter }));
			result.push_back(UnvalidatedVariable("*"));
			++input_iter;
		}

		return result;
	}
}

