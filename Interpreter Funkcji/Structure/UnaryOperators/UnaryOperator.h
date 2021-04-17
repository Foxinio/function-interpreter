#pragma once

#include <numeric>
#include <algorithm>
#include <regex>

#include "../Element.h"

namespace Structure {
	class UnaryOperator :
		public Element
	{
	public:
		enum class UnaryOperatorType {
			negative,
			sinh,
			sech,
			cosh,
			csch,
			ctgh,
			tgh,
			sin,
			sec,
			cos,
			csc,
			ctg,
			tg,
			asin,
			asec,
			acos,
			acsc,
			actg,
			atg,
			ln,
			exp,
			log,
			sqrt,
			cbrt,
			sign,
			floor,
			ceil,
			round,
			fact,
			abs
		};

	protected:
		std::shared_ptr<Element> arg;

		UnaryOperator(Element argument) :
			arg(std::make_shared<Element>(argument)) { }
	public:
		const static std::unordered_map<std::string, UnaryOperatorType> stringToTypeConverter;
		static const std::vector<std::string> allUnaryOperators;

		virtual double evaluate(VariablePackage package);
		virtual std::string to_string();

		
		static std::string getRegex();
		static bool isUnaryOperator(std::string string);
		static UnaryOperatorType getType(std::string unaryOperatorName);
		static UnaryOperator& getUnaryOperator(std::string unaryOperator, Element arg);
	};

}
