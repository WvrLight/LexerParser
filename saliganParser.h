#ifndef SALIGANPARSER_H
#define SALIGANPARSER_H

#include "saliganLexer.h"

#define INDENT "\t"

class Parser {
	public:
		explicit Parser();
	private:
		std::vector<Token> tokenList;
		int currToken;
		int indentation;

		void parse();
		void getNextToken();
		Token peekToken();
		void printGrammar(std::string type, int indent);
		void printCompleteToken(int indent);
		bool compareTypeTo(std::string desiredType);
		bool compareNameTo(std::string desiredName);
		bool Programa();
		bool Takda(int currInd);
		bool Func(int currInd);
		bool Stmts(int currInd);
};

#endif
