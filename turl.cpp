#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main(int argc,char *argv[]) {
		if (argc < 2) {
			std::cout << "Turl: [Usage] turl <something.turl>" << std::endl;
			return 1;
		}
		ifstream turlSource(argv[1]);
		vector<string> turlFile;
		string turlLine;
		string turlWord;
		bool quotes = false;
		bool escape = false;
		long unsigned int character = 0;
		while (getline(turlSource,turlLine)) {
			for (character = 0;character < turlLine.length();character++) {
				if (turlLine[character] == ' ' && !quotes) { //Space Delimiter When Not In Quotes
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlWord = "";
				}
				else if (turlLine[character] == ';' && !quotes) { //Separate Out Semicolons When Not In Quotes
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlFile.push_back(";");
					turlWord = "";
				}
				else if (turlLine[character] == '"' && !(quotes && escape)) { //Separate Things Between "", disable " in a string if escape is set to true
					if (quotes) quotes = false;
					else quotes = true;
					if (!turlWord.empty()) turlFile.push_back(turlWord);
					turlWord = "";
				}
				else {
					if (turlLine[character] == '"' && !turlWord.empty()) turlWord.pop_back();
					turlWord += turlLine[character];
				}
				//Set Escape Boolean to true if there is a slash
				if (turlLine[character] == '\\') escape = true;
				else escape = false;
			}
			if (!turlWord.empty()) turlFile.push_back(turlWord);
			turlWord = "";
			turlFile.push_back(";");
		}
		for (string i : turlFile) {
				cout << i << endl;
		}
}
