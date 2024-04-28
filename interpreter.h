#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "variables.h"

bool preProcessor(std::vector<std::vector<std::string>> *turlFile) {
	for (int i = 0; i < turlFile->size(); i++) {
		if (turlFile->at(i).at(0) == "mark") {
			if (turlFile->at(i).size() < 2) {
				std::cout << "[Invalid Mark] Name Missing" << std::endl;
				return false;
			}
			if (locationExists(turlFile->at(i).at(1))) {
				std::cout << "[Mark Redecaration]" << std::endl;
				return false;
			}
			location mark = { turlFile->at(i).at(1), i-1 };
			locations.push_back(mark);
			turlFile->erase(turlFile->begin()+i);
			i--;
		}
	}
	return true;
}

bool numberMath(std::string name, int offset, std::vector<std::string> math) {
	int result;
	char op = '+';
	int i = offset;
	while (i + 2 < math.size()) {
		i++;
		if (math.at(i).length() == 1) {
			switch (math.at(i)[0]) {
				case '+':
					op = '+';
					break;
				case '-':
					op = '-';
					break;
				case '*':
					op = '*';
					break;
				case '/':
					op = '/';
					break;
				default:
					std::cout << "[Operation Error] " << math.at(i)[0] << std::endl;
					return false;
			}
			continue;
		}

		int temp;
		if (math.at(i) == "value") {
			temp = atoi(math.at(i+1).c_str());
		}
		else if (math.at(i) == "number") {
			if (!numberExists(math.at(i+1))) {
				std::cout << "[Number Reference Error] " << math.at(i+1) << std::endl;
			}
			temp = numbers.at(getNumber(math.at(i+1))).value;
		}
		else if (math.at(i) == "string") {
			if (!stringExists(math.at(i+1))) {
				std::cout << "[String Reference Error] " << math.at(i+1) << std::endl;
			}
			temp = atoi(strings.at(getString(math.at(i+1))).value.c_str());
		}
		else {
			std::cout << "[Invaid Number Math Type] " << math.at(i) << std::endl;
			return false;
		}
		switch (op) {
			case '+':
				result += temp;
				break;
			case '-':
				result -= temp;
				break;
			case '*':
				result *= temp;
				break;
			case '/':
				result /= temp;
				break;
			default:
				std::cout << "[Operation Error] " << op << std::endl;
				return false;
		}
	}
	if (math.at(offset) == "=") numbers.at(getNumber(name)).value = result;
	else if (math.at(offset) == "+=") numbers.at(getNumber(name)).value += result;
	else if (math.at(offset) == "-=") numbers.at(getNumber(name)).value -= result;
	else if (math.at(offset) == "*=") numbers.at(getNumber(name)).value *= result;
	else if (math.at(offset) == "/=") numbers.at(getNumber(name)).value /= result;
	else {
		std::cout << "[Invalid Math Prefix] " << math.at(offset) << std::endl;
		return false;
	}
	return true;
}

bool stringMath(std::string name, int offset, std::vector<std::string> math) {
	std::string result;
	char op = '+';
	int i = offset;
	while (i + 2 < math.size()) {
		i++;
		if (math.at(i).length() == 1) {
			switch (math.at(i)[0]) {
				case '+':
					op = '+';
					break;
				default:
					std::cout << "[Operation Error] " << math.at(i)[0] << std::endl;
					return false;
			}
			continue;
		}

		std::string temp;
		if (math.at(i) == "value") {
			temp = math.at(i+1);
		}
		else if (math.at(i) == "number") {
			if (!numberExists(math.at(i+1))) {
				std::cout << "[Number Reference Error] " << math.at(i+1) << std::endl;
				return false;
			}
			std::stringstream buffer;
			buffer << numbers.at(getNumber(math.at(i+1))).value;
			temp = buffer.str();
		}
		else if (math.at(i) == "string") {
			if (!stringExists(math.at(i+1))) {
				std::cout << "[String Reference Error] " << math.at(i+1) << std::endl;
			}
			temp = strings.at(getString(math.at(i+1))).value;
		}
		else {
			std::cout << "[Invaid String Math Type] " << math.at(i) << std::endl;
			return false;
		}
		switch (op) {
			case '+':
				result += temp;
				break;
			default:
				std::cout << "[Operation Error] " << op << std::endl;
				return false;
		}
	}
	if (math.at(offset) == "=") strings.at(getString(name)).value = result;
	else if (math.at(offset) == "+=") strings.at(getString(name)).value += result;
	else {
		std::cout << "[Invalid Math Prefix] " << math.at(offset) << std::endl;
		return false;
	}
	return true;
}

