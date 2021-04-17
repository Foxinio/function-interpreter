#include <string>
#include <iterator>

#include "ValidationRule.h"
#include "ValidatingContainer.h"


namespace Parsing {


	ValidationRule::ValidationRule(std::string regex,
		validationFunction isValid,
		reactionMap beforeReaction) :
		regex(std::regex(regex)), isValid(isValid), beforeReaction(beforeReaction) { }



	bool ValidationRule::validate(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {

		isValid(container, iter);

		auto previousType = std::prev(iter)->type;
		if (!std::regex_match(iter->content, regex)) {
			iter->valid = ValidatingContainer::Valid::False;
			return false;
		}

		beforeReaction.at(previousType)(container, iter);

		iter->valid = ValidatingContainer::Valid::True;
		return true;
	}

	ValidationRule::reactionFunctor ValidationRule::throwInvalidArgument(std::string message) {
		return [message](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
			throw std::invalid_argument(message);
		};
	}
	ValidationRule::reactionFunctor ValidationRule::insertBefore(ValidatingContainer toInsert) {
		return [toInsert](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
			container.insert(iter, toInsert);
		};
	}
	ValidationRule::reactionFunctor ValidationRule::insertAfter(ValidatingContainer toInsert) {
		return [toInsert](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
			container.insert(std::next(iter), toInsert);
		};
	}
	void ValidationRule::doNothing(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) { }



	const ValidationRule ValidationRule::Number = ValidationRule(
		"^\\-?[[:digit:]]+)\.[[:digit:]]+)?$",
		ValidationRule::doNothing,
		std::unordered_map<ValidatingContainer::Type, ValidationRule::reactionFunctor>{

			{ValidatingContainer::Type::Number,
				ValidationRule::throwInvalidArgument("Invalid Syntax")},

			{ ValidatingContainer::Type::BracketsOpen,
				ValidationRule::doNothing },

			{ ValidatingContainer::Type::BracketsClose,
				ValidationRule::insertBefore(ValidatingContainer::create("*")) }

	});
}