#pragma once

#include <unordered_map>
#include <vector>

#include "UnvalidatedElement.h"

namespace Parsing {
	static std::vector<UnvalidatedElement>::iterator ValidateSplitedString(std::vector<UnvalidatedElement> input) {
		auto iter = std::begin(input);
		if (!iter->validate(UnvalidatedElement::Null, std::next(iter)->getType())) {
			// tutaj zaimplementowa� dodawanie obs�u�enie jakiego� problemu (np dodanie mno�enia pomi�dzy sta�� a zmienn�)

			//throw std::invalid_argument("Incorrect syntax");
			return iter;
		}
		for (++iter; iter != std::prev(std::end(input)); ++iter) {
			if (!iter->validate(std::prev(iter)->getType(), std::next(iter)->getType())) {
				// tutaj zaimplementowa� dodawanie obs�u�enie jakiego� problemu (np dodanie mno�enia pomi�dzy sta�� a zmienn�)

				//throw std::invalid_argument("Incorrect syntax");
				return iter;
			}
		}
		if (!iter->validate(std::next(iter)->getType(), UnvalidatedElement::Null)) {
			// tutaj zaimplementowa� dodawanie obs�u�enie jakiego� problemu (np dodanie mno�enia pomi�dzy sta�� a zmienn�)

			//throw std::invalid_argument("Incorrect syntax");
			return iter;
		}
		return std::end(input);
	}
}
