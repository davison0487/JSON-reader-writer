//
//  TestClass2.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass2.hpp"
#include <unordered_map>

static std::unordered_map<bool, std::string> boolMap{ {false, "false"}, {true, "true"} };

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
      aStream << "{\n"
          //-----meta------//
          << "\"meta\" : {\n"
          << "\"class\" : \"TestClass2\",\n"
          << "\"version\" : 1.0\n"
          << "},\n"
          //-----meta-----//
          //-----members-----//
          << "\"members\" : {\n"
          << "\"name\" : " << "\"" << name << "\",\n"
          << "\"size\" : " << size << ",\n"
          //-----Metadata-----//
          << "\"meta\" : {\n" 
          << "\"prop1\" : " << "\"" << meta.prop1 << "\",\n"
          << "\"prop2\" : " << "\"" << meta.prop2 << "\",\n"
          << "\"prop3\" : " << meta.prop3 << "\n"
          << "}\n"
          //-----Metadata-----//
          << "}\n"
          //-----members-----//
          << "}\n";
      return true;
  }

}
