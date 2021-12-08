#include "frontendaction.h"

#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

#include "../consumer/consumer.h"

std::unique_ptr<clang::ASTConsumer> XFrontendAction::CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef) {
    return std::make_unique<XConsumer>(compiler.getASTContext());
}

