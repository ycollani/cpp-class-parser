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

#ifndef CLASSINFORMATION_H_
#define CLASSINFORMATION_H_

#include <vector>
#include <map>
#include <utility>

namespace VC {
namespace MDSD {

// ========================================
// ==
// ========================================

class MemberInformation
{
protected:
	std::string name;
	std::string simpleTypeName;
	std::string typeName;

	bool        trivialType = false;

public:
	MemberInformation (void)
 	{

 	}

	MemberInformation (const std::string &_name, const std::string &_type, bool _c)
    : name (_name), typeName (_type), trivialType {_c}
	{
	    if (typeName == "_Bool") typeName = "bool";
	    if (typeName.substr (0,6) == "class ")
	        simpleTypeName = typeName.substr (6, std::string::npos);
	    else
	        simpleTypeName = typeName;
	}

    const std::string& getName(void) const { return name; }
    const std::string& getSimpleTypeName(void) const { return simpleTypeName; }
    const std::string& getTypeName(void) const { return typeName; }
    bool               isTrivialType(void) const { return trivialType; }

    void Show (void) const;
};


// ========================================
// ==
// ========================================

class ClassInformation
{
protected:
	std::string simpleName_;
	std::string namespaceName_;
	std::string fileName_;
	std::string dirName_;

	std::vector<std::string>       baseClasses_;
	std::vector<MemberInformation> members_;
	std::vector<std::string>       methods_;

	bool        hasTrivialDefaultConstructor_    = false;
	bool        hasNonTrivialDefaultConstructor_ = false;
	bool        isCXXClassMember_                = false;

public:
	ClassInformation (void) { };
	ClassInformation (const ClassInformation &right);
	ClassInformation (const std::string &simpleClassName);
	virtual ~ ClassInformation (void);

	void setNamespace    (const std::string &_namespaceName) { namespaceName_ = _namespaceName; }
	void setFileName     (const std::string &_fileName)      { fileName_ = _fileName; }
	void setDirName      (const std::string &_dirName)       { dirName_ = _dirName; }
	void insertBaseClass (const std::string &_baseClass) { baseClasses_.push_back (_baseClass); }
	void insertMember    (const MemberInformation &_m)  { members_.push_back (_m); }
	void insertMethod    (const std::string &_method) { methods_.push_back (_method); }

	void setHasTrivialDefaultConstructor (bool flag)    { hasTrivialDefaultConstructor_ = flag; }
	void setHasNonTrivialDefaultConstructor (bool flag) { hasNonTrivialDefaultConstructor_ = flag; }
	void setIsCXXClassMemeber (bool flag)               { isCXXClassMember_ = flag; }

	const std::string& getName (void)      const { return simpleName_; }
	const std::string& getNameSpace (void) const { return namespaceName_; }
	const std::string& getDirName (void)   const { return dirName_; }
	const std::string& getFileName (void)  const { return fileName_; }

	size_t             getNumBasesClasses (void) const { return baseClasses_.size(); }
	const std::string& getBaseClass (int index) const  { return baseClasses_[index]; }

	size_t                   getNumMembers (void)      const { return members_.size(); }
	const MemberInformation& getMember     (int index) const { return members_[index]; }

	size_t             getNumMethods () const { return methods_.size(); }
	const std::string& getMethod (int index) const { return methods_[index]; }

	bool hasTrivialDefaultConstructor (void)    const { return hasTrivialDefaultConstructor_ ; }
	bool hasNonTrivialDefaultConstructor (void) const { return hasNonTrivialDefaultConstructor_; }
	bool isCXXClassMember (void)                const { return isCXXClassMember_ ; }

	void Show (void) const;


};


// ========================================
// ==
// ========================================


class MessageClassDirectory : public std::map<std::string, std::pair<std::string,std::string>>
{
public:
	MessageClassDirectory (void) { }
	~MessageClassDirectory (void) { }
};


// ========================================
// ==
// ========================================

class TypedefInformation : public std::map<std::string, std::string>
{
public:
    TypedefInformation () { }
    ~TypedefInformation() { }

    std::string replaceType (const std::string &typeName);
};


}  // namespace MDSD
}  // namespace RB



#endif /* CLASSINFORMATION_H_ */
