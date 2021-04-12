#pragma once

#include "ValidatedElement.h"
#include "Parsing.h"
#include "../Structure/BinaryOperators/BinaryOperator.h"
#include "../Structure/UnaryOperators/UnaryOperator.h"

namespace Parsing {
	class ValidatedElementFactory
	{
	public:
		enum ValidatedElementType {
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
		static ValidatedElementType getGroup(std::string input) {
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

		static std::vector<ValidatedElement> getValidatedElementVector(std::vector<std::string> input) {
			std::vector<ValidatedElement> result{};

			for (auto inputElement : input) {
				switch (getGroup(inputElement)) {
				case Number:
					result.push_back(ValidatedNumber(inputElement));
					break;
				case BracketsOpen:
					result.push_back(ValidatedBracketOpen(inputElement));
					break;
				case BracketsClose:
					result.push_back(ValidatedBracketClose(inputElement));
					break;
				case UnaryOperator:
					result.push_back(ValidatedUnaryOperator(inputElement));
					break;
				case BinaryOperator:
					result.push_back(ValidatedBinaryOperator(inputElement));
					break;
				case Equality:
					result.push_back(ValidatedEquality(inputElement));
					break;
				case Comma:
					result.push_back(ValidatedComma(inputElement));
					break;
				case Word: 
				{
					auto toInsert = parseWord(inputElement);
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

