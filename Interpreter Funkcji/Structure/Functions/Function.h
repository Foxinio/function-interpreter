#pragma once

#include <memory>

#include "../Element.h"

namespace Structure {

	class Function : public Element {
	public:
		enum class FunctionType {
			log
		};

	private:
		const static std::unordered_map<std::string, FunctionType> stringToTypeConverter;
		const static std::vector<std::string> allFunctions;

	protected:
		std::vector<std::shared_ptr<Element>> arguments;

	public:
		const static unsigned int aridity;

		Function(std::vector<Element> arguments);

		virtual double evaluate(VariablePackage package);
		virtual std::string to_string();


		static std::string getRegex();
		static FunctionType getType(std::string functionName);
		static Function getFunction(std::string functionName, std::vector<Element> arguments);
	};
}