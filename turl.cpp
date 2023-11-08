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
		if (!turlSource) {
			std::cout << "Failed To Read Turl File: " << argv[1];
			return 2;
		}
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
					turlFile.push_back("'");
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
		//Apply turl.lang if it exists
		std::ifstream turlLang("turl.lang");
		if (turlLang) {
			std::string langLine;
			std::string originalLang;
			std::string newLang;
			short unsigned int stage = 0;
			long unsigned int character = 0;
			while (getline(turlLang,langLine)) {
				stage = 0;
				originalLang = ""; //What was written in the code
				newLang = ""; //What it should be replaced with
				for (character = 0; character < langLine.length(); character++) {
					if (langLine[character] == '=') stage++;
					else if (stage == 0) originalLang += langLine[character];
					else if (stage == 1) newLang += langLine[character];
					else break;
				}
				bool inString = false;
				for (int i = 0; i < turlFile.size(); i++) {
					if (!inString && turlFile.at(i) == originalLang) { //Apply settings in turl.lang if not in a string and equal to original lang
						turlFile.at(i) = newLang;
					}
					if (turlFile.at(i) == "'") inString = true; //Check if in string
					else inString = false;
				}
			}
		}
		//Prepare Variable Vectors
		//Internal type ids:
		//number:0
		//string:1
		//list:2
		//Variable Data Storage
		std::vector<int> numbers; //If Value Deleted set to 0
		std::vector<std::string> strings; //If Value Deleted set to ""
		std::vector<std::vector<std::vector<unsigned int>>> lists; //If Value Deleted empty vector
		std::vector<std::vector<short unsigned int>> listTypes;
		//Reference Names,types,and locations, if deleted completely delete
		std::vector<std::vector<std::string>> names;
		std::vector<std::vector<short unsigned int>> types;
		std::vector<std::vector<unsigned int>> locations;

		//Current Location
		short unsigned int currentType;
		unsigned int currentLocation;
		
		struct turlVariables {
			void createNumber(std::string name) {
				numbers.push_back(0);
				names.push_back(name);
				types.push_back(0);
				numbers.size() - 1;
			}
			void createString(std::string name) {
				strings.push_back("");
				names.push_back(name);
				types.push_back(1);
				strings.size() - 1;
			}
			void createList(std::string name,short unsigned int type) {
				lists.push_back({});
				listTypes.push_back(type);
				names.push_back(name);
				types.push_back(2);
				lists.size() - 1;
			}
			struct listFunctions {
				void at(unsigned int location,unsigned int listLocation) {
					currentType = listTypes.at(location);
					currentLocation = lists.at(location).at(listLocation);
					switch (listTypes.at(location)) {
						case 0:
							return numbers.at(lists.at(location).at(listLocation));
							break;
						case 1:
							return strings.at(lists.at(location).at(listLocation));
							break;
						case 2:
							return lists.at(lists.at(location).at(listLocation));
							break;
					}
				}
				void first(unsigned int location) {
					currentType = listTypes.at(location);
					currentLocation = lists.at(location).at(0);
					switch (listTypes.at(location)) {
						case 0:
							return numbers.at(lists.at(location).at(0));
							break;
						case 1:
							return strings.at(lists.at(location).at(0));
							break;
						case 2:
							return lists.at(lists.at(location).at(0));
							break;
					}
				}
				void last(unsigned int location) {
					currentType = listTypes.at(location);
					currentLocation = lists.at(location).at(lists.at(location).size()-1);
					switch (listTypes.at(location)) {
						case 0:
							return numbers.at(lists.at(location).at(lists.at(location).size()-1));
							break;
						case 1:
							return strings.at(lists.at(location).at(lists.at(location).size()-1));
							break;
						case 2:
							return lists.at(lists.at(location).at(lists.at(location).size()-1));
							break;
					}
				}
				void newItem(unsigned int location,short unsigned int type = 0) {
					currentType = listTypes.at(0);
					currentLocation = lists.at(location).at(lists.at(location).size());
					switch (listTypes.at(location)) {
						case 0:
							numbers.push_back(0);
							lists.at(location).push_back(numbers.size());
							break;
						case 1:
							strings.push_back("");
							lists.at(location).push_back(strings.size());
							break;
						case 2:
							lists.push_back({});
							std::vector<short unsigned int> futureTypes = listTypes.at(location);
							futureTypes.erase(futureTypes.begin());
							listTypes.push_back(futureTypes);
							lists.at(location).push_back(lists.size());
							break;
					}
				}
			};
		};
		//Output Parsed Turl File
		for (std::string i : turlFile) {
				std::cout << i << std::endl;
		}
}
