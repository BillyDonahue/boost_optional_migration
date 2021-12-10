#include "consumer.h"

#include "../finder/integervariablefinder.h"
#include "../transformer/functioncalltransformer.h"

XConsumer::XConsumer(clang::ASTContext &context) {}

void XConsumer::HandleTranslationUnit(clang::ASTContext &context) {
    rewriter.setSourceMgr(context.getSourceManager(), context.getLangOpts());
    
    FunctionCallTransformer txn(context, rewriter);
    
    txn.start();
    txn.print(llvm::outs());
    
    IntegerVariableFinder(context).start();

    auto buffer = rewriter.getRewriteBufferFor(context.getSourceManager().getMainFileID());
    if (buffer)
        buffer->write(llvm::outs());
}