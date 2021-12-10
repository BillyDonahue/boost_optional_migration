#pragma once

#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Rewrite/Core/Rewriter.h>

class XConsumer : public clang::ASTConsumer {
    private:
        clang::Rewriter rewriter;

    public:
        explicit XConsumer(clang::ASTContext &context);
        void HandleTranslationUnit(clang::ASTContext &context) override;
};