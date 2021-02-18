//
//  TestClass3.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include <cstring>
#include "TestClass3.hpp"

namespace ECE141 {

  TestClass3::TestClass3(const std::string &aName,
                         Color aColor, const char *aBuf)
    : name(aName), color(aColor) {      
      std::strncpy(initials, aBuf,3);  //autograder
      //strncpy_s(initials, 4 ,aBuf, 3); //windows
    }

  TestClass3::~TestClass3() {}

  bool TestClass3::toJSON(std::ostream &aStream) {
      aStream << "{\n"
          //-----meta------//
          << "\"meta\" : {\n"
          << "\"class\" : \"TestClass3\",\n"
          << "\"version\" : 1.0\n"
          << "},\n"
          //-----meta-----//
          //-----members-----//
          << "\"members\" : {\n"
          << "\"name\" : " << "\"" << name << "\",\n"
          //-----initials-----//
          << "\"initials\" : [\n"
          << "\"" << initials[0] << "\",\n"
          << "\"" << initials[1] << "\",\n"
          << "\"" << initials[2] << "\"\n"
          << "],\n"
          //-----initials-----//
          << "\"color\" : " << (int)color << std::endl
          << "}\n"
          //-----members-----//
          << "}\n";
    return true;
  }


}
