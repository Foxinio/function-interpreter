#pragma once
#include <memory>
#include "Element.h"
namespace Structure {

	class Parameter :
		public Element
	{
	public:
		std::shared_ptr<std::string> variableName;

		Parameter(std::shared_ptr<std::string> variableName) {
			this->variableName = variableName;
		}

		double evaluate(VariablePackage package) override {
			return package[*variableName];
		}

		std::string to_string() {
			return *variableName;
		}
	};
}
