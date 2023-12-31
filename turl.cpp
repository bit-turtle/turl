#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main(int argc,char *argv[]) {
		if (argc < 2) {
			std::cout << "Turl: [Usage] turl <something.turl>" << std::endl;
			return 1;
		}

		std::ifstream turlSource(argv[1]);
		std::vector<std::string> turlFile;
		std::string turlLine;
		std::string turlWord;
		bool quotes = false;
		bool escape = false;
		long unsigned int character = 0;
		while (getline(turlSource,turlLine)) {
			for (character = 0;character < turlLine.length();character++) {
				if (turlLine[character] == '#' && !quotes) break; //hashtag '#' comments 
				else if ((turlLine[character] == ' ' || turlLine[character] == '\t') && !quotes) { //Space or Tab Delimiter When Not In Quotes
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlWord = "";
				}
				else if (turlLine[character] == ';' && !quotes) { //Separate Out Semicolons When Not In Quotes
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlFile.push_back(";");
					turlWord = "";
				}
				else if (turlLine[character] == '"' && !(quotes && escape)) { //Separate Things Between "", disable " in a string if escape is set to true
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlWord = "";
					if (!quotes) quotes = true;
					else quotes = false;
				}
				else {
					if (turlLine[character] == '"' && !turlWord.empty()) turlWord.pop_back(); //Delete Escape Character when used in string to write a quote (Line 30: for if test for escaping a quote)
					turlWord += turlLine[character];
				}
				//Set Escape Boolean to true if there is a slash
				if (turlLine[character] == '\\') escape = true;
				else escape = false;
			}
			if (!turlWord.empty()) turlFile.push_back(turlWord);
			turlWord = "";
			if (quotes) turlFile.push_back("\n");
			else turlFile.push_back(";"); //Add semicolon at the end of every new line
		}
		//Output Parsed Turl File
		for (std::string i : turlFile) {
				std::cout << i << std::endl;
		}
}
