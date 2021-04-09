#pragma once

#include <numeric>
#include <stdexcept>

#include "UnaryOperator.h"
namespace Structure {
	class Function :
		public UnaryOperator
	{
	public:
		enum class FunctionType {
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

	private:
		const static std::unordered_map<std::string, FunctionType> stringToTypeConverter;
		const static std::vector<std::string> allFunctions;

	protected:
		FunctionType functionType;

	public:
		static std::string getRegex() {
				std::string result = std::accumulate(std::begin(allFunctions), std::end(allFunctions), std::string(), [](std::string init, std::string elem) {
				return init + elem + "|";
			});
				return result.substr(0, result.length() - 1);
		}
		static FunctionType getType(std::string functionName) {
			if (std::find(allFunctions.begin(), allFunctions.end(), functionName) != allFunctions.end()) {
				throw std::invalid_argument("No such function exists");
			}
			return stringToTypeConverter.at(functionName);
		}


		Function(std::string functionName, Element argument) :
			UnaryOperator(argument), functionType(getType(functionName)){}
	};
}