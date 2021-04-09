#pragma once

#include <string>
#include <regex>

#include "../Structure/Function.h"

namespace Parsing {
	struct UnvalidatedElement {
		enum UnvalidatedElementType {
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

	private:
		std::string content;
		UnvalidatedElementType type;
		std::regex regex;
		std::vector<UnvalidatedElementType> beforeProhibited;
		std::vector<UnvalidatedElementType> afterProhibited;

		enum class Valid {
			Null,
			True,
			False
		} valid;

	protected:
		UnvalidatedElement(std::string content, 
								 UnvalidatedElementType type, 
								 std::string regex, 
								 std::vector<UnvalidatedElementType>&& previousAllowed, 
								 std::vector<UnvalidatedElementType>&& nextAllowed) :
			content(content), type(type), regex(regex), beforeProhibited(beforeProhibited), afterProhibited(afterProhibited), valid(Valid::Null) { }

	public:
		UnvalidatedElement() :
			content(), type(Null), regex("[^]*"), beforeProhibited(), afterProhibited() { }

		bool validate(UnvalidatedElementType previousType, UnvalidatedElementType nextType) {
			if (valid != Valid::Null) {
				return valid == Valid::True;
			}
			if (std::find(std::begin(beforeProhibited), std::end(beforeProhibited), previousType) != std::end(beforeProhibited) ||
				std::find(std::begin(afterProhibited), std::end(afterProhibited), nextType) != std::end(afterProhibited) ||
				!std::regex_match(content, regex)) {
				valid = Valid::False;
				return false;
			}
			valid = Valid::True;
			return true;
		}

		UnvalidatedElementType getType() const {
			return type;
		}

		std::string getContent() const {
			return std::string(content);
		}

		const std::regex& getRegex() {
			return regex;
		}
		const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return afterProhibited;
		}
		const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return beforeProhibited;
		}
	};

	// TODO Uzupelniæ vectory Prohibited before i Prohibited after i regex
	struct UnvalidatedNumber : 
		public UnvalidatedElement {

		UnvalidatedNumber(std::string content) :
			UnvalidatedElement(content, Number, "^\\-?[[:digit:]]+)\.[[:digit:]]+)?$", {
				//	Prohibited before Number

				}, {
				//	Prohibited  after Number
				
				}) { }
	private:

		static UnvalidatedNumber singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};
	

	struct UnvalidatedBracketOpen :
		public UnvalidatedElement {

		UnvalidatedBracketOpen(std::string content) :
			UnvalidatedElement(content, BracketsOpen, "^($", {
			//	Prohibited before Number

			}, {
			//	Prohibited  after Number

			}) { }
	private:

		static UnvalidatedBracketOpen singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedBracketClose :
		public UnvalidatedElement {

		UnvalidatedBracketClose(std::string content) :
			UnvalidatedElement(content, BracketsClose, "^)$", {
			//	Prohibited before Number

			}, {
			//	Prohibited  after Number

			}) { }
	private:

		static UnvalidatedBracketClose singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedUnaryOperator :
		public UnvalidatedElement {

		UnvalidatedUnaryOperator(std::string content) :
			UnvalidatedElement(content, UnaryOperator, "", {
			//	Prohibited before Number

				}, {
					//	Prohibited  after Number

				}) { }
	private:

		static UnvalidatedUnaryOperator singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedBinaryOperator :
		public UnvalidatedElement {

		UnvalidatedBinaryOperator(std::string content) :
			UnvalidatedElement(content, BinaryOperator, "", {
			//	Prohibited before 

			}, {
			//	Prohibited  after 

			}) { }
	private:

		static UnvalidatedBinaryOperator singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedEquality :
		public UnvalidatedElement {

		UnvalidatedEquality(std::string content) :
			UnvalidatedElement(content, Equality, "^[\\<\\>=]=$", {
			//	Prohibited before 

			}, {
			//	Prohibited  after 

			}) { }
	private:

		static UnvalidatedEquality singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedComma :
		public UnvalidatedElement {

		UnvalidatedComma(std::string content) :
			UnvalidatedElement(content, Comma, "^,$", {
			//	Prohibited before 

			}, {
			//	Prohibited  after 

			}) { }
	private:

		static UnvalidatedComma singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedVariable :
		public UnvalidatedElement {

		UnvalidatedVariable(std::string content) :
			UnvalidatedElement(content, Variable, "^[a-zA-Z]$", {
			//	Prohibited before 

			}, {
			//	Prohibited  after 

			}) { }
	private:

		static UnvalidatedVariable singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};


	struct UnvalidatedFunction :
		public UnvalidatedElement {

		UnvalidatedFunction(std::string content) :
			UnvalidatedElement(content, Function, Structure::Function::getRegex(), {
			//	Prohibited before 

			}, {
			//	Prohibited  after 

			}) { }
	private:

		static UnvalidatedFunction singleton;

	public:
		static const std::regex& getRegex() {
			return singleton.getRegex();
		}
		static const std::vector<UnvalidatedElementType>& getAfterProhibited() {
			return singleton.getAfterProhibited();
		}
		static const std::vector<UnvalidatedElementType>& getBeforeProhibited() {
			return singleton.getBeforeProhibited();
		}
	};
}