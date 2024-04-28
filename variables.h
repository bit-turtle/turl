#include <vector>
#include <string>

//Numbers
struct number {
	std::string name;
	int value;
};

std::vector<number> numbers;

bool numberExists(std::string name) {
	for (int i = 0; i < numbers.size(); i++)
		if (numbers.at(i).name == name) return true;
	return false;
}

void createNumber(std::string name) {
	numbers.push_back(number{name,0});
}

int getNumber(std::string name) {
	for (int i = 0; i < numbers.size(); i++)
		if (numbers.at(i).name == name) return i;
	return -1;
}

//Strings
struct string {
	std::string name;
	std::string value;
};

std::vector<string> strings;

bool stringExists(std::string name) {
	for (int i = 0; i < strings.size(); i++)
		if (strings.at(i).name == name) return true;
	return false;
}

void createString(std::string name) {
	strings.push_back(string{name,""});
}

int getString(std::string name) {
	for (int i = 0; i < strings.size(); i++)
		if (strings.at(i).name == name) return i;
	return -1;
}

//Locations
struct location {
	std::string name;
	int line;
};

std::vector<location> locations;

int getLocation(std::string name) {
	for (int i = 0; i < locations.size(); i++)
		if (locations.at(i).name == name) return i;
	return -1;
}

bool locationExists(std::string name) {
	for (location loc : locations)
		if (loc.name == name) return true;
	return false;
}