bool interpret(std::vector<std::string> inst, int line, int *lnptr) { //True = success, False = fail
	//Low operand count to high operand count 1 -> ...
	if (inst.at(0) == "print") {
		for (int i = 1; i+1 < inst.size(); i+=2) {
			if (inst.at(i) == "value") {
				std::cout << inst.at(i+1);
			}
			else if (inst.at(i) == "number") {
				if (!numberExists(inst.at(i+1))) {
					std::cout << "[Number Reference Error] (Line " << line << ") " << inst.at(i+1);
					return false;
				}
				std::cout << numbers.at(getNumber(inst.at(i+1))).value;
			}
			else if (inst.at(i) == "string") {
				if (!stringExists(inst.at(i+1))) {
					std::cout << "[String Reference Error] (Line " << line << ") " << inst.at(i+1);
					return false;
				}
				std::cout << strings.at(getString(inst.at(i+1))).value;
			}
			else {
				std::cout << "[Invalid Print Type] (Line " << line << ") " << inst.at(i) << std::endl;
				return false;
			}
		}
		std::cout << std::endl;
		return true;
	}
	if (inst.at(0) == "input") {
		for (int i = 1; i+1 < inst.size(); i+=2) {
			if (inst.at(i) == "number") {
				if (!numberExists(inst.at(i+1))) {
					std::cout << "[Number Reference Error] (Line " << line << ") " << inst.at(i+1);
					return false;
				}
				std::cin >> numbers.at(getNumber(inst.at(i+1))).value;
			}
			else if (inst.at(i) == "string") {
				if (!stringExists(inst.at(i+1))) {
					std::cout << "[String Reference Error] (Line " << line << ") " << inst.at(i+1);
					return false;
				}
				std::cin >> strings.at(getString(inst.at(i+1))).value;
			}
			else {
				std::cout << "[Invalid Input Type] (Line " << line << ") " << inst.at(i) << std::endl;
				return false;
			}
		}
		return true;
	}
	//2 Operands
	if (inst.size() < 2) {
		std::cout << "[Low Operand Count] (Line " << line << ") For Instruction: " << inst.at(0) << std::endl;
		return false;
	}
	if (inst.at(0) == "number") {
		if (!numberExists(inst.at(1))) {
			std::cout << "[Number Reference Error] (Line " << line << ")" << std::endl;
			return false;
		}
		if (!numberMath(inst.at(1),2,inst)) {
			std::cout << "[Number Math Error] (Line " << line << ")" << std::endl;
			return false;
		}
		return true;
	}
	if (inst.at(0) == "string") {
		if (!stringExists(inst.at(1))) {
			std::cout << "[String Reference Error] (Line " << line << ")" << std::endl;
			return false;
		}
		if (!stringMath(inst.at(1),2,inst)) {
			std::cout << "[String Math Error] (Line " << line << ")" << std::endl;
			return false;
		}
		return true;
	}
	//3 Operands
	if (inst.size() < 3) {
		std::cout << "[Low Operand Count] (Line " << line << ") For Instruction: " << inst.at(0) << std::endl;
		return false;
	}
	if (inst.at(0) == "goto" && inst.at(1) == "mark") {
		std::string loc = inst.at(2);
		if (!locationExists(loc)) {
			std::cout << "[Mark Reference Error] (Line " << line << ") " << loc << std::endl;
			return false;
		}
		*lnptr = locations.at(getLocation(loc)).line;
		return true;
	}
	if (inst.at(0) == "goto" && inst.at(1) == "line") {
		int loc = atoi(inst.at(2).c_str());
		if (loc < 0) {
			std::cout << "[Negative Line] Cannot goto line " << loc << "(Line " << line << ") " << std::endl;
			return false;
		}
		*lnptr = loc;
		return true;
	}
	if (inst.at(0) == "goto" && inst.at(1) == "offset") {
		int loc = line + atoi(inst.at(2).c_str());
		if (loc < 0) {
			std::cout << "[Negative Line] Cannot goto line " << loc << " ( Offset " << inst.at(2) << ", Line " << line << ") " << std::endl;
			return false;
		}
		*lnptr = loc;
		return true;
	}
	if (inst.at(0) == "create" && inst.at(1) == "number") {
		if (numberExists(inst.at(2))) {
			std::cout << "[Number Redeclaration] (Line " << line << ")" << std::endl;
			return false;
		}
		createNumber(inst.at(2));
		if (inst.size() < 4) return true;	// No '=' Initialized to 0
		if (!numberMath(inst.at(2),3,inst)) {
			std::cout << "[Number Math Error] (Line " << line << ")" << std::endl;
			return false;
		}
		return true;
	}
	if (inst.at(0) == "create" && inst.at(1) == "string") {
		if (stringExists(inst.at(2))) {
			std::cout << "[String Redeclaration] (Line " << line << ")" << std::endl;
			return false;
		}
		createString(inst.at(2));
		if (inst.size() < 4) return true;	// No '=' Initialized to ""
		if (!stringMath(inst.at(2),3,inst)) {
			std::cout << "[String Math Error] (Line " << line << ")" << std::endl;
			return false;
		}
		return true;
	}
	if (inst.size() < 6) {
		std::cout << "[Low Operand Count] (Line " << line << ") For Instruction: " << inst.at(0) << std::endl;
		return false;
	}
	if (inst.at(0) == "if") {
		std::string value1;
		std::string value2;
		//Get Value 1
		if (inst.at(1) == "string" && stringExists(inst.at(2))) value1 = strings.at(getString(inst.at(2))).value;
		else if (inst.at(1) == "number" && numberExists(inst.at(2))) { std::stringstream buffer; buffer << numbers.at(getNumber(inst.at(2))).value; value1 = buffer.str(); }
		else if (inst.at(1) == "value") value1 = inst.at(2);
		//Get Value 2
		if (inst.at(4) == "string" && stringExists(inst.at(5))) value2 = strings.at(getString(inst.at(5))).value;
		else if (inst.at(4) == "number" && numberExists(inst.at(5))) { std::stringstream buffer; buffer << numbers.at(getNumber(inst.at(5))).value; value2 = buffer.str(); }
		else if (inst.at(4) == "value") value2 = inst.at(5);
		bool run = false;
		//Conditions
		std::string condition = inst.at(3);
		int number1 = atoi(value1.c_str());
		int number2 = atoi(value2.c_str());
		if (condition == "=" && value1 == value2) run = true;
		else if (condition == "!=" && value1 != value2) run = true;
		else if (condition == ">" && number1 > number2) run = true;
		else if (condition == "<" && number1 < number2) run = true;
		else if (condition == ">=" && number1 >= number2) run = true;
		else if (condition == "<=" && number1 <= number2) run = true;
		//Run if true
		std::vector<std::string> buffer = inst;
		buffer.erase(buffer.begin(),buffer.begin()+6);
		if (run) return interpret(buffer, line, lnptr);
		else return true;
	}

	//Long Unknown Instruction
	std::cout << "[Unknown Instruction] (Line " << line << ") " << inst.at(0) << std::endl;
	return false;
}
