
#include "../Structure/Element_pch.h"
#include "Parsing.h"

Structure::Element Parsing::makeTree(std::list<std::string>::const_iterator begin, std::list<std::string>::const_iterator end) {
	using namespace Structure;
	if (begin->getType() == ValidatedElement::UnaryOperator) {
		return UnaryOperator::getUnaryOperator(begin->getContent(), makeTree(std::next(begin), end));
	}
	else if (auto result = std::min_element(begin, end, [begin](const ValidatedElement& candidate, const ValidatedElement& smallest) {
		static std::uint32_t bracketCounter = begin->getType() == ValidatedElement::BracketsOpen ? 1 : 0;
		switch (candidate.getType())
		{
		case ValidatedElement::BracketsOpen:
			bracketCounter++;
			return false;
		case ValidatedElement::BracketsClose:
			bracketCounter--;
			return false;
		case ValidatedElement::BinaryOperator:
			if (bracketCounter == 0) {
				if (smallest.getType() == ValidatedElement::BinaryOperator) {
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
		}); result->getType() == ValidatedElement::BinaryOperator) {
		return BinaryOperator::getBinaryOperator(result->getContent(), makeTree(begin, result), makeTree(std::next(result), end));
	}
	else if(begin->getType() == ValidatedElement::BracketsOpen){}
}