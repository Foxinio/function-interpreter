#pragma once
#include <string>


namespace Parsing {
	class ValidationRule;


	struct ValidatingContainer {

		enum Type {
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

		std::string content;
		Type type;
		const ValidationRule& rules;

		enum class Valid {
			Null,
			True,
			False
		} valid;

		ValidatingContainer(std::string content, Type type, const ValidationRule& rules) :
			content(content), type(type), rules(rules), valid(Valid::Null) { }

		static ValidatingContainer create(std::string content);

	};
}