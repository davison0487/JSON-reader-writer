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
      std::strncpy(initials, aBuf,3);
    }

  TestClass3::~TestClass3() {}

  bool TestClass3::toJSON(std::ostream &aStream) {
    return true;
  }


}
