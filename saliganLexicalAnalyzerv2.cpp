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

// Token struct
struct Token {
	string lexeme;
	string type;
	
	Token(char token[], string newType) {
		lexeme = token;
		type = newType;
	}
};

// Function declarations
void clearToken(char token[], int *tokenSize, int *tokenType);
char getNextChar(char *ch);
void checkToken(bool *state, char token[], int tokenSize, string type);
void writeToken(char token[], string type);
vector<Token> getTokenList();

// Global variables
ifstream file;
ofstream symbolTable;
vector<Token> tokenList;

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
	// Defining the variables
	char ch, token[MAXTOKENSIZE], operators[] = "+-*/%=<>@^";
	string fileLoc;
	int tokenSize = 0;
	int tokenType = 0;
	int commentType = -1;
	
	// Defining the filepaths
	do {
		cout << "Input a .sal program: ";
		cin >> fileLoc;
		size_t ext = fileLoc.find(".sal");
		if (ext == string::npos) cout << endl << "Invalid filetype! Please use source code with the .sal suffix." << endl << endl;
		else {
			string fileExt = fileLoc.substr(ext);
		
			if (fileExt != ".sal") cout << endl << "Invalid filetype! Please use source code with the .sal suffix." << endl << endl;
			else {
				file.open(fileLoc.c_str());
				
				// Check if file exists
				if (!file.is_open()) cout << "Error! File cannot be found.\n" << endl;
				else {
					symbolTable.open("symbolTable.slg", ofstream::out | ofstream::trunc);
					symbolTable << setw(10) << left << "<TOKEN>" << TAB << "<TYPE>" << endl;
					
					cout << endl << "Program successfully found." << endl << "Writing symbol table..." << endl << endl;
					break;
				}
			}
		}
	} while (1);
	
	// Parse the file
	while (!file.eof()) {
		ch = file.get();
			
		// IDENTIFIERS
		// If identifier already detected, parse through every character of the identifier
		if (tokenType == 0 && ch == '_') {
			token[tokenSize++] = ch;
			tokenType == 2;
			
			bool state = false;
			
			while (isalnum(file.peek()) || file.peek() == '_') {
				token[tokenSize++] = getNextChar(&ch);
			}
			
			if (token[tokenSize - 1] != '_') {
				checkToken(&state, token, tokenSize, "identifier");
			}
			
			if (state == false) {
				token[tokenSize] = '\0';
				writeToken(token, "INVALID");
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
			
		// WORDS
		// Initial detection
		else if ((tokenType == 0) && (isalpha(ch) || ch == '.')) {
			token[tokenSize++] = ch;
			tokenType = 1;
			
			bool state = false;
			
			// KEY_WORDS
			if (token[0] == 'K') {
				if (file.peek() == 'U') {
					token[tokenSize++] = getNextChar(&ch);
				
					if (file.peek() == 'N') {
						token[tokenSize++] = getNextChar(&ch);
					
						if (file.peek() == 'G') {
							token[tokenSize++] = getNextChar(&ch);
						
							if (file.peek() == 'D') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'I') {
									token[tokenSize++] = getNextChar(&ch);
									
									checkToken(&state, token, tokenSize, "key_word");
								}
							}
							else checkToken(&state, token, tokenSize, "key_word");
						}
					}
				}
				else if (file.peek() == 'A') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'Y') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'A') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "noise_word");
						}
					}
				}
			}
			else if (token[0] == 'I')  {
				if (file.peek() == 'B') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'A') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'L') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'I') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'K') {
									token[tokenSize++] = getNextChar(&ch);
									
									checkToken(&state, token, tokenSize, "key_word");
								}
							}
						}
						else checkToken(&state, token, tokenSize, "key_word");
					}
				}
				else if (file.peek() == 'L') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'A') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'G') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'A') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'Y') {
									token[tokenSize++] = getNextChar(&ch);
									
									if (file.peek() == '.') {
										token[tokenSize++] = getNextChar(&ch);
										
										if (file.peek() == 'S') {
											token[tokenSize++] = getNextChar(&ch);
											
											if (file.peek() == 'A') {
												token[tokenSize++] = getNextChar(&ch);
												
												checkToken(&state, token, tokenSize, "key_word");
											}
										}
									}
								}
							}
						}
						else if (file.peek() == 'B') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'A') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'S') {
									token[tokenSize++] = getNextChar(&ch);
									
									if (file.peek() == '.') {
										token[tokenSize++] = getNextChar(&ch);
										
										if (file.peek() == 'A') {
											token[tokenSize++] = getNextChar(&ch);
											
											if (file.peek() == 'N') {
												token[tokenSize++] = getNextChar(&ch);
												
												if (file.peek() == 'G') {
													token[tokenSize++] = getNextChar(&ch);
													
													checkToken(&state, token, tokenSize, "key_word");
												}
											}
										}
									}
								}
							}
						}	
					}
				}
				else if (file.peek() == 'T') {
					token[tokenSize++] = getNextChar(&ch);
				
					if (file.peek() == 'A') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'K') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'D') {
									token[tokenSize++] = getNextChar(&ch);
									
									if (file.peek() == 'A') {
										token[tokenSize++] = getNextChar(&ch);
										
										checkToken(&state, token, tokenSize, "key_word");
									}
								}
						}	
					}
				}					
			}
			else if (token[0] == 'T') {			
				if (file.peek() == 'I') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'G') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'I') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'L') {
								token[tokenSize++] = getNextChar(&ch);
								
								checkToken(&state, token, tokenSize, "key_word");
							}
						}
					}
				}
				else if (file.peek() == 'A') {
					token[tokenSize++] = getNextChar(&ch);
								
					if (file.peek() == 'M') {
							token[tokenSize++] = getNextChar(&ch);
								
							if (file.peek() == 'A') {
								token[tokenSize++] = getNextChar(&ch);
								
								checkToken(&state, token, tokenSize, "boolean");
							}
						}
					}
				}
			else if (token[0] == 'M') {			
				if (file.peek() == 'A') {
					token[tokenSize++] = getNextChar(&ch);
								
					if (file.peek() == 'L') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'I') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "boolean");
						}
					}
				}
			}
			else if (token[0] == 'P') {
				if (file.peek() == 'A') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'R') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'A') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == '.') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'S') {
									token[tokenSize++] = getNextChar(&ch);
									
									if (file.peek() == 'A') {
										token[tokenSize++] = getNextChar(&ch);
						
										checkToken(&state, token, tokenSize, "key_word");
									}
								}
							}
						}
					}
				}				
			}
			else if (token[0] == 'B') {
				if (file.peek() == 'L') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'A') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'N') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'K') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'O') {
									token[tokenSize++] = getNextChar(&ch);
						
									checkToken(&state, token, tokenSize, "key_word");
								}
							}
						}
					}
				}				
			}
			else if (token[0] == 'U') {
				if (file.peek() == 'N') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'A') {
						token[tokenSize++] = getNextChar(&ch);
						
						checkToken(&state, token, tokenSize, "key_word");
					}
				}					
			}
			
			// RESERVED_WORDS
			else if (token[0] == 'n') {
				if (file.peek() == 'u') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'm') {
						token[tokenSize++] = getNextChar(&ch);
						
						checkToken(&state, token, tokenSize, "reserved_word");
					}
				}					
			}
			else if (token[0] == 'b') {
				if (file.peek() == 'i') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'l') {
						token[tokenSize++] = getNextChar(&ch);
						
						checkToken(&state, token, tokenSize, "reserved_word");
					}
				}
				else if (file.peek() == 'o')	{
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'o') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'l') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "reserved_word");
						}
					}	
				}				
			}	
			else if (token[0] == 'd') {
				if (file.peek() == 'e') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 's') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'i') {
							token[tokenSize++] = getNextChar(&ch);
						
							checkToken(&state, token, tokenSize, "reserved_word");
						}	
					}
				}					
			}	
			else if (token[0] == 'l') {
				if (file.peek() == 'e') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 't') {
						token[tokenSize++] = getNextChar(&ch);
						
						checkToken(&state, token, tokenSize, "reserved_word");
					}
				}					
			}		
			else if (token[0] == 'k') {
				if (file.peek() == 'a') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 't') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'a') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'g') {
								token[tokenSize++] = getNextChar(&ch);
								
								if (file.peek() == 'a') {
									token[tokenSize++] = getNextChar(&ch);
						
									checkToken(&state, token, tokenSize, "reserved_word");
								}
							}
						}
					}
				}					
			}			
			else if (token[0] == 'v') {
				if (file.peek() == 'o') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'i') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'd') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "reserved_word");
						}
					}	
				}
			}			
			else if (token[0] == 'G') {
				if (file.peek() == 'A') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'W') {
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'I') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'N') {
								token[tokenSize++] = getNextChar(&ch);
						
								checkToken(&state, token, tokenSize, "noise_word");
							}
						}
					}
				}					
			}
			
			// LOGICAL_OPERATORS
			else if (token[0] == 'A') {
				if (file.peek() == 'T') {
					token[tokenSize++] = getNextChar(&ch);
					checkToken(&state, token, tokenSize, "logical_operator");
				}
			}
			else if (token[0] == 'O') {
				checkToken(&state, token, tokenSize, "logical_operator");
			}
			else if (token[0] == 'H') {
				if (file.peek() == 'I') {
					token[tokenSize++] = getNextChar(&ch);
					
					if (file.peek() == 'N'){
						token[tokenSize++] = getNextChar(&ch);
						
						if (file.peek() == 'D') {
							token[tokenSize++] = getNextChar(&ch);
							
							if (file.peek() == 'I') {
								token[tokenSize++] = getNextChar(&ch);
								
								checkToken(&state, token, tokenSize, "logical_operator");
							}
					    }
					}
				}    	
			}
			
			if (state == false) {
				token[tokenSize] = '\0';
				symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// CHARACTERS
		else if (tokenType == 0 && ch == '\'' && tokenSize == 0) {
			token[tokenSize++] = ch;
			token[tokenSize] = '\0';
			
			writeToken(token, "delimiter");
		
			clearToken(token, &tokenSize, &tokenType);
			tokenType = 3;
			
			ch = file.get();
				
			if (tokenType == 3 && ch != '\'') {
				token[tokenSize++] = ch;
				
				ch = file.get();
			
				if (tokenType == 3 && ch == '\'') {
					token[tokenSize] = '\0';
					writeToken(token, "character");
					clearToken(token, &tokenSize, &tokenType);
					
					token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					writeToken(token, "delimiter");
				
				}
				else {
					writeToken(token, "INVALID");
				}
			}
			// If character after ' is immediately '
			else if (tokenType == 3 && ch == '\'') {
				
				token[tokenSize++] = ch;
				token[tokenSize] = '\0';
				
				writeToken(token, "delimiter");
			}
			else {
				writeToken(token, "INVALID");
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// STRINGS
		// Detect the first character of a string
		else if (tokenType == 0 && ch == '"' && tokenSize == 0) {
			token[tokenSize++] = ch;
			token[tokenSize] = '\0';
			
			writeToken(token, "delimiter");
		
			clearToken(token, &tokenSize, &tokenType);
			
			tokenType = 4;
			
			while (!file.eof()) {
				ch = file.get();
				
				if (tokenType == 4 && (isalnum(ch) || ch == ' ')) {
					token[tokenSize++] = ch;
				}
				else if (tokenType == 4 && ch == '"') {
					token[tokenSize] = '\0';
					writeToken(token, "string");
					clearToken(token, &tokenSize, &tokenType);
					
					token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					writeToken(token, "delimiter");
				
					clearToken(token, &tokenSize, &tokenType);
					
					break;
				}
			}
			
			// Check if string is incomplete
			if (isalnum(token[0])) {
				token[tokenSize] = '\0';
				
				writeToken(token, "INVALID");
				clearToken(token, &tokenSize, &tokenType);
			}
		}

		// NUMBERS
		else if (tokenType == 0 && isdigit(ch)) {
			token[tokenSize++] = ch;
			tokenType = 5;
			bool isFloat = false;
			bool state = true;
			
			while (isdigit(getNextChar(&ch)) || ch == '.') {
				
				
				if (isdigit(ch)) token[tokenSize++] = ch;
				else if (ch == '.') {
					token[tokenSize++] = ch;
					isFloat = true;
				}
				else {
					state = false;
				}
			}
			
			if (state == false) {
				token[tokenSize] = '\0';
				writeToken(token, "INVALID");
			}
			else {
				token[tokenSize] = '\0';
				if (isFloat == false) writeToken(token, "integer");

				else writeToken(token, "float");
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
		
		// SYMBOLS
		else if (tokenType == 0 && !isalnum(ch)) {
			if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') {
		            token[tokenSize++] = ch;
					token[tokenSize] = '\0';
					
					if (ch == ';') writeToken(token, "terminator");
					else if (ch == ',') writeToken(token, "separator");
					else writeToken(token, "delimiter");
				
					clearToken(token, &tokenSize, &tokenType);
		    }
		// ARITHMETIC/BOOLEAN/ASSIGNMENT OPERATOR/COMMENT
		    else {
		    	// Check if character is within character set
				bool inSet = false;
				
				for (int i = 0; i < 10; i++) {
				    if (ch == operators[i]) {
					   	token[tokenSize++] = ch;
						tokenType = 10;
						inSet = true;
				    }
	   			}
				
				if (inSet) {
					bool state = false;
					if (token[0] == '+') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '-') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
						else if (file.peek() == '-') {
							token[tokenSize++] = getNextChar(&ch);
							
							state = true;
							writeToken(token, "comment delimiter");
							tokenType = 7;
							commentType = 0;
						}
						else if (file.peek() == '>') {
							token[tokenSize++] = getNextChar(&ch);
							
							state = true;
							writeToken(token, "comment delimiter");
							commentType = 2;
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '<') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "relational_operator");
						}
						else if (file.peek() == '-') {
							token[tokenSize++] = getNextChar(&ch);
							
							state = true;
							writeToken(token, "comment delimiter");
							tokenType = 7;
							commentType = 1;
						}
						else {
							checkToken(&state, token, tokenSize, "relational_operator");
						}
					}
					else if (token[0] == '>') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							
							checkToken(&state, token, tokenSize, "relational_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "relational_operator");
						}
					}
					else if (token[0] == '=') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							checkToken(&state, token, tokenSize, "relational_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
					}
					else if (token[0] == '/') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							if (file.peek() == '/') {
								token[tokenSize++] = getNextChar(&ch);
								checkToken(&state, token, tokenSize, "relational_operator");
							}
							else {
								checkToken(&state, token, tokenSize, "assignment_operator");
							}
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '*') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '%') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '@') {
						if (file.peek() == '=') {
							token[tokenSize++] = getNextChar(&ch);
							checkToken(&state, token, tokenSize, "assignment_operator");
						}
						else {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
						}
					}
					else if (token[0] == '^') {
							checkToken(&state, token, tokenSize, "arithmetic_operator");
					}
					
					if (state == false) {
						token[tokenSize] = '\0';
						symbolTable << setw(10) << left << token << TAB << "INVALID" << endl;
					}
					
					if (tokenType != 7) clearToken(token, &tokenSize, &tokenType);
					else {
						clearToken(token, &tokenSize, &tokenType);
						tokenType = 7;
					}
				}
			}
		}
		
		// COMMENT STRING
		if (tokenType == 7) {
			while (tokenType == 7 && commentType != -1) {
			if (!file.eof()) ch = file.get();
			
			// For singleline comment end
			if (commentType == 0) {
				if (file.peek() == '\n' || file.peek() == EOF) {
					token[tokenSize++] = ch;
					token[tokenSize] = '\0';
				
					writeToken(token, "comment string");
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
				
							writeToken(token, "comment string");
							clearToken(token, &tokenSize, &tokenType);	
							
							token[tokenSize++] = ch;
							token[tokenSize++] = file.get();
							token[tokenSize] = '\0';
							
							writeToken(token, "comment delimiter");
							clearToken(token, &tokenSize, &tokenType);
						}
						else token[tokenSize++] = ch;
					}
					else token[tokenSize++] = ch;
				}
			}
			
			clearToken(token, &tokenSize, &tokenType);
		}
	}
	
	file.close();
	symbolTable.close();
	
	cout << "Symbol table successfully written to symbolTable.slg.";
	return 0;
}

