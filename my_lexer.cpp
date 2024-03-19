#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#include<cctype>
#include<fstream>

using namespace std;

enum TokenType{
  KEYWORD_BASIC_MAIN,
  KEYWORD_BASIC_RETURN,
  KEYWORD_CONDITIONAL_IF,
  KEYWORD_CONDITIONAL_THEN,
  KEYWORD_CONDITIONAL_ELSE,
  KEYWORD_CONDITIONAL_SWITCH,
  KEYWORD_CONDITIONAL_OF,
  KEYWORD_CONDITIONAL_CASE,
  KEYWORD_CONDITIONAL_DEFAULT,
  KEYWORD_LOOP_WHILE,
  KEYWORD_LOOP_DO,
  KEYWORD_LOOP_REPEAT,
  KEYWORD_LOOP_UNTIL,
  KEYWORD_LOOP_FOR,
  KEYWORD_LOOP_FROM,
  KEYWORD_LOOP_TO,
  KEYWORD_LOOP_STEP,
  KEYWORD_TYPE_INTEGER,
  KEYWORD_TYPE_REAL,
  KEYWORD_TYPE_CHAR,
  KEYWORD_TYPE_BOOL,
  KEYWORD_LOGIC_AND,
  KEYWORD_LOGIC_OR,
  KEYWORD_LOGIC_NOT,
  KEYWORD_LOGIC_MOD,
  KEYWORD_IO_READ,
  KEYWORD_IO_WRITE,
  SYMBOL_OPERATOR_EQ,
  SYMBOL_OPERATOR_ADD,
  SYMBOL_OPERATOR_SUB,
  SYMBOL_OPERATOR_MUL,
  SYMBOL_OPERATOR_DIV,
  SYMBOL_OPERATOR_LT,
  SYMBOL_OPERATOR_LE,
  SYMBOL_OPERATOR_GT,
  SYMBOL_OPERATOR_GE,
  SYMBOL_OPERATOR_NE,
  SYMBOL_DELIMITER_COMMA,
  SYMBOL_DELIMITER_SEMICOLON,
  SYMBOL_DELIMITER_COLON,
  SYMBOL_DELIMITER_LPAREN,
  SYMBOL_DELIMITER_RPAREN,
  SYMBOL_DELIMITER_LBRACE,
  SYMBOL_DELIMITER_RBRACE,
  SYMBOL_DELIMITER_LBRACKET,
  SYMBOL_DELIMITER_RBRACKET,
  IDENTIFIER,
  NUMBER,
  UNKNOWN
};

const map<string, TokenType> keywords = {
  {"main", KEYWORD_BASIC_MAIN},
  {"return", KEYWORD_BASIC_RETURN},
  {"if", KEYWORD_CONDITIONAL_IF},
  {"then", KEYWORD_CONDITIONAL_THEN},
  {"else", KEYWORD_CONDITIONAL_ELSE},
  {"switch", KEYWORD_CONDITIONAL_SWITCH},
  {"of", KEYWORD_CONDITIONAL_OF},
  {"case", KEYWORD_CONDITIONAL_CASE},
  {"default", KEYWORD_CONDITIONAL_DEFAULT},
  {"while", KEYWORD_LOOP_WHILE},
  {"do", KEYWORD_LOOP_DO},
  {"repeat", KEYWORD_LOOP_REPEAT},
  {"until", KEYWORD_LOOP_UNTIL},
  {"for", KEYWORD_LOOP_FOR},
  {"from", KEYWORD_LOOP_FROM},
  {"to", KEYWORD_LOOP_TO},
  {"step", KEYWORD_LOOP_STEP},
  {"integer", KEYWORD_TYPE_INTEGER},
  {"real", KEYWORD_TYPE_REAL},
  {"char", KEYWORD_TYPE_CHAR},
  {"bool", KEYWORD_TYPE_BOOL},
  {"and", KEYWORD_LOGIC_AND},
  {"or", KEYWORD_LOGIC_OR},
  {"not", KEYWORD_LOGIC_NOT},
  {"mod", KEYWORD_LOGIC_MOD},
  {"read", KEYWORD_IO_READ},
  {"write", KEYWORD_IO_WRITE}
};

