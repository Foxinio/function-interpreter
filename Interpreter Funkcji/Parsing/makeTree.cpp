//
//#include "../Structure/Element_pch.h"
//#include "Parsing.h"
//
//Structure::Element Parsing::makeTree(std::list<std::string>::const_iterator begin, std::list<std::string>::const_iterator end) {
//	using namespace Structure;
//	if (begin->getType() == ValidationRule::UnaryOperator) {
//		return UnaryOperator::getUnaryOperator(begin->getContent(), makeTree(std::next(begin), end));
//	}
//	else if (auto result = std::min_element(begin, end, [begin](const ValidationRule& candidate, const ValidationRule& smallest) {
//		static std::uint32_t bracketCounter = begin->getType() == ValidationRule::BracketsOpen ? 1 : 0;
//		switch (candidate.getType())
//		{
//		case ValidationRule::BracketsOpen:
//			bracketCounter++;
//			return false;
//		case ValidationRule::BracketsClose:
//			bracketCounter--;
//			return false;
//		case ValidationRule::BinaryOperator:
//			if (bracketCounter == 0) {
//				if (smallest.getType() == ValidationRule::BinaryOperator) {
//					return BinaryOperator::priorityFromString(candidate.getContent()) < BinaryOperator::priorityFromString(smallest.getContent());
//				}
//				else {
//					return true;
//				}
//			}
//			else {
//				return false;
//			}
//		default:
//			return false;
//		}
//		}); result->getType() == ValidationRule::BinaryOperator) {
//		return BinaryOperator::getBinaryOperator(result->getContent(), makeTree(begin, result), makeTree(std::next(result), end));
//	}
//	else if(begin->getType() == ValidationRule::BracketsOpen){}
//}