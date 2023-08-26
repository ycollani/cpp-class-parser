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


#include "ClassInformation.h"

#include <iostream>

namespace VC
{
namespace MDSD
{


void MemberInformation::Show(void) const
{
    std::cout << "    member: " << name << "   type: " << typeName << "   canonical: " << trivialType << std::endl;
}

ClassInformation::ClassInformation(const ClassInformation &right)
: simpleName_(right.simpleName_)
, namespaceName_(right.namespaceName_)
, fileName_(right.fileName_)
, dirName_(right.dirName_)
, hasTrivialDefaultConstructor_(right.hasTrivialDefaultConstructor_)
, hasNonTrivialDefaultConstructor_(right.hasNonTrivialDefaultConstructor_)
, isCXXClassMember_(right.isCXXClassMember_)
{
    baseClasses_ = right.baseClasses_;
    members_     = right.members_;
}

ClassInformation::ClassInformation(const std::string &simpleClassName)
: simpleName_(simpleClassName)
{
}

ClassInformation::~ClassInformation(void)
{
}

void ClassInformation::Show(void) const
{
    std::cout << "CXXRecoredDecL                   : " << simpleName_ << std::endl;
    std::cout << "  Namespace                      : " << namespaceName_ << std::endl;
    std::cout << "  FileName                       : " << fileName_ << std::endl;
    std::cout << "  DirName                        : " << dirName_ << std::endl;
    std::cout << "  hasTrivialDefaultConstructor   : " << hasNonTrivialDefaultConstructor_ << std::endl;
    std::cout << "  hasNonTrivialDefaultConstructor: " << hasNonTrivialDefaultConstructor_ << std::endl;
    std::cout << "  isCXXClassMember               : " << isCXXClassMember_ << std::endl;

    for (std::string b : baseClasses_)
    {
        std::cout << "base: " << b << std::endl;
    }

    for (MemberInformation m : members_)
    {
        m.Show();
    }
}



std::string TypedefInformation::replaceType (const std::string &typeName)
{
    std::string rc = typeName;

    // do not replace std::string with basic_string<char>
    if (rc == "std::string") return rc;

    auto it = find (typeName);
    if (it != end())
    {
        //std::cout << "Replace "  << typeName << "  with  " << it->second << std::endl;

        rc = replaceType (it->second);
    }
    return rc;
}



}  // namespace MDSD
}  // namespace RB
