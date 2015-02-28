#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum Messages{
	WELCOME_MESSAGE,
	LINE_ADD_SUCCESS_MESSAGE,
	LINE_FOUND_MESSAGE,
	LINE_NOT_FOUND_MESSAGE,
	FILE_DELETED_MESSAGE,
	FILE_EMPTY_MESSAGE,
	FILE_SORTED_MESSAGE,
	FILE_CONTENT_DELETED_MESSAGE,
	HELP_MESSAGE
};


enum Commands{
	DISPLAY,
	ADD_LINE,
	DELETE_LINE,
	SEARCH_LINE,
	SORT_FILE,
	CLEAR_FILE,
	EXIT_PROGRAM,
	INVALID_COMMAND
};

	Messages readMessageType(string);
	Commands readCommand(string);
	string printMessage(string,string,string);
	string displayText(string);
	void addText(string, string);
	void clearText(string);
	void deleteText(string,string);
	string findText(string, string);
	void sortText(string);
	void checkInput(int, char*[]);
	vector<string> getUserInput();
	