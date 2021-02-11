//
//  TestClass2.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass2.hpp"

namespace ECE141 {

  TestClass2::TestClass2(const std::string &aName, size_t aSize,
                         const Metadata &aMeta) : 
    name(aName), size(aSize) {
      meta.prop1=aMeta.prop1;
      meta.prop2=aMeta.prop2;
      meta.prop3=aMeta.prop3;
  }
  
  TestClass2::~TestClass2() {}

  bool TestClass2::toJSON(std::ostream &aStream) {
    return true;
  }

}
