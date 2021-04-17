#pragma once

#include <list>
#include <string>

#include "../Structure/Element.h"
#include "ValidatingContainer.h"

namespace Parsing {
	/*
	 * Splits input string by internaly specified rules.
	 */
	std::list<std::string> split(std::string input);

	/*
	 * Splits a word (string consisting of alphabethic characters) into functions and single characters
	 */
	std::list<std::string> parseWord(const std::string& wordToParse);

	/*
	 *	Checks whether splited string is matches established rules, 
	 *		fixes if possible 
	 *		throws exception if not
	 */
	std::list<ValidatingContainer> validate(std::list<std::string> list);

	/*
	 *	Makes tree representing expression in accordance with rules
	 * 	if expression doesn't match established rules results with undefined behaviour
	 */
	Structure::Element& makeTree(std::list<ValidatingContainer>::const_iterator beginIter, std::list<ValidatingContainer>::const_iterator endIter);

	/*
	 *	Parses string in accordance with established rules,
	 *		returns tree representing given expression if valid
	 * 	throws exception if not
	 */
	Structure::Element parse(std::string input);
}