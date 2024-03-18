#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<cctype>
#include<chrono>
#include<ctime>
#include<algorithm>

using namespace std;

enum TokenType {
  KEYWORD,
  SYMBOL,
  IDENTIFIER,
  NUMBER,
  UNKNOWN,
};

struct Token {
  TokenType type;
  string value;
};

const vector<string> keywords = {
    "main",
    "if", "then", "else",
    "while", "do",
    "repeat", "until",
    "for", "from", "to", "step",
    "switch", "of", "case", "default",
    "return",
    "integer", "real", "char", "bool",
    "and", "or", "not", "mod",
    "read", "write"
};

const map<string, TokenType> symbols = {
  {"=", SYMBOL}, {"+", SYMBOL}, {"-", SYMBOL}, {"*", SYMBOL}, {"/", SYMBOL},
  {"<", SYMBOL}, {"<=", SYMBOL}, {">", SYMBOL}, {">=", SYMBOL},  {"!=", SYMBOL},
  {",", SYMBOL}, {";", SYMBOL}, {":",SYMBOL}, {"(", SYMBOL}, {")", SYMBOL},
  {"{", SYMBOL}, {"}", SYMBOL}, {"[", SYMBOL}, {"]", SYMBOL}
};

class Lexer {
private:
  ifstream file;
  char peek = ' ';

  bool isAlpha(char c) {
    return isalpha(static_cast<unsigned char>(c));
  }

  bool isDigit(char c) {
    return isdigit(static_cast<unsigned char>(c));
  }

  void readChar() {
    if(!file.eof()) {
      file.get(peek);
    } else {
      peek = EOF;
    }
  }

public:
  Lexer(const string& filename) {
    file.open(filename);
    if(!file.is_open()) {
      throw runtime_error("[ERROR] File not found");
    }
  }

  vector<Token> tokenize() {
    vector<Token> tokens;
    while(true) {
      while(isspace(peek)) {
        readChar();
      }

      if(peek == EOF) {
        break;
      }

      #include <algorithm>

      if (isalpha(peek)) {
        string buffer;
        while (true) {
          buffer += peek;
          readChar();
          if (!(isAlpha(peek) || isDigit(peek))) {
            break;
          }
        }

        if (find(keywords.begin(), keywords.end(), buffer) != keywords.end()) {
          tokens.push_back({KEYWORD, buffer});
        } else {
          tokens.push_back({IDENTIFIER, buffer});
        }
        continue;
      }

      if(isDigit(peek)) {
        string num;
        while(true) {
          num += peek;
          readChar();
          if(!isDigit(peek)) {
            break;
          }
        }

        tokens.push_back({NUMBER, num});
        continue;
      }

      if(symbols.find(string(1, peek)) != symbols.end()) {
        char symbol = peek;
        readChar();
        tokens.push_back({symbols.at(string(1, symbol)), string(1, symbol)});
        continue;
      }

      readChar();
      tokens.push_back({UNKNOWN, string(1, peek)});
    }
    return tokens;
  }
};

int main(int argc, char* argv[]){
  if(argc != 2){
    throw runtime_error("[ERROR] Invalid number of arguments. Usage: ./lexer <filename>");
  }

  string filename = argv[1];
  Lexer lexer(filename);
  vector<Token> tokens = lexer.tokenize();
  for(const auto &token : tokens){
    cout << "Token(Type=" << token.type << ", Value=\"" << token.value << "\")" << endl;
  }
  return 0;
}