#pragma once

#include <clang/AST/ASTContext.h>

#include "finder.h"

class IntegerVariableFinder : public Finder {
    public:
        explicit IntegerVariableFinder(clang::ASTContext &context);
        void start() override;
        void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
};