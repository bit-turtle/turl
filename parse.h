#include <vector>
#include <string>
#include <iostream>
#include <sstream>

std::vector<std::vector<std::string>> parse(std::string buffer) {

	std::vector<std::vector<std::string>> result;
	int length = 0;	//Lines read

	std::stringstream bufferstream(buffer);
	std::string line;

	while (getline(bufferstream,line)) {	//Split string into lines

		result.push_back({}); //Add new line to list
		length++; //Add 1 to the length of the list

		std::stringstream linestream(line);

		std::string comment;
		getline(linestream,comment,'#'); //Remove comments '#' is a comment

		std::stringstream commentstream(comment);

		std::string quote;
		bool inquote = false;;
		while (getline(commentstream,quote,'"')) {

			if (!inquote) {

				std::stringstream quotestream(quote);

				std::string word;

				while (getline(quotestream,word,' ')) {	//Split lines into words

					std::stringstream wordstream(word);
					std::string token;

					while (getline(wordstream,token,',')) {	//Split words into tokens

						if (quote != "") result.at(length-1).push_back(token);	//Add tokens to list

					}
				}
			}
			else {
				result.at(length-1).push_back(quote);
			}
			inquote = !inquote;
		}
	}

	for (int i = 0; i < result.size(); i++)
		if (result.at(i).size() == 0) {
			result.erase( result.begin() + i );
			i--;
		}

	return result; //Return parsed list

}
