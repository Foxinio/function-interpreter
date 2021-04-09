#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace Parsing {
	class Splitter {
	public:
		enum SplitElementType {
			Null,
			Word,
			Number,
			Equality,
			BracketsOpen,
			BracketsClose,
			Factorial,
			Comma,
			Addition,
			Subtraction,
			Multiplication,
			Division,
			Modulo,
			Semicolon,
			Colon,
			UpArrow
		};


		static SplitElementType groupCharacter(char c) {
			switch (c) {
			case '!':
				return Factorial;
			case '%':
				return Modulo;
			case '(':
				return BracketsOpen;
			case ')':
				return BracketsClose;
			case '*':
				return Multiplication;
			case '+':
				return Addition;
			case ',':
				return Comma;
			case '-':
				return Subtraction;
			case '.':
				return Number;
			case '/':
				return Division;
			case ':':
				return Colon;
			case ';':
				return Semicolon;
			case '^':
				return UpArrow;
			default:
				break;
			}

			if (c >= '0' && c <= '9') {
				return Number;
			}
			else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
				return Word;
			}
			else if (c >= '<' && c <= '>') {
				return Equality;
			}

			return Null;
		}


		static std::vector<std::string> Split(std::string input) {
			std::vector<std::string> result{};
			auto beginIter = std::begin(input);

			while (beginIter != std::end(input)) {
				SplitElementType type = groupCharacter(*beginIter);

				auto endIter = std::find_if_not(beginIter, input.end(), [type](char c) { return type == groupCharacter(c); });

				std::back_inserter(result) = { beginIter, endIter };

				beginIter = endIter;
			}

			return result;
		}

	};
}