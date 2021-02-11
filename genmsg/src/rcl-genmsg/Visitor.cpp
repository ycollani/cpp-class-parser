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

#include "../rcl-genmsg/Visitor.h"

#include <map>
#include "../rcl-genmsg/utils.h"

namespace VC {
namespace MDSD {

// ========================================
// ==
// ========================================

Visitor::~Visitor (void)
{

}


// ========================================
// ==
// ========================================

Visitor::Visitor(clang::CompilerInstance *CI, std::map<std::string, ClassInformation> *_classMap, TypedefInformation *_typedefInformation)
: astContext(&(CI->getASTContext())) // initialize private members
, classMap { _classMap }
, typedefInformation { _typedefInformation }
{
    //rewriter.setSourceMgr (astContext->getSourceManager(), astContext->getLangOpts());
}


// ========================================
// ==
// ========================================

bool Visitor::VisitType (clang::Type *Type)
{
    std::string typeClass = Type->getTypeClassName ();

    //std::cout << "typeClassName: " << typeClass << std::endl;

    if (typeClass == "Typedef")
    {
        const clang::TypedefType* TypeDef = Type->getAs<const clang::TypedefType>();
        clang::TypedefNameDecl   *decl = TypeDef->getDecl()->getCanonicalDecl();

        std::string newType = decl->getQualifiedNameAsString ();
        std::string oldType =  decl->getUnderlyingType ().getAsString();

//        std::cout << "getNameAsString: " << newType << std::endl;
//        std::cout << "uType.getAsString: " << oldType << std::endl;

        (*typedefInformation)[newType] = oldType;
    }



    return true;
}


// ========================================
// ==
// ========================================

bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl *decl)
{
	clang::SourceManager &sourceManager = astContext->getSourceManager();

	clang::CXXRecordDecl *Declaration= decl->getCanonicalDecl();


	///std::string currentClass = Declaration->getQualifiedNameAsString();

//	std::string canonicalName = Declaration->getCanonicalDecl()->getQualifiedNameAsString() ;
//	(*classMap)[canonicalName] = Declaration;


    if (Declaration->isClass() == true)
    {
        if (Declaration->getDefinition() != nullptr)
        {
            processClassDeclration (Declaration, sourceManager);
            return true;
        }
    }


//    std::string canonicalName = Declaration->getCanonicalDecl()->getQualifiedNameAsString() ;
//
//    std::cout << "non class declaration: " << canonicalName << std::endl;




	return true;
}


// ========================================
// ==
// ========================================

void Visitor::processClassDeclration (clang::CXXRecordDecl *Declaration, clang::SourceManager &sourceManager)
{
    if (classMap->find(Declaration->getQualifiedNameAsString()) != classMap->end() )
        return;

    ClassInformation currentClass (Declaration->getQualifiedNameAsString());

    clang::SourceLocation loc = Declaration->getLocation();
    if (loc.isValid() && loc.isFileID())
    {
        currentClass.setFileName(sourceManager.getFilename(loc).str());
        //currentClass.setDirName(sourceManager.getDir(loc).getName().str());
    }


//      std::cout << std::endl;
//      std::cout << "CXXRecoredDecL: " << Declaration->getQualifiedNameAsString() << std::endl;
//      std::cout << "  isCXXClassMember               : " << Declaration->isCXXClassMember() << std::endl;
//
//      std::cout << "  isTemplateDecl                 : " << Declaration->isTemplateDecl() <<std::endl;
//      std::cout << "  isBeingDefined                 : " << Declaration->isBeingDefined() << std::endl;
//      std::cout << "  isCompleteDefition             : " <<  Declaration->isCompleteDefinition() << std::endl;
//
//      std::cout << "  isCompleteDefinitionRequired   : " << Declaration->isCompleteDefinitionRequired() << std::endl;
//      std::cout << "  isExternCXXContext             : " << Declaration->isExternCXXContext() << std::endl;
//
//
//      std::cout << "  hasDirectFields                : " << Declaration->hasDirectFields() << std::endl;
//      std::cout << "  isEmpty                        : " << Declaration->isEmpty() << std::endl;
//      std::cout << "  isAggregat                     : " << Declaration->isAggregate() << std::endl;
//
//      std::cout << "  hasTrivialDefaultConstructor   : " << Declaration->hasTrivialDefaultConstructor() << std::endl;
//      std::cout << "  hasNonTrivialDefaultConstructor: " << Declaration->hasNonTrivialDefaultConstructor() << std::endl;


    for (auto it = Declaration->field_begin(); it != Declaration->field_end(); it++)
    {
        clang::FieldDecl* field = *it;
        clang::QualType   type  = field->getType();

//          std::cout << "  Field: " << field->getNameAsString() << std::endl;
//          if (type.isTrivialType(*astContext) == true)
//          {
//              std::cout << "    TrivialType" << std::endl;
//              std::cout << "    isCanonical: " << type.isCanonical() << std::endl;
//              std::cout << "    getAsString: " << type.getAsString().c_str() << std::endl;
//              if (type.isConstant(*astContext) == true) std::cout << "  is constant" << std::endl; else std::cout << "  is not constant" << std::endl;
//              std::string cName = type.getCanonicalType().getAsString();
//              std::cout << "    cannicalTypeName: " << cName << std::endl;
//              auto record = classMap->find (cName);
//              if (record != classMap->end())
//                  std::cout << "    in classMap" << std::endl;
//          }


        bool isPrivate = field->getAccess() ==  clang::AccessSpecifier::AS_private;

        if ((type.isConstQualified() == false) && (isPrivate == false))
        {
//              if (type.isTrivialType (*astContext) == true)
//              {
//                  std::cout << "member is trivial: " << type.getAsString() << std::endl;
//              }

            bool isCanonical     = type.isTrivialType (*astContext);
            std::string typeName = type.getAsString();

//              if (type.isCanonical() == false)
//              {
//                  clang::QualType   ctype = type.getCanonicalType();
//                  typeName = ctype.getAsString();
//              }

            MemberInformation member (field->getNameAsString(), typeName, isCanonical);

            currentClass.insertMember(member);
        }
//          else {
//              std::cout << "member is const: " << type.getAsString() << std::endl;
//          }

    }

//      std::cout << "NumBases: " << Declaration->getNumBases() << std::endl;
    for (auto it = Declaration->bases_begin(); it != Declaration->bases_end(); it++)
    {
        clang::CXXBaseSpecifier* baseClass = it;

        currentClass.insertBaseClass(baseClass->getType().getAsString());

//          std::cout << "bases: " << baseClass->getType().getAsString() << std::endl;
//          clang::QualType type = it->getType();
//          if (type.isTrivialType(*astContext) == true)
//          {
//              std::cout << "    TrivialType" << std::endl;
//              std::cout << "    isCanonical: " << type.isCanonical() << std::endl;
//              std::cout << "    getAsString: " << type.getAsString().c_str() << std::endl;
//              if (type.isConstant(*astContext) == true) std::cout << "  is constant" << std::endl; else std::cout << "  is not constant" << std::endl;
//              auto record = classMap->find (type.getAsString());
//              if (record != classMap->end())
//                  std::cout << "    in classMap" << std::endl;
//          }
    }

    for (auto it = Declaration->method_begin(); it != Declaration->method_end(); ++it)
    {
        const clang::CXXMethodDecl *canonicalDecl = it->getCanonicalDecl();

        //std::cout << "Class: " << Declaration->getQualifiedNameAsString() << "  -- Method: " << canonicalDecl->getNameAsString() << std::endl;
        currentClass.insertMethod (canonicalDecl->getNameAsString());
    }

    (*classMap)[Declaration->getQualifiedNameAsString()] = currentClass;
}


}  // namespace MDSD
}  // namespace RB

