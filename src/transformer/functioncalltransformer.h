#ifndef FUNCTIONCALL_TRANSFORMER_HPP
#define FUNCTIONCALL_TRANSFORMER_HPP

#include "transformer.h"

#include <llvm/Support/raw_ostream.h>

#include <string>
#include <set>

namespace clang
{
    class ASTContext;
    class Rewriter;
}

class FunctionCallTransformer : public Transformer
{
    private:
        
        std::set<std::string> functions;
        
    public:

        explicit FunctionCallTransformer(clang::ASTContext &context, clang::Rewriter &rewriter);

        void start() override;
        void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
        void print(clang::raw_ostream &stream) override;
};


#endif
