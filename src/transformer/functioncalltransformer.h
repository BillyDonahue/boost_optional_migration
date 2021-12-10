#pragma once

#include <string>
#include <set>

#include <clang/AST/ASTContext.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <llvm/Support/raw_ostream.h>

#include "transformer.h"

class FunctionCallTransformer : public Transformer {
    private:
        std::set<std::string> functions;
        
    public:
        explicit FunctionCallTransformer(clang::ASTContext &context, clang::Rewriter &rewriter);

        void start() override;
        void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
        void print(clang::raw_ostream &stream) override;
};