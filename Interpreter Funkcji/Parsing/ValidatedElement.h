#pragma once
#include <functional>
#include <regex>
#include <unordered_map>


#include "ValidatingContainer.h"

namespace Parsing {

	struct ValidationRule {

		using reactionFunctor = std::function<void(std::list<ValidatingContainer>&, std::list<ValidatingContainer>::iterator&)>;
		using reactionMap = std::unordered_map<ValidatingContainer::Type, reactionFunctor>;
		using validationFunction = reactionFunctor;

	private:
		const std::regex regex;
		const validationFunction isValid;
		const reactionMap beforeReaction;


		ValidationRule(std::string regex,
			validationFunction isValid,
			reactionMap beforeReaction);

		ValidationRule() = delete;

	public:


		bool validate(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter);

		static const ValidationRule Number;

		static const ValidationRule BracketOpen;

		static const ValidationRule BracketClose;

		static const ValidationRule UnaryOperator;

		static const ValidationRule BinaryOperator;

		static const ValidationRule Equality;

		static const ValidationRule Comma;

		static const ValidationRule Variable;

		static const ValidationRule Function;

		const auto& getBaseRegex() {
			return regex;
		}
		const auto& getBaseBeforeProhibited() {
			return beforeReaction;
		}

		static reactionFunctor throwInvalidArgument(std::string message);
		static reactionFunctor insertBefore(ValidatingContainer toInsert);
		static reactionFunctor insertAfter(ValidatingContainer toInsert);
		static void doNothing(std::list<ValidatingContainer>& container, std::list<ValidatingContainer>::iterator iter);
	};



	// TODO Uzupelniæ vectory Prohibited before i Prohibited after i regex
	//struct ValidatedNumber : 
	//	public ValidationRule {
	//
	//	ValidatedNumber(std::string content) :
	//		ValidationRule(content, Number, "^\\-?[[:digit:]]+)\.[[:digit:]]+)?$", {
	//			//	Prohibited before Number
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//			) { }
	//private:
	//
	//	static ValidatedNumber singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedBracketOpen :
	//	public ValidationRule {
	//
	//	ValidatedBracketOpen(std::string content) :
	//		ValidationRule(content, BracketsOpen, "^($", {
	//		//	Prohibited before Number
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedBracketOpen singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedBracketClose :
	//	public ValidationRule {
	//
	//	ValidatedBracketClose(std::string content) :
	//		ValidationRule(content, BracketsClose, "^)$", {
	//		//	Prohibited before Number
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedBracketClose singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedUnaryOperator :
	//	public ValidationRule {
	//
	//	ValidatedUnaryOperator(std::string content) :
	//		ValidationRule(content, UnaryOperator, "", {
	//		//	Prohibited before Number
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedUnaryOperator singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//	
	//struct ValidatedBinaryOperator :
	//	public ValidationRule {
	//
	//	ValidatedBinaryOperator(std::string content) :
	//		ValidationRule(content, BinaryOperator, "", {
	//		//	Prohibited before 
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedBinaryOperator singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedEquality :
	//	public ValidationRule {
	//
	//	ValidatedEquality(std::string content) :
	//		ValidationRule(content, Equality, "^[\\<\\>=]=$", {
	//		//	Prohibited before 
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedEquality singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedComma :
	//	public ValidationRule {
	//
	//	ValidatedComma(std::string content) :
	//		ValidationRule(content, Comma, "^,$", {
	//		//	Prohibited before 
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedComma singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedVariable :
	//	public ValidationRule {
	//
	//	ValidatedVariable(std::string content) :
	//		ValidationRule(content, Variable, "^[a-zA-Z]$", {
	//		//	Prohibited before 
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedVariable singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
	//
	//
	//struct ValidatedFunction :
	//	public ValidationRule {
	//
	//	ValidatedFunction(std::string content) :
	//		ValidationRule(content, Function, Structure::Function<0>::getBaseRegex(), {
	//		//	Prohibited before 
	//
	//			}
	//			//, {
	//			////	Prohibited  after Number
	//			//
	//			//}
	//		) { }
	//private:
	//
	//	static ValidatedFunction singleton;
	//
	//public:
	//	static const auto& getRegex() {
	//		return singleton.getBaseRegex();
	//	}
	//	//static const auto& getAfterProhibited() {
	//	//	return singleton.getBaseAfterProhibited();
	//	//}
	//	static const auto& getBeforeProhibited() {
	//		return singleton.getBaseBeforeProhibited();
	//	}
	//};
}