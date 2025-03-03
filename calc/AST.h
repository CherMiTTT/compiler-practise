#ifndef LLVM_TEST_AST_H
#define LLVM_TEST_AST_H

#include <utility>

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;
class Expr;
class Factor;
class WithDecl;
class BinaryOp;

class ASTVisitor {
public:
    virtual void visit(AST&){};
    virtual void visit(Expr&){};
    virtual void visit(Factor&) = 0;
    virtual void visit(BinaryOp&) = 0;
    virtual void visit(WithDecl&) = 0;
};

class AST {
public:
    virtual ~AST() = default;
    virtual void accept(ASTVisitor& V) = 0;
};

class Expr : public AST{
public:
    Expr() = default;
};

class Factor : public Expr {
public:
    enum ValueKind {Ident, Number};

private:
    ValueKind Kind;
    llvm::StringRef Val;

public:
    Factor(ValueKind Kind, llvm::StringRef Val) : Kind(Kind), Val(Val) {}
    [[nodiscard]] ValueKind getKind() const {return Kind;}
    [[nodiscard]] llvm::StringRef getVal() {return Val;}
    void accept(ASTVisitor& V) override {
        V.visit(*this);
    }
};

class BinaryOp : public Expr {
public:
    enum Operator {Plus, Minus, Mul, Div};
private:
    Expr* Left;
    Expr* Right;
    Operator Op;

public:
    BinaryOp(Operator Op, Expr* L, Expr* R) : Op(Op), Left(L), Right(R) {}
    Expr *getLeft() {return Left;}
    Expr *getRight() {return Right;}
    Operator getOperator() {return Op;}
    void accept(ASTVisitor& V) override  {V.visit(*this);}
};

class WithDecl : public AST {
    using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
    VarVector Vars;
    Expr* E;

public:
    WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars, Expr* E) :
        Vars(std::move(Vars)), E(E) {}
    VarVector::const_iterator begin() {return Vars.begin();}
    VarVector::const_iterator end() {return Vars.end();}
    Expr* getExpr() {return E;}
    void accept(ASTVisitor& V) override {V.visit(*this);}
};
#endif //LLVM_TEST_AST_H