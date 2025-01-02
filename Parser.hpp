
#pragma once

///
///
///     `Parser.cpp`
///
///     The core of this library is situates in one single macro called
///     `LEXER_IMPL`
///
///     Following is a Simple implementation for lexing a simple
///     json file with comments for demonstration
///
///     ```c
// #include "./Parser.hpp"
// #include <cstdint>
// #include <cstdlib>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
//
// /// # are consider comments in this json parser for example purpose
// class JsonLexer {
//     enum TokenType {
//         Ident = 0,
//         RightBrace,
//         LeftBrace,
//         Comma,
//         Collan,
//         Number,
//         Qutation
//     };
//
//     LEXER_IMPL(TokenType)
//     Lexer lexer;
//
//     JsonLexer(std::string input) : lexer(Lexer(input)) {};
//
//     // Must delete the tokens after use
//     Lexer::Token *next_token() {
//         Lexer::Token *tok = nullptr;
//         this->lexer.skip_whitespace();
//         if (this->lexer.is_eof())
//             return nullptr;
//
//         switch (lexer.curr_char) {
//
//         case '"':
//             tok = new Lexer::Token();
//             tok->type = TokenType::Qutation;
//             tok->literal = "\"";
//             break;
//         case '{':
//             tok = new Lexer::Token();
//             tok->type = TokenType::LeftBrace;
//             tok->literal = "{";
//             break;
//         case '}':
//             tok = new Lexer::Token();
//             tok->type = TokenType::RightBrace;
//             tok->literal = "}";
//             break;
//         case ',':
//             tok = new Lexer::Token();
//             tok->type = TokenType::Comma;
//             tok->literal = ",";
//             break;
//         case ':':
//             tok = new Lexer::Token();
//             tok->type = TokenType::Collan;
//             tok->literal = ":";
//             break;
//         case '#':
//             this->lexer.skip_line();
//             return this->next_token();
//             break;
//         default:
//             if (this->lexer.is_letter()) {
//                 std::string ident = this->lexer.read_identifier();
//                 tok = new Lexer::Token();
//                 tok->type = TokenType::Ident;
//                 tok->literal = ident.data();
//             } else if (this->lexer.is_number()) {
//                 std::string ident = this->lexer.read_number();
//                 tok = new Lexer::Token();
//                 tok->type = TokenType::Number;
//                 tok->literal = ident.data();
//             } else {
//             }
//         };
//         lexer.read_next();
//         return tok;
//     }
// };
//
// int main() {
//     std::string test(R"({
//                             "Hwllo" : "World", # I am a comment
//                             "Foo" : 69
//                         })");
//     JsonLexer json_lexer = JsonLexer(test);
//
//     for (JsonLexer::Lexer::Token *token = json_lexer.next_token(); token;
//          token = json_lexer.next_token()) {
//         std::cout << "-----------------------------" << std::endl;
//         std::cout << "Literal: " << token->literal << std::endl;
//         std::cout << "Type: " << token->type << std::endl;
//         std::cout << "-----------------------------" << std::endl;
//     }
// }
///     ```
///
///
///

#define LEXER_IMPL(TokenTypeName)                                              \
    struct Lexer {                                                             \
        struct Token {                                                         \
            TokenTypeName type;                                                \
            std ::string literal;                                              \
        };                                                                     \
                                                                               \
    public:                                                                    \
        char curr_char;                                                        \
        uint64_t read_position;                                                \
        uint64_t position;                                                     \
        std ::vector<char> input;                                              \
        Lexer(std ::string input) {                                            \
            this->input = std ::vector<char>(input.begin(), input.end());      \
            this->curr_char = input[0];                                        \
            this->read_position = 0;                                           \
            this->position = 0;                                                \
        }                                                                      \
        Lexer() = default;                                                     \
        void set_input(std ::string input) {                                   \
            this->input = std ::vector<char>(input.begin(), input.end());      \
        }                                                                      \
        void read_next() {                                                     \
            if (this->read_position >= input.size()) {                         \
                this->curr_char = '\0';                                        \
            } else {                                                           \
                this->curr_char = this->input[this->read_position];            \
            }                                                                  \
            this->position = this->read_position++;                            \
        }                                                                      \
        bool is_letter() {                                                     \
            return (this->curr_char >= 'A' && this->curr_char <= 'Z') ||       \
                   (this->curr_char >= 'a' && this->curr_char <= 'z');         \
        }                                                                      \
        bool is_number() {                                                     \
            return this->curr_char >= '0' && this->curr_char <= '9';           \
        }                                                                      \
        char curr() { return this->curr_char; }                                \
        std ::string read_number() {                                           \
            std ::string res;                                                  \
            while (this->is_number()) {                                        \
                res.push_back(this->curr_char);                                \
                this->read_next();                                             \
            }                                                                  \
            return res;                                                        \
        }                                                                      \
        std ::string read_identifier() {                                       \
            std::string res;                                                   \
            while (this->is_letter()) {                                        \
                res.push_back(this->input[this->position]);                    \
                this->read_next();                                             \
            }                                                                  \
            this->read_back();                                                 \
            return res;                                                        \
        }                                                                      \
        void read_back() {                                                     \
            uint64_t new_pos = this->read_position - 2;                        \
            this->read_position = (0 < new_pos) ? new_pos : 0;                 \
            this->read_next();                                                 \
        }                                                                      \
        bool is_eof() { return this->curr_char == 0; }                         \
        void skip_line() {                                                     \
            while (this->curr_char != '\n')                                    \
                this->read_next();                                             \
        }                                                                      \
        void skip_whitespace() {                                               \
            while (std ::isspace(this->curr_char)) {                           \
                this->read_next();                                             \
            }                                                                  \
        }                                                                      \
    };