// FUNCTIONS

// Removes all information about the token
void clearToken(char token[], int *tokenSize, int *tokenType) {
	memset(&(token[0]), 0, MAXTOKENSIZE);
	*tokenSize = 0;
	*tokenType = 0;
}

char getNextChar(char *ch) {
	if (!file.eof()) {
		*ch = file.get();
		return *ch;
	}
	else return 0;
	
}

void checkToken(bool *state, char token[], int tokenSize, string type) {
	*state = true;
	
	if (file.peek() == ' ' || file.peek() == '\n' || file.peek() == EOF || file.peek() == ',' || file.peek() == ';' || file.peek() == '(' || file.peek() == ')' || file.peek() == '[' || file.peek() == ']' || file.peek() == '{' || file.peek() == '}') {
		token[tokenSize] = '\0';
		writeToken(token, type);
	}
	else {
		while (file.peek() != ' ' && file.peek() != '\n' && file.peek() != EOF && file.peek() != ',' && file.peek() != ';' && file.peek() != '(' && file.peek() != ')' && file.peek() != '[' && file.peek() != ']' && file.peek() != '{' && file.peek() != '}') {
			char ch = file.get();
			token[tokenSize++] = ch;
		}
		
		token[tokenSize] = '\0';
		writeToken(token, "INVALID");
	}	
}

void writeToken(char token[], string type) {
	symbolTable << setw(10) << left << token << TAB << type << endl;
	
	if (strcmp(type.c_str(), "comment string") != 0 && strcmp(type.c_str(), "comment delimiter") != 0) {
		Token newToken(token, type);
		tokenList.push_back(newToken);
	}
}

vector<Token> getTokenList() {
	for (int i = 0; i < tokenList.size(); i++) {
		cout << tokenList[i].lexeme << endl;
	}
	
	return tokenList;
}
