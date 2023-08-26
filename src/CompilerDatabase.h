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

#ifndef SRC_CPP_CLASS_PARSER_COMPILERDATABASE_H_
#define SRC_CPP_CLASS_PARSER_COMPILERDATABASE_H_

#include <iostream>
#include "clang/Tooling/CompilationDatabase.h"

namespace clang {
namespace tooling {

class StaticCompilationDatabase : public CompilationDatabase {
public:
    /// Returns all compile commands in which the specified file was
    /// compiled.
    ///
    /// FIXME: Currently FilePath must be an absolute path inside the
    /// source directory which does not have symlinks resolved.
    std::vector<CompileCommand> getCompileCommands(StringRef FilePath) const override;

    /// Returns the list of all files available in the compilation database.
    ///
    /// These are the 'file' entries of the JSON objects.
    std::vector<std::string> getAllFiles() const override;

    /// Returns all compile commands for all the files in the compilation
    /// database.
    std::vector<CompileCommand> getAllCompileCommands() const override;

    /// Constructs a static compilation database
    StaticCompilationDatabase()
    {
        //std::cout << "Create static compilation database" << std::endl;
    }
};

}  // namespace tooling
}  // namespace clang


#endif /* SRC_CPP_CLASS_PARSER_COMPILERDATABASE_H_ */
