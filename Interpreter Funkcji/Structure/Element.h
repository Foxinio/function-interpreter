#pragma once
#include <string>
#include <memory>

#include "VariablePackage.h"

namespace Structure {
	class Element
	{
	public:
		double		virtual evaluate(VariablePackage package);
		std::string virtual to_string();
	};
}
