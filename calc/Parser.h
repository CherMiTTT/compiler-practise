#ifndef LLVM_TEST_PARSER_H
#define LLVM_TEST_PARSER_H

#include "Lexer.h"
#include "AST.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
    Lexer &Lex;
    Token Tok;
    bool HasError;

    void error() {
        llvm::errs() << "Unexpected: " << Tok.getText() << "\n";
        HasError = true;
    }

    void advance() {Lex.next(Tok);}

    [[nodiscard]] bool expect(Token::TokenKind Kind) {
        if(Tok.getKind() != Kind) {
            error();
            return true;
        }
        return false;
    }

    [[nodiscard]] bool consume(Token::TokenKind Kind) {
        if(expect(Kind))
            return true;
        advance();
        return false;
    }

    AST* parseCalc();
    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();

public:
    Parser(Lexer& Lex) : Lex(Lex), HasError(false) {
        advance();
    }

    [[nodiscard]] bool hasError() const {return HasError;}

    AST* parse();
};


#endif //LLVM_TEST_PARSER_H
