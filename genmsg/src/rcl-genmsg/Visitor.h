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

#ifndef VISITOR_H_
#define VISITOR_H_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcomment"

#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
//#include "clang/Rewrite/Core/Rewriter.h"

#pragma GCC diagnostic pop

#include <iostream>
#include "../rcl-genmsg/ClassInformation.h"

namespace VC {
namespace MDSD {

class Visitor : public clang::RecursiveASTVisitor<VC::MDSD::Visitor>
{
private:
    clang::ASTContext *                      astContext;  // used for getting additional AST info
    std::map<std::string, ClassInformation> *classMap = nullptr;
    TypedefInformation *                     typedefInformation;

    void processClassDeclration (clang::CXXRecordDecl *Declaration, clang::SourceManager &sourceManager);

public:
    explicit Visitor (clang::CompilerInstance *CI, std::map<std::string, ClassInformation> *_classMap, TypedefInformation *_typedefInformation);
    virtual ~Visitor (void);

    virtual bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration);
    virtual bool VisitType (clang::Type *Type);
};


}  // namespace MDSD
}  // namespace RB


#endif /* VISITOR_H_ */
