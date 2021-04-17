
#include <set>

#include "../Structure/Element_pch.h"
#include "Parsing.h"

namespace Parsing {
	Structure::Element& makeTree(std::set<std::string> variables, std::list<ValidatingContainer>::const_iterator begin, std::list<ValidatingContainer>::const_iterator end) {
		if (begin == end)throw std::invalid_argument("Somewhere error appered.");
		using namespace Structure;
		if (auto result = std::min_element(begin, end, [begin](const ValidatingContainer& candidate, const ValidatingContainer& smallest) {
			static std::uint32_t bracketCounter = begin->type == ValidatingContainer::BracketsOpen ? 1 : 0;
			switch (candidate.type)
			{
			case ValidatingContainer::BracketsOpen:
				bracketCounter++;
				return false;
			case ValidatingContainer::BracketsClose:
				bracketCounter--;
				return false;
			case ValidatingContainer::BinaryOperator:
				if (bracketCounter == 0) {
					if (smallest.type == ValidatingContainer::BinaryOperator) {
						return BinaryOperator::priorityFromString(candidate.content) < BinaryOperator::priorityFromString(smallest.content);
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
			}); result->type == ValidatingContainer::BinaryOperator) {
			return BinaryOperator::getBinaryOperator(result->content, makeTree(begin, result), makeTree(std::next(result), end));
		}
		else if (begin->type == ValidatingContainer::UnaryOperator) {
			return UnaryOperator::getUnaryOperator(begin->content, makeTree(std::next(begin), end));
		}
		else if (begin->type == ValidatingContainer::BracketsOpen && std::prev(end)->type == ValidatingContainer::BracketsClose) {
			return makeTree(std::next(begin), std::prev(end));
		}
		else if (begin->type == ValidatingContainer::Function) {
			Function::FunctionType type = Function::getType(begin->content);
			int aridity = Function::getAridity(type);
			int thisAridity = 0;
			auto iter = begin;
			auto resultIter = begin;
			Function result = Function::getFunction(type, {});
			while ((resultIter = std::find(iter, end, [=](const ValidatingContainer& candidate) {
					static int bracketCounter = 0;
					if (bracketCounter < 0) {
						throw std::invalid_argument(begin->content + ": not enougth arguments.");
					}
					switch (candidate.type) {
					case ValidatingContainer::BracketsOpen:
						bracketCounter++;
						return false;
					case ValidatingContainer::BracketsClose:
						bracketCounter--;
						return false;
					case ValidatingContainer::Comma:
						return bracketCounter == 1;
					default:
						return false;
					}
				})) != end) {

				if (thisAridity == aridity) {
					throw std::invalid_argument(begin->content + ": too many arguments.");
				}

				result.push_argument(makeTree(iter, resultIter));
				iter = std::next(resultIter);
			}
			result.push_argument(makeTree(iter, end));
			return result;
		}
		else if (begin->type == ValidatingContainer::Number) {
			return Constant(std::stoi(begin->content));
		}
		else if (begin->type == ValidatingContainer::Variable) {
			variables.insert(begin->content);
			return Parameter(begin->content);
		}
		else if (begin->type == ValidatingContainer::BracketsClose) {
			throw std::invalid_argument("Something went wrong, BracketClose at begining.");
		}
		else if (begin->type == ValidatingContainer::Comma) {
			throw std::invalid_argument("Something went wrong, Comma at begining.");
		}
		else if (begin->type == ValidatingContainer::Equality) {
			throw std::invalid_argument("Not implement yet.");
		}
		else if (begin->type == ValidatingContainer::BracketsOpen) {
			throw std::invalid_argument("Bracket open but not closed");
		}
	}
}