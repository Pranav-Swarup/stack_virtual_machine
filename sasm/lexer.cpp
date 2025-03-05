#include "lexer.h"
#include <cstdint>
#include <unordered_set>
strings Lexer::lex(std::string s) {
	strings strlst;
	char lexeme[256];
	int i = 0;
	int j = 0;
	State state = START;
	int done = 0; 
	int len = s.length();
	int balance = 0; 

	while(i < len) {
		switch(state) {
		case START:
			if (my_isSpace(s[i])) {
				state = SKIP;
			} else if (isGroup(s[i])) {
				if(s[i] == '"') {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				state = READBLOCK;
			} else if (s[i] == '/' && s[i + 1] == '/') {
				i += 2;
				state = COMMENT;
			} else {
				state = READCHAR;
			}
			break;
		case READCHAR:
			if (my_isSpace(s[i])) {
				state = DUMP;
			} else if (s[i] == '\\') {
				i += 2;
			} else if (isGroup(s[i])) {
				if (s[i] == '"') {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				state = READBLOCK;
			} else if (isSpecial(s[i])) {
				if (j == 0) {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				state = DUMP;
			} else if (s[i] == '/' && s[i + 1] == '/') {
				i += 2;
				state = COMMENT;
			} else {
				lexeme[j] = s[i];
				j++;
				i++;
			}
			break;
		case READBLOCK:
			if (s[i] == beg_char && s[i] != '"') {
				balance++;
				lexeme[j] = s[i];
				j++;
				i++;
			} else if (s[i] == end_char) {
				balance--;
				lexeme[j] = s[i];
				j++;
				i++;
				if (balance <= 0) {
					state = DUMP;
				}
			} else if (end_char == '"' && s[i] == '\\') {
				// TODO: fix this to actually record the chars
				i += 2;
			} else {
				lexeme[j] = s[i];
				j++;
				i++;
			}
			break;
		case SKIP:
			if (my_isSpace(s[i])) {
				i++;
			} else {
				state = READCHAR;
			}
			break;
		case DUMP:
			if (j > 0) {
				lexeme[j] = 0;
				strlst.push_back(lexeme);
				j = 0;
			}
			state = START;
			break;
		case COMMENT:
			if (s[i] != '\n') {
				i++;
			} else {
				state = READCHAR;
			}
			break;
		case END:
			i = len;
			break;
		}
	}
	if (j > 0) {
		lexeme[j] = 0;
		strlst.push_back(lexeme);
	}
	return strlst;
}

// this function allows us to define what a space is
bool Lexer::my_isSpace(char c) {
	switch(c) {
		case '\n':
		case '\r':
		case '\t':
		case '\v':
		case ' ':
		case '\f':
			return true;
		default:
			return false;
	}
}
bool Lexer::isGroup(char c) {
	beg_char = c;
	switch(c) {
	case '"':
		end_char = '"';
		return true;
	case '(':
		end_char = ')';
		return true;
	case '{':
	       	end_char = '}';
		  return true;
	case ')':
		  return true;
	case '}':
		return true;
	default:
		return false;
	}
}
bool Lexer::isSpecial(char c) {
	switch(c) {
		case '[':
		case ']':
			return true;
		default:
			return false;
	}
}
bool isKeyword(const std::string& str) {
    static const std::unordered_set<std::string> keywords = {
        "if", "else", "while", "return", 
        "open", "read", "write", "close" // Checks for keywords
    };
    return keywords.find(str) != keywords.end();
}
