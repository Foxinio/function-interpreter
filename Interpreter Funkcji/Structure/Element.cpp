
#include <stdexcept>

#include "Element.h"
namespace Structure {
	double Element::evaluate(VariablePackage package) {
		throw std::invalid_argument("Call to base class without further context.");
	}
	std::string Element::to_string() {
		throw std::invalid_argument("Call to base class without further context.");
	}
}