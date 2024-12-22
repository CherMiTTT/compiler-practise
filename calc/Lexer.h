#ifndef LLVM_TEST_LEXER_H
#define LLVM_TEST_LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

class Lexer;

class Token {
    friend class Lexer;

    public:
        enum TokenKind : unsigned short {
            eoi, unknown, ident, number, comma, colon, plus, minus, star, slash,
            l_paren, r_paren, KW_with
        };

        [[nodiscard]] TokenKind getKind() const {return Kind;}
        [[nodiscard]] llvm::StringRef getText() const {return Text;}

        [[nodiscard]] bool is(TokenKind K) const {return Kind == K;}
        [[nodiscard]] bool isOneOf(TokenKind K1, TokenKind K2) const {
            return is(K1) || is(K2);
        }

        template <typename... Ts>
        [[nodiscard]] bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
            return is(K1) || isOneOf(K2, Ks...);
        }

    private:
        TokenKind Kind;
        llvm::StringRef Text;
};

class Lexer {
public:
    Lexer(const llvm::StringRef& Buffer) : BufferStart(Buffer.begin()),
                                           BufferPtr(BufferStart) {}

    void next(Token &token);
private:
    void formToken(Token &Tok, const char* TokEnd, Token::TokenKind Kind);

    const char* BufferStart;
    const char* BufferPtr;
};



#endif //LLVM_TEST_LEXER_H
