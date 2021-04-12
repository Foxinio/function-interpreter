#pragma once

#include <unordered_map>
#include <vector>

#include "ValidatedElement.h"

namespace Parsing {
	static std::vector<ValidatedElement>::iterator ValidateSplitedString(std::vector<ValidatedElement> input) {
		auto iter = std::begin(input);
		if (!iter->validate(ValidatedElement::Null, std::next(iter)->getType())) {
			// tutaj zaimplementowaæ dodawanie obs³u¿enie jakiegoœ problemu (np dodanie mno¿enia pomiêdzy sta³¹ a zmienn¹)

			//throw std::invalid_argument("Incorrect syntax");
			return iter;
		}
		for (++iter; iter != std::prev(std::end(input)); ++iter) {
			if (!iter->validate(std::prev(iter)->getType(), std::next(iter)->getType())) {
				// tutaj zaimplementowaæ dodawanie obs³u¿enie jakiegoœ problemu (np dodanie mno¿enia pomiêdzy sta³¹ a zmienn¹)

				//throw std::invalid_argument("Incorrect syntax");
				return iter;
			}
		}
		if (!iter->validate(std::next(iter)->getType(), ValidatedElement::Null)) {
			// tutaj zaimplementowaæ dodawanie obs³u¿enie jakiegoœ problemu (np dodanie mno¿enia pomiêdzy sta³¹ a zmienn¹)

			//throw std::invalid_argument("Incorrect syntax");
			return iter;
		}
		return std::end(input);
	}
}
