#ifndef SALIGANLEXER_H
#define SALIGANLEXER_H

#include "token.h"

#define TAB "\t\t\t\t\t\t"
#define MAXTOKENSIZE 30

class Lexer {
	public:
		explicit Lexer();
		std::vector<Token> getTokenList();
	private:
		std::ifstream file;
		std::ofstream symbolTable;
		std::vector<Token> tokenList;
		
		void clearToken(char token[], int *tokenSize, int *tokenType);
		char getNextChar(char *ch);
		void checkToken(bool *state, char token[], int tokenSize, std::string type);
		void writeToken(char token[], std::string type);
		void lex();
};

#endif
