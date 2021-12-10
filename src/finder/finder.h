#pragma once

#include <clang/ASTMatchers/ASTMatchFinder.h>

class Finder : public clang::ast_matchers::MatchFinder::MatchCallback {
    protected:
        clang::ASTContext &context;

    public:
        explicit Finder(clang::ASTContext &context);
        virtual void start() = 0;
};