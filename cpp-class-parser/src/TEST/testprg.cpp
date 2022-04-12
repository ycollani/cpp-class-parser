/*
 * getmsg.cpp
 *
 *  Created on: 29.11.2018
 *      Author: ycollani
 */

#include <assert.h>
#include <iostream>
#include <map>

#include "SourceGenerator.h"
#include "cpp-class-parser/ASTConsumer.h"
#include "cpp-class-parser/ClassInformation.h"
#include "cpp-class-parser/FrontendAction.h"
#include "MessageClassMapping.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcomment"           // reason: including third party code
#pragma GCC diagnostic ignored "-Wunused-parameter"  // reason: including third party code
#pragma GCC diagnostic ignored "-Wstrict-aliasing"   // reason: including third party code

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#pragma GCC diagnostic pop

extern std::map<std::string, VC::MDSD::ClassInformation> classMap;
extern VC::MDSD::TypedefInformation typedefInformation;

// ========= Options =======

llvm::cl::opt<std::string> OutputFilename("o", llvm::cl::desc("Specify output filename"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string> messageBaseClass("m", llvm::cl::desc("Specify message base class"), llvm::cl::value_desc("message base class"));
llvm::cl::opt<bool>        verbose("v", llvm::cl::desc("Verbose"), llvm::cl::value_desc("true or false"));
llvm::cl::opt<std::string> messageClassMapping("x", llvm::cl::desc("Specify message class mapping"), llvm::cl::value_desc("message class mapping"));

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

// ========================================
// ==
// ========================================

int main(int argc, const char **argv)
{
    //clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);

    auto OptionsParser = clang::tooling::CommonOptionsParser::create (argc, argv, MyToolCategory, llvm::cl::OneOrMore, nullptr);

    if (verbose)
    {
        std::cout << "gen message: (C) 2018-20 Yorck von Collani" << std::endl;
    }


    if (messageBaseClass.empty())
    {
        std::cerr << "message base class isn't defined." << std::endl;
        return 1;
    }
    if (OutputFilename.empty())
    {
        std::cerr << "message class name isn't defined" << std::endl;
        return 1;
    }

    if (verbose)
    {
        std::cout << "Output file name: " << OutputFilename.getValue() << std::endl;
        std::cout << "Source class    : " << messageBaseClass.getValue() << std::endl;
    }

    clang::tooling::ClangTool Tool(OptionsParser->getCompilations(), OptionsParser->getSourcePathList());

    if (verbose)
    {
        std::cout << "Current Dir: " << getenv ("PWD") << std::endl;
        std::cout << "Analyzing" << std::endl;
    }

    std::shared_ptr<clang::tooling::FrontendActionFactory> frontEndActionFactory =
        clang::tooling::newFrontendActionFactory<VC::MDSD::FrontendAction>();
    int rc = Tool.run(frontEndActionFactory.get());
    if (rc == 1)
    {
        return 1;
    }

    assert(frontEndActionFactory.get() != nullptr);

    std::unique_ptr<clang::FrontendAction> frontEndActionPtr = frontEndActionFactory->create();
    assert(frontEndActionPtr != nullptr);

    return 0;
}
