#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TextBuddy.h"

// TextBuddy contains 5+2 fuctions:
// add [sentence] :adds sentence to file
// display :displays contents of file
// delete [lineNumber] :deletes specified line in file
// clear :deletes file contents
// exit :exits program
// 
// sort : sorts lines in alphabetical order
// search [word] : search for line matching word(exact match) in file  
//
// Program Usage: TextBuddy.exe [filePath]

// printMessage handles all the output to user except for displayText() method
string printMessage(string messageType, string message ,string filePath){
	string msgToPrint = "";
	Messages messageCommand = readMessageType(messageType);

	switch(messageCommand){
	case WELCOME_MESSAGE:
		msgToPrint = "\nWelcome to TextBuddy. " + filePath + " is ready for use\n\n"; break;
	case LINE_ADD_SUCCESS_MESSAGE:	
		msgToPrint = "added to " + filePath + ": " + "\"" + message + "\"" + "\n"; break;
	case LINE_FOUND_MESSAGE:
		msgToPrint = "content found at" + message + "\nin file:" + filePath + "\n"; break;
	case LINE_NOT_FOUND_MESSAGE:
		msgToPrint = "content \"" + message + "\"not found \nin file:" + filePath + "\n"; break;
	case FILE_DELETED_MESSAGE:
		msgToPrint = "deleted from " + filePath + ": \"" + message + "\"" + "\n"; break;
	case FILE_EMPTY_MESSAGE:
		msgToPrint = "\n" + filePath + " is empty." + "\n"; break;
	case FILE_SORTED_MESSAGE:
		msgToPrint = "file sorted\n"; break;
	case FILE_CONTENT_DELETED_MESSAGE:
		msgToPrint = "all content deleted from " + filePath + "\n"; break;
	case HELP_MESSAGE:
		msgToPrint = "\ninvalid command!";
		msgToPrint += "\navailable commands:";
		msgToPrint += "\nadd [message]		delete [line number]\nsearch [word]		sort\ndisplay		clear\nexit\n";
	}

	cout << msgToPrint;
	return msgToPrint;
}

Messages readMessageType(string messageType){
	Messages message = HELP_MESSAGE;

	if(messageType == "welcomeMessage"){
		message = WELCOME_MESSAGE;
	} else if(messageType == "lineAddSuccess"){
		message = LINE_ADD_SUCCESS_MESSAGE;
	} else if(messageType == "lineFoundMessage"){	
		message = LINE_FOUND_MESSAGE;
	} else if(messageType == "lineNotFoundMessage"){	
		message = LINE_NOT_FOUND_MESSAGE;
	} else if(messageType == "fileDeletedMessage"){
		message = FILE_DELETED_MESSAGE;
	} else if(messageType == "fileEmpty"){
		message = FILE_EMPTY_MESSAGE;
	} else if(messageType == "fileSortedMessage"){	
		message = FILE_SORTED_MESSAGE;
	} else if(messageType == "fileContentDeleted"){
		message = FILE_CONTENT_DELETED_MESSAGE;
	} else if(messageType == "helpMessage"){
		message = HELP_MESSAGE;
	}
	return message;
}

Commands readCommand(string inputCommand){
	Commands command = INVALID_COMMAND;
	if(inputCommand == "display"){
		command = DISPLAY;
	} else if(inputCommand == "add"){
		command = ADD_LINE;	
	} else if(inputCommand == "search"){
		command = SEARCH_LINE;
	} else if(inputCommand == "sort"){
		command = SORT_FILE;
	} else if(inputCommand == "delete"){
		command = DELETE_LINE;
	} else if(inputCommand == "clear"){
		command = CLEAR_FILE;
	} else if(inputCommand == "exit"){
		command = EXIT_PROGRAM;
	}

	return command;
}

// displayText prints all the contents in the file line by line
// e.g. 1. line one
//		2. line two
string displayText(string filePath) {
	string output = "";
	ifstream inFile (filePath);	
	if (inFile.is_open()) {

		string line;
		int count = 0;

		while( getline(inFile,line) ){

			count++;
			output += "\n" + to_string(count) + ". " + line + "\n";
			cout << output;
		}

		if(count == 0){
			//count==0 => file is empty
			output=printMessage("fileEmpty", "" , filePath);
		}
	}

	inFile.close();
	return output;
}

void addText(string sentence ,string filePath) {
	cout << endl;

	// append new sentence to target file
	ofstream outFile (filePath, ios::app);	

	if (outFile.is_open()) {
		outFile << sentence << "\n";
		printMessage("lineAddSuccess", sentence, filePath);
	}

	outFile.close();

}

