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
		const static std::unordered_map<FunctionType, std::string> typeToStringConverter;
		const static std::vector<std::string> allFunctions;

	protected:
		std::vector<std::shared_ptr<Element>> arguments;

	public:
		const static unsigned int aridity;

		Function(std::vector<Element> arguments);
		Function();

		virtual double evaluate(VariablePackage package);
		virtual std::string to_string();

		void push_argument(Element& elem) {
			arguments.push_back(std::make_shared<Element>(elem));
		}

		static std::string getRegex();
		static FunctionType getType(std::string functionName);
		static std::string getName(FunctionType type);
		static Function getFunction(FunctionType type, std::vector<Element> arguments);
		static unsigned int getAridity(FunctionType type);
	};
}