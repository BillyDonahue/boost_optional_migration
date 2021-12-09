#include <string>

#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include "actions/frontendaction.h"
#include "utils/utils.h"

int main(int argc, const char **argv)
{
    llvm::cl::OptionCategory ctCategory("clang-tool options");
    auto opts = clang::tooling::CommonOptionsParser::create(argc, argv, ctCategory);

    for (auto &src : opts->getSourcePathList()) {
        if (!utils::fileExists(src)) {
            llvm::errs() << "File: " << src << " does not exist!\n";
            return -1;
        }

        auto compileArgs = utils::getCompileArgs(
            opts->getCompilations().getCompileCommands(clang::tooling::getAbsolutePath(src)));
        compileArgs.push_back("-I" + utils::getClangBuiltInIncludePath(argv[0]));

        for (auto &s : compileArgs)
            llvm::outs() << s << "\n";

        utils::customRunToolOnCodeWithArgs(
            std::make_unique<XFrontendAction>(),
            utils::getSourceCode(src),
            compileArgs,
            src);
    }

    return 0;
}