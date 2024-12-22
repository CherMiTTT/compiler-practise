#ifndef LLVM_TEST_LEXER_H
#define LLVM_TEST_LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

class Lexer {

};



class Token {
    friend class Lexer;
    enum TokenKind : unsigned short {
        eoi, unknown, ident, number, comma, colon, plus, minus, star, slash,
        l_paren, r_paren, KW_with
    };
};

#endif //LLVM_TEST_LEXER_H
