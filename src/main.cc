#include <string>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include "actions/frontendaction.h"
#include "utils/utils.h"

namespace {

namespace ct = clang::tooling;

llvm::cl::OptionCategory category("boost-optional-migration options");

const char* progname;

int revisedMain(ct::CommonOptionsParser& opts) {
    return ct::ClangTool(opts.getCompilations(), opts.getSourcePathList())
        .run(&*ct::newFrontendActionFactory<clang::SyntaxOnlyAction>());
}

int originalMain(ct::CommonOptionsParser& opts) {
    for (auto &src : opts.getSourcePathList()) {
        if (!utils::fileExists(src)) {
            llvm::errs() << "File: " << src << " does not exist!\n";
            return -1;
        }

        auto absPath = ct::getAbsolutePath(src);
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
