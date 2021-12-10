#pragma once

#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <llvm/Support/raw_ostream.h>

class Transformer : public clang::ast_matchers::MatchFinder::MatchCallback {
    protected:
        clang::ASTContext &context;
        clang::Rewriter &rewriter;

    public:
        explicit Transformer(clang::ASTContext &context, clang::Rewriter &rewriter);
        
        virtual void start() = 0;
        virtual void print(clang::raw_ostream &stream) = 0;
};