#include "integervariablefinder.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>

IntegerVariableFinder::IntegerVariableFinder(clang::ASTContext &context)
    : Finder(context)
{}

void IntegerVariableFinder::start() {
    using namespace clang::ast_matchers;
    MatchFinder integerFinder;
    integerFinder.addMatcher(varDecl(hasType(isInteger())).bind("intVar"), this);
    integerFinder.matchAST(context);
}

void IntegerVariableFinder::run(const clang::ast_matchers::MatchFinder::MatchResult &result) {
    auto varDecl = result.Nodes.getNodeAs<clang::VarDecl>("intVar");
    if (!varDecl)
        return;
    if (result.SourceManager->isInSystemHeader(varDecl->getSourceRange().getBegin()))
        return;
    auto name = varDecl->getNameAsString();
    if (name.empty())
        return;
    llvm::outs() << "integer variable: " << name << "\n";
}
