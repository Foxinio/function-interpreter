#pragma once

#include <unordered_map>
#include <initializer_list>
#include <utility>


class VariablePackage {
	std::unordered_map<std::string, double> content;

public:
	VariablePackage() :
		content(){ }

	VariablePackage(const VariablePackage& other) :
		content(other.content) {}

	VariablePackage(VariablePackage&& other) noexcept :
		content(other.content) {
		other.content.clear();
	}

	VariablePackage(std::initializer_list<std::pair<std::string, double>> l) :
		content(l.begin(), l.end()){ }

	VariablePackage operator=(const VariablePackage& other) {
		content = { other.content };
	}

	VariablePackage operator=(VariablePackage&& other) noexcept {
		content = std::move(other.content);

		other.content.clear();
	}

	bool put(std::string variableName, double value) {
		return put({ variableName, value });
	}

	bool put(std::pair < std::string, double> p) {
		return content.insert(p).second;
	}

	double& operator[](std::string key) {
		return content[key];
	}
};