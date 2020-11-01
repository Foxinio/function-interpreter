#pragma once
#include "Function.h"
#include "Element.h"
#include <string>
#include <vector>

class StringInterpreter
{
	std::string input;
public:
	StringInterpreter(std::string input) {
		if (input.length() == 0) {
			throw std::invalid_argument("Function cannot be empty.");
		}
		this->input = input;
	}

	Function Interpret() {
		
	}

private:
	class Splitter {
		enum class SplitElementType {
			BracketsOpen,
			Number,
			Word,
			Operator,
			BracketsClose,
			Equality,
			Factorial,
			Comma,
			Negative,
			Null
		};

		std::string input;
		std::vector<std::string> splitedString;
		std::string currentString;
		bool isDot = false;
		SplitElementType previousType = SplitElementType::Null;
		SplitElementType beforePreviousType = SplitElementType::Null;

	public:
		Splitter(std::string input) {
			this->input = input;
		}

		std::vector<std::string> Split() {

			for (auto character : input) {
				SplitElementType currentType = CurrentTypeDetector(character);

				if (previousType == SplitElementType::Null){
					currentString = character;
					if (currentType == SplitElementType::BracketsClose) {
						currentString = "";
					}
					else if (currentType == SplitElementType::Operator ||
						currentType == SplitElementType::Comma ||
						currentType == SplitElementType::Equality ||
						currentType == SplitElementType::Factorial) {
						throw std::invalid_argument("not recognized syntax");
					}
				}
				else if (previousType == SplitElementType::BracketsOpen) {
					if (currentType == SplitElementType::Operator ||
						currentType == SplitElementType::Comma ||
						currentType == SplitElementType::Factorial) {
						throw std::invalid_argument("not recognized syntax");
					}
					if (currentType == SplitElementType::BracketsClose) {
						currentString = "";
						previousType = beforePreviousType;
						continue;
					}
					else if (currentType == SplitElementType::Equality) {
						currentString = character;
					}
					else {
						splitedString.push_back(currentString);
						currentString = character;
					}
				}
				else if (previousType == SplitElementType::Number) {
					if (currentType == previousType) {
						currentString += character;
					}
					else {
						splitedString.push_back(currentString);
						if (currentType == SplitElementType::BracketsOpen ||
							currentType == SplitElementType::Word) {
							splitedString.push_back("*");
						}
						else if (currentType == SplitElementType::Negative) {
							splitedString.push_back("+");
							currentType = SplitElementType::Number;
						}
						currentString = character;
						isDot = false;
					}
				}
				else if (previousType == SplitElementType::Word) {
					if (currentType == previousType) {
						currentString += character;
					}
					else {
						splitedString.push_back(currentString);
						currentString = "";
					}
				}
				else if (previousType == SplitElementType::Operator) {
					if (currentType == SplitElementType::Operator ||
						currentType == SplitElementType::BracketsClose ||
						currentType == SplitElementType::Comma ||
						currentType == SplitElementType::Equality ||
						currentType == SplitElementType::Factorial) {
						throw std::invalid_argument("not recognized syntax");
					}
					else {
						splitedString.push_back(currentString);
						currentString = character;
						if (currentType == SplitElementType::Negative) {
							currentType = SplitElementType::Number;
						}
					}
				}
				else if (previousType == SplitElementType::BracketsClose) {
					splitedString.push_back(currentString);
					if (currentType == SplitElementType::BracketsOpen ||
						currentType == SplitElementType::Number ||
						currentType == SplitElementType::Word) {
						splitedString.push_back("*");
					}
					else if (currentType == SplitElementType::Negative) {
						splitedString.push_back("+");
					}
					currentString = character;
				}
				else if (previousType == SplitElementType::Factorial) {
					if (currentType == SplitElementType::Equality) {
						currentString += character;
					}
					else {
						splitedString.push_back(currentString);
						if (currentType == SplitElementType::Negative) {
							splitedString.push_back("+");
						}
						else if (currentType == SplitElementType::BracketsOpen ||
							currentType == SplitElementType::Number ||
							currentType == SplitElementType::Word) {
							throw std::invalid_argument("not recognized syntax");
						}
						currentString = character;
					}
				}
				else if (previousType == SplitElementType::Equality) {
					if (currentType == SplitElementType::Operator ||
							currentType == SplitElementType::Comma ||
							currentType == SplitElementType::Factorial) {
						throw std::invalid_argument("not recognized syntax");
					}
					else if (currentType == SplitElementType::BracketsClose) {
						currentType = previousType;
						beforePreviousType = SplitElementType::Equality;
					}
					else if (currentType == SplitElementType::Equality) {
						if (beforePreviousType == SplitElementType::Factorial) {
							splitedString.push_back("!");
							currentString += "=" + character;
						}
						else if (beforePreviousType == SplitElementType::Equality) {
							throw std::invalid_argument("not recognized syntax");
						}
						else {
							beforePreviousType = SplitElementType::Equality;
							currentString += character;
						}
					}
					else {
						splitedString.push_back(currentString);
						if (currentType == SplitElementType::BracketsOpen) {
							beforePreviousType = SplitElementType::Equality;
						}
						if (currentType == SplitElementType::Negative) {
							currentType == SplitElementType::Number;
						}
						currentString = character;
					}
				}
				else if (previousType == SplitElementType::Comma) {
					if (currentType == SplitElementType::Operator ||
						currentType == SplitElementType::Comma ||
						currentType == SplitElementType::Equality ||
						currentType == SplitElementType::BracketsClose ||
						currentType == SplitElementType::Factorial) {
						throw std::invalid_argument("not recognized syntax");
					}
					splitedString.push_back(currentString);
					if (currentType == SplitElementType::Negative) {
						currentType = SplitElementType::Number;
					}
					currentString = character;
				}
				else if (previousType == SplitElementType::Negative) {
					if (currentType == SplitElementType::Number) {
						currentString += character;
					}
					else if (currentType == SplitElementType::BracketsOpen || currentType == SplitElementType::Word) {
						splitedString.push_back(currentString + "1");
						splitedString.push_back("*");
						currentString = character;
					}
					else {
						throw std::invalid_argument("not recognized syntax");
					}
				}
				previousType = currentType;
			}

			if (previousType == SplitElementType::Operator ||
				previousType == SplitElementType::Comma ||
				previousType == SplitElementType::Equality ||
				previousType == SplitElementType::Factorial) {
				throw std::invalid_argument("not recognized syntax");
			}
			else if (previousType != SplitElementType::BracketsOpen) {
				splitedString.push_back(currentString);
			}
			return splitedString;
		}

		SplitElementType CurrentTypeDetector(char character) {
			using namespace std::string_literals;
			if ("+-*/^"s.find(character) != -1) {
				return SplitElementType::Operator;
			}
			else if (character == '(') {
				beforePreviousType = previousType;
				return SplitElementType::BracketsOpen;
			}
			else if (character == ')') {
				return SplitElementType::BracketsClose;
			}
			else if (character == '-') {
				return SplitElementType::Negative;
			}
			else if (character >= '0' && character <= '9' || character == '.') {
				if (character == '.' && (isDot || currentString.length() == 0)) {
					throw std::invalid_argument("wrong number syntax");
				}
				return SplitElementType::Number;
			}
			else if (character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z') {
				return SplitElementType::Word;
			}
			else if (character == '=' || character == '<' || character == '>') {
				if (previousType == SplitElementType::Factorial) {
					beforePreviousType = SplitElementType::Factorial;
				}
				return SplitElementType::Equality;
			}
			else if (character == '!') {
				return SplitElementType::Factorial;
			}
			else if (character == ',') {
				return SplitElementType::Comma;
			}
			else {
				throw std::invalid_argument("not recognized syntax");
			}
		}
	};
};

