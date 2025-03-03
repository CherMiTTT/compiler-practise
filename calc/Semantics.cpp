#include <llvm/Support/raw_ostream.h>
#include "llvm/ADT/StringSet.h"
#include "Semantics.h"

namespace {
    class DeclCheck : public ASTVisitor {
        llvm::StringSet<> Scope;
        bool HasError;

        enum ErrorType {Twice, Not};

        void error(ErrorType ET, llvm::StringRef V) {
            llvm::errs() << "Variable " << V << " " << (ET == Twice ? "already" : "not") <<
            "declared\n";
            HasError = true;
        }
    public:
        DeclCheck() : HasError(false) {};
        [[nodiscard]] bool hasError() {return HasError;}

        void visit(Factor& Node) override {
            if(Node.getKind() == Factor::Ident) {
                if(Scope.find(Node.getVal()) == Scope.end())
                    error(Not, Node.getVal());
            }
        }

        void visit(BinaryOp& Node) override {
            if(Node.getLeft())
                Node.getLeft()->accept(*this);
            else
                HasError = true;

            if(Node.getRight())
                Node.getRight()->accept(*this);
            else
                HasError = true;
        }

        void visit(WithDecl& Node) override {
            for(auto I : Node) {
                if(!Scope.insert(I).second) error(Twice, I);
            }

            if(Node.getExpr())
                Node.getExpr()->accept(*this);
            else
                HasError = true;
        }
    };
}

bool Semantics::semantic(AST *Tree) {
    if (!Tree)
        return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();
}