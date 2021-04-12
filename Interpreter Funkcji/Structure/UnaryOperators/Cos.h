#pragma once
#include "UnaryOperator.h"

namespace Structure {
   class Cos :
      public UnaryOperator
   {
   public:
      Cos(Element arg) :
         UnaryOperator(arg) { }

      double evaluate(VariablePackage package) override {
         return std::cos(arg->evaluate(package));
      }

      std::string to_string() {
         using std::string_literals::operator""s;
         return "cos("s + arg->to_string() + ")";
      }
   };
}
