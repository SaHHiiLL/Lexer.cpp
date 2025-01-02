#include "./Parser.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/// # are consider comments in this json parser for example purpose
struct JsonLexer {
    enum TokenType {
        Ident = 0,
        RightBrace,
        LeftBrace,
        Comma,
        Collan,
        Number,
        Qutation
    };

    LEXER_IMPL(TokenType)
    Lexer lexer;

    JsonLexer(std::string input) : lexer(Lexer(input)) {};

    // Must free the tokens after use
    Lexer::Token *next_token() {
        Lexer::Token *tok = nullptr;
        this->lexer.skip_whitespace();
        if (this->lexer.is_eof())
            return nullptr;

        switch (lexer.curr_char) {

        case '"':
            tok = new Lexer::Token();
            tok->type = TokenType::Qutation;
            tok->literal = "\"";
            break;
        case '{':
            tok = new Lexer::Token();
            tok->type = TokenType::LeftBrace;
            tok->literal = "{";
            break;
        case '}':
            tok = new Lexer::Token();
            tok->type = TokenType::RightBrace;
            tok->literal = "}";
            break;
        case ',':
            tok = new Lexer::Token();
            tok->type = TokenType::Comma;
            tok->literal = ",";
            break;
        case ':':
            tok = new Lexer::Token();
            tok->type = TokenType::Collan;
            tok->literal = ":";
            break;
        case '#':
            this->lexer.skip_line();
            return this->next_token();
            break;
        default:
            if (this->lexer.is_letter()) {
                std::string ident = this->lexer.read_identifier();
                tok = new Lexer::Token();
                tok->type = TokenType::Ident;
                tok->literal = ident.data();
            } else if (this->lexer.is_number()) {
                std::string ident = this->lexer.read_number();
                tok = new Lexer::Token();
                tok->type = TokenType::Number;
                tok->literal = ident.data();
            } else {
            }
        };
        lexer.read_next();
        return tok;
    }
};

int main() {
    std::string test(R"({
                            "Hwllo" : "World", # I am a comment
                            "Foo" : 69
                        })");
    JsonLexer json_lexer = JsonLexer(test);

    for (JsonLexer::Lexer::Token *token = json_lexer.next_token(); token;
         token = json_lexer.next_token()) {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Literal: " << token->literal << std::endl;
        std::cout << "Type: " << token->type << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}
