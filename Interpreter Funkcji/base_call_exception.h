#pragma once

#include <stdexcept>

class base_call_exception :
   public std::exception {
public:
   std::string message;

   base_call_exception(std::string message):
      message(message) { }

   base_call_exception() = default;

   const char* what() const noexcept{
      return message.c_str();
   }
};

