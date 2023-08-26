/*
 * Copyright (c) 2018-2023 Yorck von Collani <foss@von-collani.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "CompilerDatabase.h"

#include <boost/filesystem.hpp>
#include <iostream>

#include "clang/Tooling/CompilationDatabasePluginRegistry.h"

namespace clang {
namespace tooling {

namespace {

    class StaticCompilationDatabasePlugin : public CompilationDatabasePlugin
    {
        std::unique_ptr<CompilationDatabase> loadFromDirectory(StringRef Directory, std::string &ErrorMessage) override
        {
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
            return std::unique_ptr<CompilationDatabase> (new StaticCompilationDatabase);
        }
    };

}


// Register the JSONCompilationDatabasePlugin with the
// CompilationDatabasePluginRegistry using this statically initialized variable.
static CompilationDatabasePluginRegistry::Add<StaticCompilationDatabasePlugin> X("static-compilation-database",
                                                                               "Provides a static defined compilation databases");

// This anchor is used to force the linker to link in the generated object file
// and thus register the JSONCompilationDatabasePlugin.

volatile int JSONAnchorSource = 0;

// ========================================
// == StaticCompilationDatabase::getCompileCommands
// ========================================

std::vector<CompileCommand> StaticCompilationDatabase::getCompileCommands(StringRef FilePath) const
{
    //std::cout << __FUNCTION__ <<  std::endl;

    std::string directory = boost::filesystem::path(FilePath.str()).parent_path().generic_string();
    std::string fileName  = FilePath.str();

    std::vector< std::string > CommandLine;
    CommandLine.push_back("/usr/bin/g++");
    CommandLine.push_back("-I/usr/include/c++/7");
    CommandLine.push_back("-I/usr/include/c++/9");
    CommandLine.push_back("-I/usr/include/c++/11");
    CommandLine.push_back("-I/usr/include/x86_64-linux-gnu/c++/7/");
    CommandLine.push_back("-I/usr/include/x86_64-linux-gnu/c++/9/");
    CommandLine.push_back("-I/usr/include/x86_64-linux-gnu/c++/11/");
    CommandLine.push_back("-I/usr/lib/gcc/x86_64-linux-gnu/7/include/");
    CommandLine.push_back("-I/usr/lib/gcc/x86_64-linux-gnu/9/include/");
    CommandLine.push_back("-I/usr/lib/gcc/x86_64-linux-gnu/11/include/");
    const char* currentDir=getenv("PWD");
    CommandLine.push_back(std::string("-I") + std::string(currentDir));
    CommandLine.push_back(fileName);

    std::string outputFile ("a.out");

    //std::cout << "Dir : " << directory << std::endl;
    //std::cout << "File: " <<fileName << std::endl;

    std::vector<CompileCommand> Commands;
    Commands.push_back (CompileCommand (directory, fileName, CommandLine, outputFile));
    return Commands;
}

// ========================================
// == StaticCompilationDatabase::getAllFiles
// ========================================

std::vector<std::string> StaticCompilationDatabase::getAllFiles() const
{
    //std::cout << __FUNCTION__ <<  std::endl;
    std::vector<std::string> Result;
    return Result;
}

// ========================================
// == StaticCompilationDatabase::getAllCompileCommands
// ========================================

std::vector<CompileCommand> StaticCompilationDatabase::getAllCompileCommands() const
{
    //std::cout << __FUNCTION__ <<  std::endl;
    std::vector<CompileCommand> Commands;
    return Commands;
}

}  // namespace tooling
}  // namespace clang