const map<string, TokenType> symbols = {
  {"=", SYMBOL_OPERATOR_EQ},
  {"+", SYMBOL_OPERATOR_ADD},
  {"-", SYMBOL_OPERATOR_SUB},
  {"*", SYMBOL_OPERATOR_MUL},
  {"/", SYMBOL_OPERATOR_DIV},
  {"<", SYMBOL_OPERATOR_LT},
  {"<=", SYMBOL_OPERATOR_LE},
  {">", SYMBOL_OPERATOR_GT},
  {">=", SYMBOL_OPERATOR_GE},
  {"<>", SYMBOL_OPERATOR_NE},
  {",", SYMBOL_DELIMITER_COMMA},
  {";", SYMBOL_DELIMITER_SEMICOLON},
  {":", SYMBOL_DELIMITER_COLON},
  {"(", SYMBOL_DELIMITER_LPAREN},
  {")", SYMBOL_DELIMITER_RPAREN},
  {"{", SYMBOL_DELIMITER_LBRACE},
  {"}", SYMBOL_DELIMITER_RBRACE},
  {"[", SYMBOL_DELIMITER_LBRACKET},
  {"]", SYMBOL_DELIMITER_RBRACKET}
};

struct Token {
  TokenType type;
  string value;
};

string TokenTypeToString(TokenType type){
  switch(type){
    case KEYWORD_BASIC_MAIN:
      return "KEYWORD_BASIC_MAIN";
    case KEYWORD_BASIC_RETURN:
      return "KEYWORD_BASIC_RETURN";
    case KEYWORD_CONDITIONAL_IF:
      return "KEYWORD_CONDITIONAL_IF";
    case KEYWORD_CONDITIONAL_THEN:
      return "KEYWORD_CONDITIONAL_THEN";
    case KEYWORD_CONDITIONAL_ELSE:
      return "KEYWORD_CONDITIONAL_ELSE";
    case KEYWORD_CONDITIONAL_SWITCH:
      return "KEYWORD_CONDITIONAL_SWITCH";
    case KEYWORD_CONDITIONAL_OF:
      return "KEYWORD_CONDITIONAL_OF";
    case KEYWORD_CONDITIONAL_CASE:
      return "KEYWORD_CONDITIONAL_CASE";
    case KEYWORD_CONDITIONAL_DEFAULT:
      return "KEYWORD_CONDITIONAL_DEFAULT";
    case KEYWORD_LOOP_WHILE:
      return "KEYWORD_LOOP_WHILE";
    case KEYWORD_LOOP_DO:
      return "KEYWORD_LOOP_DO";
    case KEYWORD_LOOP_REPEAT:
      return "KEYWORD_LOOP_REPEAT";
    case KEYWORD_LOOP_UNTIL:
      return "KEYWORD_LOOP_UNTIL";
    case KEYWORD_LOOP_FOR:
      return "KEYWORD_LOOP_FOR";
    case KEYWORD_LOOP_FROM:
      return "KEYWORD_LOOP_FROM";
    case KEYWORD_LOOP_TO:
      return "KEYWORD_LOOP_TO";
    case KEYWORD_LOOP_STEP:
      return "KEYWORD_LOOP_STEP";
    case KEYWORD_TYPE_INTEGER:
      return "KEYWORD_TYPE_INTEGER";
    case KEYWORD_TYPE_REAL:
      return "KEYWORD_TYPE_REAL";
    case KEYWORD_TYPE_CHAR:
      return "KEYWORD_TYPE_CHAR";
    case KEYWORD_TYPE_BOOL:
      return "KEYWORD_TYPE_BOOL";
    case KEYWORD_LOGIC_AND:
      return "KEYWORD_LOGIC_AND";
    case KEYWORD_LOGIC_OR:
      return "KEYWORD_LOGIC_OR";
    case KEYWORD_LOGIC_NOT:
      return "KEYWORD_LOGIC_NOT";
    case KEYWORD_LOGIC_MOD:
      return "KEYWORD_LOGIC_MOD";
    case KEYWORD_IO_READ:
      return "KEYWORD_IO_READ";
    case KEYWORD_IO_WRITE:
      return "KEYWORD_IO_WRITE";
    case SYMBOL_OPERATOR_EQ:
      return "SYMBOL_OPERATOR_EQ";
    case SYMBOL_OPERATOR_ADD:
      return "SYMBOL_OPERATOR_ADD";
    case SYMBOL_OPERATOR_SUB:
      return "SYMBOL_OPERATOR_SUB";
    case SYMBOL_OPERATOR_MUL:
      return "SYMBOL_OPERATOR_MUL";
    case SYMBOL_OPERATOR_DIV:
      return "SYMBOL_OPERATOR_DIV";
    case SYMBOL_OPERATOR_LT:
      return "SYMBOL_OPERATOR_LT";
    case SYMBOL_OPERATOR_LE:
      return "SYMBOL_OPERATOR_LE";
    case SYMBOL_OPERATOR_GT:
      return "SYMBOL_OPERATOR_GT";
    case SYMBOL_OPERATOR_GE:
      return "SYMBOL_OPERATOR_GE";
    case SYMBOL_OPERATOR_NE:
      return "SYMBOL_OPERATOR_NE";
    case SYMBOL_DELIMITER_COMMA:
      return "SYMBOL_DELIMITER_COMMA";
    case SYMBOL_DELIMITER_SEMICOLON:
      return "SYMBOL_DELIMITER_SEMICOLON";
    case SYMBOL_DELIMITER_COLON:
      return "SYMBOL_DELIMITER_COLON";
    case SYMBOL_DELIMITER_LPAREN:
      return "SYMBOL_DELIMITER_LPAREN";
    case SYMBOL_DELIMITER_RPAREN:
      return "SYMBOL_DELIMITER_RPAREN";
    case SYMBOL_DELIMITER_LBRACE:
      return "SYMBOL_DELIMITER_LBRACE";
    case SYMBOL_DELIMITER_RBRACE:
      return "SYMBOL_DELIMITER_RBRACE";
    case SYMBOL_DELIMITER_LBRACKET:
      return "SYMBOL_DELIMITER_LBRACKET";
    case SYMBOL_DELIMITER_RBRACKET:
      return "SYMBOL_DELIMITER_RBRACKET";
    case IDENTIFIER:
      return "IDENTIFIER";
    case UNKNOWN:
      return "UNKNOWN";
    case NUMBER:
      return "NUMBER";
    default:
      return "UNKNOWN";
  }
}

