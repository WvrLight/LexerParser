#include "saliganParser.h"
using namespace std;

Parser::Parser() {
	parse();
}

int main() {
	Parser parse;
}

void Parser::parse() {	
	currToken = -1;
	indentation = 0;
	
	Lexer lex;
	tokenList = lex.getTokenList();
	
	cout << endl << endl << "PARSE TREE" << endl;
	Programa();
}

void Parser::getNextToken() {
	currToken++;
}

Token Parser::peekToken() {
	return tokenList[currToken+1];
}

void Parser::printGrammar(string grammar, int indent) {
	for (int i = 0; i < indent; i++) {
		cout << INDENT;
	}
	
	cout << "[" << grammar << "]" << endl;
}

void Parser::printCompleteToken(int indent) {
	for (int i = 0; i < indent; i++) {
		cout << INDENT;
	}
	
	cout << "[" << tokenList[currToken].lexeme << ", " << tokenList[currToken].type << "]" << endl;
}

bool Parser::compareTypeTo(string desiredType) {
	if (tokenList[currToken].type.compare(desiredType) == 0) return true;
	else return false;
}

bool Parser::compareNameTo(string desiredName) {
	if (tokenList[currToken].lexeme.compare(desiredName) == 0) return true;
	else return false;
}

bool Parser::Programa() {
	printGrammar("Programa", indentation);
	indentation++;
	
	while (peekToken().lexeme.compare("ITAKDA") == 0) Takda(indentation);
	Func(indentation);
}

bool Parser::Takda(int currInd) {
	printGrammar("Takda", currInd); 
	currInd++;
	
	getNextToken();
	if (compareNameTo("ITAKDA")) {
		printCompleteToken(currInd); 
		
		getNextToken();
		if (compareTypeTo("identifier")) {
			printCompleteToken(currInd);
			
			getNextToken();
			if (compareTypeTo("integer") || compareTypeTo("string") || compareTypeTo("character")) {
				printCompleteToken(currInd);
				return true;
			}
		}
	}
	
	return false;
}

bool Parser::Func(int currInd) {
	printGrammar("Func", currInd); 
	currInd++;
	
	getNextToken();
	if (compareTypeTo("reserved_word")) {
		printCompleteToken(currInd); 
		
		getNextToken();
		if (compareTypeTo("identifier") || compareNameTo("UNA")) {
			printCompleteToken(currInd); 
			
			getNextToken();
			if (compareNameTo("(")) {
				printCompleteToken(currInd); 
				getNextToken();
				if (compareNameTo(")")) {
					printCompleteToken(currInd);
					getNextToken();
					if (compareNameTo("{")) {
						printCompleteToken(currInd);
						
						Stmts(currInd+1);
						
						getNextToken();
						if (compareNameTo("}")) {
							printCompleteToken(currInd);
						}
					}
				}
			}
		}
	}
}

bool Parser::Stmts(int currInd) {
	printGrammar("Stmts", currInd); 
}
