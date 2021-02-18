//
//  TestClass1.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass1.hpp"
#include <unordered_map>

static std::unordered_map<bool, std::string> boolMap{ {false, "false"}, {true, "true"} };

namespace ECE141 {

  TestClass1::TestClass1(const std::string &aName,
                         bool aUsed, float anAmount, int aCount)
    : name(aName), used(aUsed), amount(anAmount), count(aCount) {}

  TestClass1::~TestClass1() {}

  bool TestClass1::toJSON(std::ostream &aStream) {
      aStream << "{\n"
          //-----meta------//
          << "\"meta\" : {\n"
          << "\"class\" : \"TestClass1\",\n"
          << "\"version\" : 1.0\n"
          << "},\n"
          //-----meta-----//
          //-----members-----//
          << "\"members\" : {\n"
          << "\"name\" : " << "\"" << name << "\",\n"
          << "\"count\" : " << count << ",\n"
          << "\"amount\" : " << amount << ",\n"
          << "\"used\" : " << boolMap[used] << std::endl
          << "}\n"
          //-----members-----//
          << "}\n";
      return true;
  }

}
