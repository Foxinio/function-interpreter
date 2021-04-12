#include "Parsing.h"

#include <list>
#include <string>
#include <algorithm>
#include <iterator>

std::list<std::string> Parsing::split(std::string input) {
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

	auto groupCharacter = [](char c) {
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
	};

	std::list<std::string> result{};
	auto beginIter = std::begin(input);

	while (beginIter != std::end(input)) {
		SplitElementType type = groupCharacter(*beginIter);

		auto endIter = std::find_if_not(beginIter, input.end(), [type, groupCharacter](char c) { return type == groupCharacter(c); });
		if (type == Word) {
			std::ranges::copy(parseWord({ beginIter, endIter }), std::back_inserter(result));
		}
		else {
			std::back_inserter(result) = { beginIter, endIter };
		}

		beginIter = endIter;
	}

	return result;
}