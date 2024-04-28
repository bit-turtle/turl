#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#include "parse.h"
#include "interpreter.h"

std::string help = "Turl Help:\nUsage: turl <filename>\nFlags:\ndebug: Displays Debug Info\nturl <filename> debug";

int main(int argc,char *argv[]) {

		if (argc < 2) {
			std::cout << help << std::endl;
			return 1;
		}

		std::ifstream turlSource(argv[1]);

		if (!turlSource) {
			std::cout << "Turl: [Error] Failed To Read Turl File: " << argv[1] << std::endl;
			return 2;
		}

		std::stringstream buffer;
		buffer << turlSource.rdbuf();

		std::vector<std::vector<std::string>> turlFile = parse(buffer.str());	//From "parse.h"

		if (!preProcessor(&turlFile)) {
			std::cout << "[Pre Processor Error]" << std::endl;
			return 3;
		}

		bool debug = false;	//Debug mode
		if (argc > 2 && strcmp(argv[2],"debug") == 0) debug = true;

		if (debug) for (int i = 0; i < numbers.size(); i++) std::cout << "mark " << locations.at(i).name << " = " << locations.at(i).line << std::endl;

		bool running = true;
		for (int line = 0; line < turlFile.size(); line++) {
			if (debug) std::cout << "[Debug] Running instruction..." << std::endl;
			try {
				if (!interpret(turlFile.at(line),line,&line)) {
					running = false;
					break;
				}
			}
			catch (std::out_of_range) {
				std::cout << "[Invalid Instruction] (Line " << line << ") " << std::endl;
			}

			if (debug) {
				//Display numbers
				for (int i = 0; i < numbers.size(); i++) std::cout << "number " << numbers.at(i).name << " = " << numbers.at(i).value << std::endl;

				//Display strings
				for (int i = 0; i < strings.size(); i++) std::cout << "string " << strings.at(i).name << " = " << strings.at(i).value << std::endl;
			}
		}

		//End Of Program
		if (running) {
			if (debug) std::cout << "[Program Ended]" << std::endl;
		}
		else {
			std::cout << "[Program Stopped]" << std::endl;
		}
}
