#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <vector>

// Token struct
struct Token {
	std::string lexeme;
	std::string type;
	
	Token(char token[], std::string newType) {
		lexeme = token;
		type = newType;
	}
};

#endif
