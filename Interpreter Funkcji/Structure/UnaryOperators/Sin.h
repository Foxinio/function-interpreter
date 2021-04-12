#pragma once
#include "UnaryOperator.h"

namespace Structure {
   class Sin :
      public UnaryOperator
   {
   public:
      Sin(Element arg) : 
         UnaryOperator(arg){ }

      double evaluate(VariablePackage package) override {
         return std::sin(arg->evaluate(package));
      }

      std::string to_string() {
         using std::string_literals::operator""s;
         return "sin("s + arg->to_string() + ")";
      }
   };
}

