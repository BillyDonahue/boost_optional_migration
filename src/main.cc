#include <string>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include "actions/frontendaction.h"
#include "utils/utils.h"

static llvm::cl::OptionCategory category("boost-optional-migration options");

static const char* progname;

static int revisedMain(clang::tooling::CommonOptionsParser& opts) {
    clang::tooling::ClangTool tool(opts.getCompilations(), opts.getSourcePathList());
    return tool.run(clang::tooling::newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}

static int originalMain(clang::tooling::CommonOptionsParser& opts) {
    for (auto &src : opts.getSourcePathList()) {
        if (!utils::fileExists(src)) {
            llvm::errs() << "File: " << src << " does not exist!\n";
            return -1;
        }

        auto absPath = clang::tooling::getAbsolutePath(src);
        llvm::outs() << "src='" << src << "', absPath='" << absPath << "'\n";

        auto compileArgs = utils::getCompileArgs(opts.getCompilations().getCompileCommands(absPath));
        compileArgs.push_back("-I" + utils::getClangBuiltInIncludePath(progname));

        {
            llvm::outs() << "compileArgs: [\n";
            for (auto &s : compileArgs)
                llvm::outs() << "  '" << s << "',\n";
            llvm::outs() << "]\n";
        }

        utils::customRunToolOnCodeWithArgs(
            std::make_unique<XFrontendAction>(),
            utils::getSourceCode(src),
            compileArgs,
            src);
    }
    return 0;

}

int main(int argc, const char **argv) {
    auto opts = clang::tooling::CommonOptionsParser::create(argc, argv, category);
    if (!opts) {
        llvm::errs() << "cmdline option parse failed:" << opts.takeError();
        return -1;
    }
    progname = argv[0];
    return revisedMain(*opts);
}
