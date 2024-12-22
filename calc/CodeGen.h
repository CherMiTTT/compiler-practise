#ifndef LLVM_TEST_CODEGEN_H
#define LLVM_TEST_CODEGEN_H

#include "AST.h"

class CodeGen {
public:
    void compile(AST* Tree);
};

#endif //LLVM_TEST_CODEGEN_H
