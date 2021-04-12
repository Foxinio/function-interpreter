#pragma once

#include <string>
#include <regex>
#include <functional>
#include <iterator>

#include "../Structure/Functions/Function.h"

namespace Parsing {

	struct ValidatingContainer {
		std::string content;
		ValidatedElement::ValidatedElementType type;
		const ValidatedElement& rules;

		enum class Valid {
			Null,
			True,
			False
		} valid;

		ValidatingContainer(std::string content, ValidatedElement::ValidatedElementType type, const ValidatedElement& rules) :
			content(content), type(type), rules(rules), valid(Valid::Null) { }

	};

	struct ValidatedElement {
		enum ValidatedElementType {
			Null,
			Number,
			BracketsOpen,
			BracketsClose,
			UnaryOperator,
			BinaryOperator,
			Equality,
			Comma,
			Variable,
			Function
		};

		using reactionFunctor = std::function<void(std::list<ValidatingContainer>&, std::list<ValidatingContainer>::iterator&)>;

	private:
		const ValidatedElementType type;
		const std::regex regex;
		const std::function<bool(std::list<ValidatingContainer>::iterator&)> isValid;
		const std::unordered_map<ValidatedElementType, reactionFunctor> beforeReaction;


		ValidatedElement(std::string regex, 
			std::function<bool(std::list<ValidatingContainer>::iterator&)> isValid,
			std::unordered_map<ValidatedElementType, reactionFunctor> beforeReaction) :
			regex(std::regex(regex)), isValid(isValid), beforeReaction(beforeReaction) { }
		ValidatedElement() = delete;

	public:
		bool validate(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {

			isValid(iter);

			auto previousType = std::prev(iter)->rules.type;
			if (!std::regex_match(iter->content, regex)) {
				iter->valid = ValidatingContainer::Valid::False;
				return false;
			}

			beforeReaction.at(previousType);

			iter->valid = ValidatingContainer::Valid::True;
			return true;
		}

		static const ValidatedElement Number;
		static const ValidatedElement BracketOpen;
		static const ValidatedElement BracketClose;
		static const ValidatedElement UnaryOperator;
		static const ValidatedElement BinaryOperator;
		static const ValidatedElement Equality;
		static const ValidatedElement Comma;
		static const ValidatedElement Variable;
		static const ValidatedElement Function;

		const auto& getBaseRegex() {
			return regex;
		}
		const auto& getBaseBeforeProhibited() {
			return beforeReaction;
		}

		static reactionFunctor throwInvalidArgument(std::string message) {
			return [message](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
				throw std::invalid_argument(message);
			};
		}
		static reactionFunctor insertBefore(ValidatingContainer toInsert) {
			return [toInsert](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
				container.insert(iter, toInsert);
			};
		}
		static reactionFunctor insertAfter(ValidatingContainer toInsert) {
			return [toInsert](std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) {
				container.insert(std::next(iter), toInsert);
			};
		}
		static void doNothing(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter) { }
	};

	const ValidatedElement Number = ValidatedElement(
		"^\\-?[[:digit:]]+)\.[[:digit:]]+)?$" ,
	ValidatedElement::doNothing, 
	std::unordered_map<ValidatedElement::ValidatedElementType, ValidatedElement::reactionFunctor>{

		{ValidatedElement::ValidatedElementType::Number,			
			ValidatedElement::throwInvalidArgument("Invalid Syntax")},

		{ValidatedElement::ValidatedElementType::BracketsOpen,	
			ValidatedElement::doNothing},

		{ValidatedElement::ValidatedElementType::BracketsClose,	
			ValidatedElement::insertBefore(ValidatingContainer("*", 
																				ValidatedElement::ValidatedElementType::BinaryOperator, 
																				ValidatedElement::BinaryOperator))}
		
	});


	// TODO Uzupelniæ vectory Prohibited before i Prohibited after i regex
	struct ValidatedNumber : 
		public ValidatedElement {

		ValidatedNumber(std::string content) :
			ValidatedElement(content, Number, "^\\-?[[:digit:]]+)\.[[:digit:]]+)?$", {
				//	Prohibited before Number

				}
				//, {
				////	Prohibited  after Number
				//
				//}
				) { }
	private:

		static ValidatedNumber singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};
	

	struct ValidatedBracketOpen :
		public ValidatedElement {

		ValidatedBracketOpen(std::string content) :
			ValidatedElement(content, BracketsOpen, "^($", {
			//	Prohibited before Number

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedBracketOpen singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedBracketClose :
		public ValidatedElement {

		ValidatedBracketClose(std::string content) :
			ValidatedElement(content, BracketsClose, "^)$", {
			//	Prohibited before Number

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedBracketClose singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedUnaryOperator :
		public ValidatedElement {

		ValidatedUnaryOperator(std::string content) :
			ValidatedElement(content, UnaryOperator, "", {
			//	Prohibited before Number

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedUnaryOperator singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedBinaryOperator :
		public ValidatedElement {

		ValidatedBinaryOperator(std::string content) :
			ValidatedElement(content, BinaryOperator, "", {
			//	Prohibited before 

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedBinaryOperator singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedEquality :
		public ValidatedElement {

		ValidatedEquality(std::string content) :
			ValidatedElement(content, Equality, "^[\\<\\>=]=$", {
			//	Prohibited before 

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedEquality singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedComma :
		public ValidatedElement {

		ValidatedComma(std::string content) :
			ValidatedElement(content, Comma, "^,$", {
			//	Prohibited before 

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedComma singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedVariable :
		public ValidatedElement {

		ValidatedVariable(std::string content) :
			ValidatedElement(content, Variable, "^[a-zA-Z]$", {
			//	Prohibited before 

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedVariable singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};


	struct ValidatedFunction :
		public ValidatedElement {

		ValidatedFunction(std::string content) :
			ValidatedElement(content, Function, Structure::Function<0>::getBaseRegex(), {
			//	Prohibited before 

				}
				//, {
				////	Prohibited  after Number
				//
				//}
			) { }
	private:

		static ValidatedFunction singleton;

	public:
		static const auto& getRegex() {
			return singleton.getBaseRegex();
		}
		//static const auto& getAfterProhibited() {
		//	return singleton.getBaseAfterProhibited();
		//}
		static const auto& getBeforeProhibited() {
			return singleton.getBaseBeforeProhibited();
		}
	};
}