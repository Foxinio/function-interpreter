#pragma once

#include "UnvalidatedElement.h"
#include "WordParser.h"
#include "../Structure/BinaryOperator.h"
#include "../Structure/UnaryOperator.h"

namespace Parsing {
	class UnvalidatedElementFactory
	{
	public:
		enum UnvalidatedElementType {
			Null,
			Number,
			BracketsOpen,
			BracketsClose,
			UnaryOperator,
			BinaryOperator,
			Equality,
			Comma,
			Word
		};
		static UnvalidatedElementType getGroup(std::string input) {
			switch (input[0]) {
			case '(':
				return BracketsOpen;
			case ')':
				return BracketsClose;
			case ',':
				return Comma;
			default:
				if (input[0] >= 'a' && input[0] <= 'z' || input[0] >= 'A' && input[0] <= 'Z') {
					return Word;
				}
				else if (input[0] >= '0' && input[0] <= '9' || input[0] == '.') {
					return Number;
				}
				else if (Structure::BinaryOperator::isBinaryOperator(input)) {
					return BinaryOperator;
				}
				else if (Structure::UnaryOperator::isUnaryOperator(input)) {
					return UnaryOperator;
				}
				else if (input[0] >= '<' && input[0] <= '>') {
					return Equality;
				}
				return Null;
			}
		}

		static std::vector<UnvalidatedElement> getUnvalidatedElementVector(std::vector<std::string> input) {
			std::vector<UnvalidatedElement> result{};

			for (auto inputElement : input) {
				switch (getGroup(inputElement)) {
				case Number:
					result.push_back(UnvalidatedNumber(inputElement));
					break;
				case BracketsOpen:
					result.push_back(UnvalidatedBracketOpen(inputElement));
					break;
				case BracketsClose:
					result.push_back(UnvalidatedBracketClose(inputElement));
					break;
				case UnaryOperator:
					result.push_back(UnvalidatedUnaryOperator(inputElement));
					break;
				case BinaryOperator:
					result.push_back(UnvalidatedBinaryOperator(inputElement));
					break;
				case Equality:
					result.push_back(UnvalidatedEquality(inputElement));
					break;
				case Comma:
					result.push_back(UnvalidatedComma(inputElement));
					break;
				case Word: 
				{
					auto toInsert = ParseWord(inputElement);
					result.insert(std::end(result), std::begin(toInsert), std::end(toInsert));
					break;
				}
				case Null:
					break;
				}
			}

			return result;
		}

	};
}

