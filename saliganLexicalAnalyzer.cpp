#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <vector>

#define TAB "\t\t\t\t\t\t"
#define MAXTOKENSIZE 30

using namespace std;

struct Node {
	char ch;
	struct Node *next;
};

// Function declarations
int parseWord(string token);
int parseSymbol(string token);
vector<Node> createLinkedList(string nodes);
void checkList(string token, vector< vector<Node> > list, int *result, int successType);
void clearToken(char token[], int *tokenSize, int *tokenType);

// Global variables
vector< vector<Node> > keywordList;
vector< vector<Node> > reservedwordList;
vector< vector<Node> > noisewordList;

vector< vector<Node> > logOpList;
vector< vector<Node> > arOpList;
vector< vector<Node> > boolOpList;
vector< vector<Node> > assOpList;

vector< vector<Node> > commentList;

/* TOKEN TYPES
	-1 - invalid
	0 - empty
	1 - word
	2 - identifier 
	3 - character
	4 - string
	5 - number
	6 - comment
	7 - comment string
	10 - assignment/boolean/arithmetic operator
	11 - logical operator
	12 - delimiter
*/

int main() {
	// DEFINE WORDS HERE
	reservedwordList.push_back(createLinkedList("num"));
	reservedwordList.push_back(createLinkedList("bil"));
	reservedwordList.push_back(createLinkedList("desi"));
	reservedwordList.push_back(createLinkedList("let"));
	reservedwordList.push_back(createLinkedList("kataga"));
	
	keywordList.push_back(createLinkedList("KUNG"));
	keywordList.push_back(createLinkedList("KUNGDI"));
	keywordList.push_back(createLinkedList("IBA"));
	keywordList.push_back(createLinkedList("PARA.SA"));
	keywordList.push_back(createLinkedList("ILAGAY.SA"));
	keywordList.push_back(createLinkedList("ILABAS.ANG"));
	keywordList.push_back(createLinkedList("TIGIL"));
	keywordList.push_back(createLinkedList("IBALIK"));
	keywordList.push_back(createLinkedList("BLANKO"));
	keywordList.push_back(createLinkedList("UNA"));
	keywordList.push_back(createLinkedList("ITAKDA"));
	
	noisewordList.push_back(createLinkedList("KAYA"));
	noisewordList.push_back(createLinkedList("GAWIN"));
	
	logOpList.push_back(createLinkedList("AT"));
	logOpList.push_back(createLinkedList("O"));
	logOpList.push_back(createLinkedList("HINDI"));
	
	arOpList.push_back(createLinkedList("+"));
	arOpList.push_back(createLinkedList("-"));
	arOpList.push_back(createLinkedList("*"));
	arOpList.push_back(createLinkedList("/"));
	arOpList.push_back(createLinkedList("%"));
	arOpList.push_back(createLinkedList("@"));
	arOpList.push_back(createLinkedList("^"));
	
	boolOpList.push_back(createLinkedList("<"));
	boolOpList.push_back(createLinkedList("<="));
	boolOpList.push_back(createLinkedList(">"));
	boolOpList.push_back(createLinkedList(">="));
	boolOpList.push_back(createLinkedList("=="));
	boolOpList.push_back(createLinkedList("/=/"));
	
	assOpList.push_back(createLinkedList("="));
	assOpList.push_back(createLinkedList("+="));
	assOpList.push_back(createLinkedList("-="));
	assOpList.push_back(createLinkedList("*="));
	assOpList.push_back(createLinkedList("/="));
	assOpList.push_back(createLinkedList("%="));
	assOpList.push_back(createLinkedList("@="));
	
	commentList.push_back(createLinkedList("--"));
	commentList.push_back(createLinkedList("<-"));
	commentList.push_back(createLinkedList("->"));
	
	// Defining the variables
	char ch, token[MAXTOKENSIZE], operators[] = "+-*/%=<>@";
	int tokenSize = 0;
	int tokenType = 0;
	int commentType;
	
	// Defining the filepaths
	ifstream file("program.sal");
	ofstream symbolTable;
	symbolTable.open("symbolTable.slg", ofstream::out | ofstream::trunc);
	symbolTable << setw(10) << left << "<TOKEN>" << TAB << "<TYPE>" << endl;
	
	// Check if file exists
	if (!file.is_open()) {
		cout << "Error! File cannot be found.\n";
		exit(0);
	}
	else cout << "Program successfully found." << endl << "Writing symbol table..." << endl << endl;
	
	// Parse the file
	while (!file.eof()) {
		ch = file.get();
			
		// IDENTIFIERS
		// If identifier already detected, parse through every character of the identifier
		if (tokenType == 2 && (isalnum(ch) || ch == '_')) {
			token[tokenSize++] = ch;
		}
		else if (tokenType == 2) {
			token[tokenSize] = '\0';
			
			if (!isalnum(token[1])) {
				symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
				tokenType = -1;
			}
			else {
				symbolTable << setw(10) << left << token << TAB << "identifier" << endl;
			}
		
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// Detect the first character of an identifier
		if (tokenType == 0 && ch == '_') {
			token[tokenSize++] = ch;
			tokenType = 2;
		}
			
		// KEYWORDS
		if ((tokenType == 0 || tokenType == 1) && (isalpha(ch) || ch == '.')) {
			token[tokenSize++] = ch;
			tokenType = 1;
		}
		else if (tokenType == 1) {
			token[tokenSize] = '\0';
		 
			switch (parseWord(token)) {
				case 1:
					symbolTable << setw(10) << left << token << TAB << "key_word" << endl;
					break;
				case 2:
					symbolTable << setw(10) << left << token << TAB << "reserved_word" << endl;
					break;
				case 3:
					symbolTable << setw(10) << left << token << TAB << "noise_word" << endl;
					break;
				case 4:
					symbolTable << setw(10) << left << token << TAB << "logical_operator" << endl;
					break;
				default:
					symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// CHARACTERS
		if (tokenType == 0 && ch == '\'' && tokenSize == 0) {
			token[tokenSize++] = ch;
			token[tokenSize] = '\0';
			
			symbolTable << token << TAB << "delimiter" << endl;
		
			clearToken(token, &tokenSize, &tokenType);
			
			tokenType = 3;
			
			ch = file.get();
				
			if (tokenType == 3 && ch != '\'') {
				token[tokenSize++] = ch;
				
				ch = file.get();
			
				if (tokenType == 3 && ch == '\'') {
					token[tokenSize] = '\0';
					symbolTable << setw(10) << left << token << TAB << "character" << endl;
					clearToken(token, &tokenSize, &tokenType);
					
					token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					symbolTable << setw(10) << left << token << TAB << "delimiter" << endl;
				
				}
				else {
					symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
				}
			}
			// If character after ' is immediately '
			else if (tokenType == 3 && ch == '\'') {
				
				token[tokenSize++] = ch;
				token[tokenSize] = '\0';
				
				symbolTable << setw(10) << left << token << TAB << "delimiter";
			}
			else {
				symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// STRINGS
		// Detect the first character of a string
		if (tokenType == 0 && ch == '"' && tokenSize == 0) {
			token[tokenSize++] = ch;
			token[tokenSize] = '\0';
			
			symbolTable << setw(10) << left << token << TAB << "delimiter" << endl;
		
			clearToken(token, &tokenSize, &tokenType);
			
			tokenType = 4;
			
			while (!file.eof()) {
				ch = file.get();
				
				if (tokenType == 4 && (isalnum(ch) || ch == ' ')) {
					token[tokenSize++] = ch;
				}
				else if (tokenType == 4 && ch == '"') {
					token[tokenSize] = '\0';
					symbolTable << setw(10) << left << token << TAB << "string" << endl;
					clearToken(token, &tokenSize, &tokenType);
					
					token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					symbolTable << setw(10) << left << token << TAB << "delimiter" << endl;
				
					clearToken(token, &tokenSize, &tokenType);
					
					break;
				}
			}
			
			// Check if string is incomplete
			if (isalnum(token[0])) {
				token[tokenSize] = '\0';
				
				symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
				clearToken(token, &tokenSize, &tokenType);
			}
		}

		// NUMBERS
		if ((tokenType == 0 || tokenType == 5) && (isdigit(ch) || ch == '.')) {
			token[tokenSize++] = ch;
			tokenType = 5;
		}
		else if (tokenType == 5) {
			token[tokenSize] = '\0';
			symbolTable << setw(10) << left << token << TAB << "number" << endl;
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// SYMBOLS
		if (tokenType == 0 && !isalnum(ch)) {
			if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') {
		            token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					symbolTable << setw(10) << left << token << TAB << "delimiter" << endl;
				
					clearToken(token, &tokenSize, &tokenType);
		        }
		}
		
		// ARITHMETIC/BOOLEAN/ASSIGNMENT OPERATOR/COMMENT
		if ((tokenType == 0 || tokenType == 10) && !isalnum(ch)) {
			// Check if character is within character set
			bool inSet = false;
			
			for (int i = 0; i < 9; i++) {
			    if (ch == operators[i]) {
				   	token[tokenSize++] = ch;
					tokenType = 10;
					inSet = true;
			    }
   			}
   			
   			if (inSet == false && tokenSize > 0) {
				token[tokenSize] = '\0';
 
				switch (parseSymbol(token)) {
					case 1:
						symbolTable << setw(10) << left << token << TAB << "arithmetic_operator" << endl;
						break;
					case 2:
						symbolTable << setw(10) << left << token << TAB << "boolean_operator" << endl;
						break;
					case 3:
						symbolTable << setw(10) << left << token << TAB << "assignment_operator" << endl;
						break;
					case 4:
						tokenType = 6;
						break;
					default:
						symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
				}
				
				if (tokenType != 6) clearToken(token, &tokenSize, &tokenType);
			}
		}
		
		// COMMENTS
		if (tokenType == 6) {
			string tempToken = token;
			commentType = -1;

			// Determine comment type
			for (int i = 0; i < commentList.size(); i++) {
				if (commentType == -1 && commentList[i].begin()->ch == tempToken[0]) {
					for (int j = 0; j < tempToken.length(); j++) {
						if (tempToken[j] == commentList[i][j].ch) commentType = i;
						else commentType = -1;
					}
				}
			}
			
			token[tokenSize] = '\0';
			symbolTable << setw(10) << left << token << TAB << "comment delimiter" << endl;
			clearToken(token, &tokenSize, &tokenType);
			
			if (commentType == 0 || commentType == 1) tokenType = 7;
			else tokenType = 0;
		}
		
		// COMMENT STRING
		if (tokenType == 7) {
			// For singleline comment end
			if (commentType == 0) {
				if (ch == '\n' || file.peek() == EOF)  {
					token[tokenSize] = '\0';
				
					symbolTable << setw(10) << left << token << TAB << "comment string" << endl;
					clearToken(token, &tokenSize, &tokenType);
					commentType = -1;
				}
				else token[tokenSize++] = ch;
			}
			// For multiline comment end
			else {
					if (ch == '-') {
						if (file.peek() == '>') {
							token[tokenSize] = '\0';
				
							symbolTable << setw(10) << left << token << TAB << "comment string" << endl;
							clearToken(token, &tokenSize, &tokenType);	
							
							token[tokenSize++] = ch;
							token[tokenSize++] = file.get();
							token[tokenSize] = '\0';
							
							symbolTable << setw(10) << left << token << TAB << "comment delimiter" << endl;
							clearToken(token, &tokenSize, &tokenType);
						}
						else token[tokenSize++] = ch;
					}
					else token[tokenSize++] = ch;
				}
		}
	}
	
	file.close();
	symbolTable.close();
	
	cout << "Symbol table successfully written to symbolTable.slg.";
	return 0;
}

// Function for checking if token matches the keywords
// Check the first letter of each keyword if it matches the token's first letter, if so, check every letter of the token if it matches the keyword
// -1 - INVALID
// 1 - keyword
// 2 - reserved word
// 3 - noise word
// 4 - logical operator
int parseWord(string token) {
	int result = -1;
	
	checkList(token, keywordList, &result, 1);
	checkList(token, reservedwordList, &result, 2);
	checkList(token, noisewordList, &result, 3);
	checkList(token, logOpList, &result, 4);
	
	return result;
}

// Function for checking if token matches a symbol
// Check the first char of each symbol if it matches the token's first char, if so, check every letter of the token if it matches the symbol
// -1 - INVALID
// 1 - arithmetic operator
// 2 - boolean operator
// 3 - assignment operator
// 4 - comment
int parseSymbol(string token) {
	int result = -1;
	
	checkList(token, arOpList, &result, 1);
	checkList(token, boolOpList, &result, 2);
	checkList(token, assOpList, &result, 3);
	checkList(token, commentList, &result, 4);
	
	return result;
}

// Function for automatically creating a linked list given a string
vector<Node> createLinkedList(string nodes) {
	vector<Node> linkedList;
	
	Node* tempNode = new Node();
	for (int i = 0; i < nodes.length(); i++) {
		
		tempNode->ch = nodes[i];
		if (i != 0) linkedList.back().next = tempNode;
		
		linkedList.push_back(*tempNode);
	}
	
	return linkedList;
}

// Function for looping through a list of linked lists, and returning if the token matches
void checkList(string token, vector< vector<Node> > list, int *result, int successType) {
	if (*result == -1) for (int i = 0; i < list.size(); i++) {
		if (*result == -1 && list[i].begin()->ch == token[0] && list[i].size() == token.length()) {
			for (int j = 0; j < token.length(); j++) {
				if (token[j] == list[i][j].ch) *result = successType;
				else *result = -1;
			}
		}
	}
}

// Removes all information about the token
void clearToken(char token[], int *tokenSize, int *tokenType) {
	memset(&(token[0]), 0, MAXTOKENSIZE);
	*tokenSize = 0;
	*tokenType = 0;
}
