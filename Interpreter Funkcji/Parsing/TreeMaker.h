#pragma once

#include "../Structure/Element_pch.h"
#include "UnvalidatedElement.h"

namespace Parsing {
	Structure::Element makeTree(std::vector<UnvalidatedElement>::const_iterator begin, std::vector<UnvalidatedElement>::const_iterator end) {
		using namespace Structure;
		//if(begin->getType() == UnvalidatedElement::BracketsOpen){}
		if (begin->getType() == UnvalidatedElement::UnaryOperator) {
			return UnaryOperator::getUnaryOperator(begin->getContent(), makeTree(std::next(begin), end));
		}
		if (auto result = std::min_element(begin, end, [begin](const UnvalidatedElement& candidate, const UnvalidatedElement& smallest) {
			static std::uint32_t bracketCounter = begin->getType() == UnvalidatedElement::BracketsOpen ? 1 : 0;
			switch (candidate.getType())
			{
			case UnvalidatedElement::BracketsOpen:
				bracketCounter++;
				return false;
			case UnvalidatedElement::BracketsClose:
				bracketCounter--;
				return false;
			case UnvalidatedElement::BinaryOperator:
				if (bracketCounter == 0) {
					if (smallest.getType() == UnvalidatedElement::BinaryOperator) {
						return BinaryOperator::priorityFromString(candidate.getContent()) < BinaryOperator::priorityFromString(smallest.getContent());
					}
					else {
						return true;
					}
				}
				else {
					return false;
				}
			default:
				return false;
			}
			}); result->getType() == UnvalidatedElement::BinaryOperator) {
			return BinaryOperator::getBinaryOperator(result->getContent(), makeTree(begin, result), makeTree(std::next(result), end));
		}
	}
}