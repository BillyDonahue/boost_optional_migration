#include <string>

#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

//#include "actions/frontendaction.h"
#include "utils/utils.h"

namespace {

namespace ct = clang::tooling;

llvm::cl::OptionCategory category("boost-optional-migration options");

const char* progname;

class MyConsumer : public clang::ASTConsumer {
public:
    MyConsumer(clang::CompilerInstance& ci, llvm::StringRef inFile) {
        llvm::outs() << "MyConsumer(ci=???, inFile=" << inFile << ")\n";
    }

    void HandleTranslationUnit(clang::ASTContext &context) override {
        llvm::outs() << "HandleTranslationUnit\n";
    }
};

class MyAction : public clang::ASTFrontendAction {
public:
    using clang::ASTFrontendAction::ASTFrontendAction;
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& ci, clang::StringRef inFile) override {
        return std::make_unique<MyConsumer>(ci, inFile);
    }
};

int revisedMain(ct::CommonOptionsParser& opts) {
    auto action = ct::newFrontendActionFactory<MyAction>();
    return ct::ClangTool(opts.getCompilations(), opts.getSourcePathList())
        .run(&*action);
}

}  // namespace

int main(int argc, const char **argv) {
    progname = argv[0];
    auto opts = ct::CommonOptionsParser::create(argc, argv, category);
    if (!opts) {
        llvm::errs() << "cmdline option parse failed:" << opts.takeError();
        return -1;
    }
    return revisedMain(*opts);
}