class Lexer {
private:
  ifstream file; // input file
  char peek = ' '; // next character to be read

  bool isAlpha(char c){
    return isalpha(static_cast<unsigned char>(c));
  }

  bool isDigit(char c){
    return isdigit(static_cast<unsigned char>(c));
  }

  void readChar(){
    if(!file.eof()){
      file.get(peek);
    } else {
      peek = EOF;
    }
  }

public:
  Lexer(const string& filename){
    file.open(filename);
    if(!file.is_open()){
      throw runtime_error("[ERROR] File not found");
    }
  }

  ~Lexer(){
    file.close();
  }

  vector<Token> tokenize(){
    vector<Token> tokens;
    while(true){
      // jump over white spaces
      while(isspace(peek)){
        readChar();
      }

      // end of file
      if(peek == EOF){
        break;
      }

      // condition for alphabets
      if(isalpha(peek)){
        string buffer;
        while(true){
          buffer += peek;
          readChar();
          if(!(isAlpha(peek) || isDigit(peek))){
            break; // break when the next character is not an alphabet or digit
          }
        }

        // check if the buffer is a keyword
        if(keywords.find(buffer) != keywords.end()){
          tokens.push_back({keywords.at(buffer), buffer});
        } else {
          tokens.push_back({IDENTIFIER, buffer});
        }
        continue;
      }

      // condition for digits
      if(isDigit(peek)){
        string num;
        while(true){
          num += peek;
          readChar();
          if(!isDigit(peek)){
            break; // break when the next character is not a digit
          }
        }
        tokens.push_back({NUMBER, num});
        continue;
      }

      // condition for string literals
      if(peek == '"'){
        string str;
        readChar();
        while(peek != '"'){
          str += peek;
          readChar();
        }
        readChar();
        tokens.push_back({IDENTIFIER, str});
        continue;
      }

      // condition for symbols
      if(symbols.find(string(1, peek)) != symbols.end()){
        char symbol = peek;
        readChar();
        tokens.push_back({symbols.at(string(1, symbol)), string(1, symbol)});
        continue;
      }

      // condition for unknown characters
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
  for(const Token &token : tokens){
    cout << "{" << token.type << ", \"" << token.value << "\", " << TokenTypeToString(token.type) << "}" << endl;
  }
  cout << endl;
  return 0;
}