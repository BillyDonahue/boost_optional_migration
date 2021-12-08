#ifndef FRONTEND_ACTION_HPP
#define FRONTEND_ACTION_HPP

#include <memory>
#include <vector>
#include <string>

#include <llvm/ADT/StringRef.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>

class XFrontendAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef inFile) override;
};

#endif // FRONTEND_ACTION_HPP