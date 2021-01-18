/*
 * Copyright (c) 2018-2021 Yorck von Collani <foss@von-collani.de>
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


#include "rcl-genmsg/FrontendAction.h"
#include "rcl-genmsg/ASTConsumer.h"
#include "rcl-genmsg/ClassInformation.h"
#include <map>
#include <iostream>


std::map<std::string, VC::MDSD::ClassInformation> classMap;
VC::MDSD::TypedefInformation typedefInformation;

namespace VC {
namespace MDSD {

// ========================================
// ==
// ========================================

FrontendAction::~FrontendAction()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}


// ========================================
// ==
// ========================================

std::unique_ptr<clang::ASTConsumer> FrontendAction::CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef file)
{
    return std::unique_ptr<clang::ASTConsumer> (new VC::MDSD::ASTConsumer(&CI, &classMap, &typedefInformation)); // pass CI pointer to ASTConsumer
}


}  // namespace MDSD
}  // namespace RB
