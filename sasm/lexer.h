#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <cstdint>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State : byte {
	START,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END,
   	 FILE_OPEN, FILE_READ, FILE_WRITE, FILE_CLOSE
};

class Lexer {
	bool my_isSpace(char c);
	bool isSpecial(char c);
	bool isGroup(char c);
	bool isKeyword(const std::string& str);
	char end_char, beg_char;
	public:
	strings lex(std::string s);
};

#endif
