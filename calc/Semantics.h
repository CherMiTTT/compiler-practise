#ifndef LLVM_TEST_SEMANTICS_H
#define LLVM_TEST_SEMANTICS_H

#include "AST.h"
#include "Lexer.h"

class Semantics {
public:
    [[nodiscard]] bool semantic(AST* Tree);
};
#endif //LLVM_TEST_SEMANTICS_H