void clearText(string filePath) {
	cout << endl;

	const char * TEMP_FILE_PATH = filePath.c_str();
	//remove requires const char* instead of string
	remove(TEMP_FILE_PATH);
	ofstream outFile(filePath);

	printMessage("fileContentDeleted", "", filePath);
}

void deleteText(string lineNumberStr, string filePath) {
	cout << endl;

	int lineToDelete = atoi(lineNumberStr.c_str());

	ifstream inFile (filePath);	
	ofstream outFile("temp");
	if (inFile.is_open()) { 
		string line;
		int currentLine = 0;

		while( getline(inFile,line) ){
			currentLine++;
			if(currentLine == lineToDelete){
				printMessage("fileDeletedMessage", line ,filePath);

			}
			else{
				outFile << line << "\n";
			}
		}

	}

	outFile.close();
	inFile.close();

	//remove and rename requires const char* instead of string
	const char * TEMP_FILE_PATH = filePath.c_str();
	remove(TEMP_FILE_PATH);
	rename("temp", TEMP_FILE_PATH);

}

string findText(string searchString, string filePath) {
	string result;
	cout << endl;

	bool isTextFound = false;

	ifstream inFile (filePath);	
	if (inFile.is_open()) { 

		string line;

		//counter to find line number where searchString is found
		int currentLine = 0;	
		while( !inFile.eof() ){
			getline(inFile,line);
			currentLine++;
			if( line.find(searchString) != string::npos ){
				isTextFound = true;
				break;
			}
		}
		if(isTextFound){
			line = " " + to_string(currentLine) + ". " + line+" ";
			result = printMessage("lineFoundMessage", line ,filePath);
		}
		else{
			result = printMessage("lineNotFoundMessage", searchString , filePath);
		}
	}
	inFile.close();
	return result;
}

// sortText rearranges text file lines in alphabetical order
void sortText(string filePath) {
	cout << endl;

	ifstream inFile (filePath);	
	ofstream outFile("sortedFile");
	if (inFile.is_open()) {
		string line;
		int currentLine = 0;
		vector<string> fileLines;

		while( !inFile.eof() ){
			getline(inFile,line);
			currentLine++;
			fileLines.push_back(line);
		}
		fileLines.pop_back();
		sort(fileLines.begin(),fileLines.end());


		ostream_iterator<string> output_iterator(outFile, "\n");
		copy(fileLines.begin(), fileLines.end(), output_iterator);
	}

	printMessage("fileSortedMessage", "", filePath);

	outFile.close();
	inFile.close();

	//remove and rename requires const char* instead of string
	const char * TEMP_FILE_PATH = filePath.c_str();
	remove(TEMP_FILE_PATH);
	rename("sortedFile",TEMP_FILE_PATH);

}

// checkInput determines if number of user input is correct
void checkInput(int argc, char* argv[]){
	if(argc != 2){
		cout << "usage: TextBuddy.exe [filepath]" << endl;
		exit(1);
	}
	else{
		printMessage("welcomeMessage", "" ,argv[1]);
	}
}

vector<string> getUserInput(){
	vector<string> userInputVector(2);
	string userInput;

	cout << "command: ";
	getline(cin, userInput);

	userInputVector[0] = userInput.substr(0,userInput.find(" "));
	userInputVector[1] = userInput.substr(userInput.find(" ")+1);

	return userInputVector;
}
int main(int argc, char* argv[]){
	// testing purposes only
	argc = 2;
	argv[1] = "temp.txt";
	// testing end

	checkInput(argc,argv);

	string command;
	string option;
	vector<string> inputList;
	string filePath;

	filePath = argv[1];



	bool isExitCommand = false;
	while(!isExitCommand){

		inputList = getUserInput();		
		option = inputList[1];

		//_ASSERT(command=="display"||command=="add"||command=="delete"||command=="clear"||command=="exit");


		Commands command = readCommand(inputList[0]);

		switch(command){
			case DISPLAY:		displayText(filePath); break;
			case ADD_LINE:		addText(option, filePath); break;
			case DELETE_LINE:	deleteText(option, filePath); break;
			case SEARCH_LINE:	findText(option, filePath); break;
			case SORT_FILE:		sortText(filePath); break;
			case CLEAR_FILE:	clearText(filePath); break;
			case EXIT_PROGRAM:	isExitCommand=true; break;
			case INVALID_COMMAND: printMessage("helpMessage", "" , filePath); break;
		}


		//prevent console from closing automatically
		cout << endl;
	} //while loop end

	cin.get();
	exit(0);
}

// method not used
/*
   void runTests(string filePath){
//_ASSERT("\nWelcome to TextBuddy. "+filePath+" is ready for use\n" , printMessage("welcomeMessage", "" , filePath));
}
*/
