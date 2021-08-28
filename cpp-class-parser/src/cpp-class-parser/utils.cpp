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


#include "../cpp-class-parser/utils.h"

#include <iostream>
#include <boost/filesystem.hpp>

// ========================================
// ==
// ========================================

// ========================================
// ==
// ========================================

bool isBaseType (const std::string &typeName)
{
	 if      (typeName == "int") return true;
	 else if (typeName == "unsigned int") return true;
	 else if (typeName == "short") return true;
	 else if (typeName == "unsigned short") return true;
	 else if (typeName == "char") return true;
	 else if (typeName == "unsigned char") return true;
	 else if (typeName == "long") return true;
	 else if (typeName == "unsigned long") return true;
	 else if (typeName == "int8_t") return true;
	 else if (typeName == "int16_t") return true;
	 else if (typeName == "int32_t") return true;
	 else if (typeName == "int64_t") return true;
	 else if (typeName == "uint8_t") return true;
	 else if (typeName == "uint16_t") return true;
	 else if (typeName == "uint32_t") return true;
	 else if (typeName == "uint64_t") return true;
	 else if (typeName == "float") return true;
	 else if (typeName == "double") return true;
	 else if (typeName == "bool") return true;

	return false;
}


void truncSpace (std::string s)
{
	while (s.size() && s[0] == ' ') s.erase (0,1);
	while (s.size() && s[s.size() -1] == ' ') s.erase (s.size() - 1 ,1);
}


std::string getPureClassName (const std::string &s)
{
    const auto pos = s.find_last_of(':');
    if (pos == std::string::npos)
        return s;

    std::string returnValue = s.substr (pos+1);
    return returnValue;
}


std::string getRelativePath  (const std::string &fileName, const std::string &currentDir)
{
  std::string directory = boost::filesystem::path(fileName).parent_path().generic_string();

  while ( (directory.length() > 0) && (directory != currentDir))
  {
      directory = boost::filesystem::path(directory).parent_path().generic_string();
  }

  std::string returnValue;
  if (directory.length())
  {
      returnValue = fileName.substr (directory.length() + 1);
  }
  else
  {
      returnValue = fileName;
  }
  return returnValue;
}


const VC::MDSD::ClassInformation* findMessageClass (std::map<std::string, VC::MDSD::ClassInformation> *classMap, const std::string &baseClass)
{
    for (auto &it : *classMap)
    {
        std::string      name = it.first;
        VC::MDSD::ClassInformation &c   = it.second;

        //std::cout << "Check " << name << " for message class for type: " << baseClass << std::endl;

        size_t numBaseClasses = c.getNumBasesClasses();
        for (size_t index = 0; index < numBaseClasses; index++)
        {
            //std::cout << "  base (" << index << "): " << c.getBaseClass(index) << std::endl;
            if (c.getBaseClass (index) ==  baseClass)
            {
                //std::cout << "    check name of " << name << "  " <<  name.substr (name.size() - 4, 3) << std::endl;
                if (name.substr (name.size() - 3, 3) == "Msg")
                {
                    //std::cout << "Found: " << name << std::endl;
                    return &c;
                }
            }
        }
    }
    return nullptr;
}
