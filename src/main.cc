#include <string>

#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include "actions/frontendaction.h"
#include "utils/utils.h"

int main(int argc, const char **argv)
{
    llvm::cl::OptionCategory ctCategory("clang-tool options");
    auto opts = clang::tooling::CommonOptionsParser::create(argc, argv, ctCategory);
    if (!opts) {
        llvm::errs() << "cmdline option parse failed:" << opts.takeError();
        return -1;
    }

    for (auto &src : opts->getSourcePathList()) {
        if (!utils::fileExists(src)) {
            llvm::errs() << "File: " << src << " does not exist!\n";
            return -1;
        }

        auto absPath = clang::tooling::getAbsolutePath(src);
        llvm::outs() << "src='" << src << "', absPath='" << absPath << "'\n";

        auto compileArgs = utils::getCompileArgs(opts->getCompilations().getCompileCommands(absPath));
        compileArgs.push_back("-I" + utils::getClangBuiltInIncludePath(argv[0]));

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