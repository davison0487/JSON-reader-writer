//
//  TestClass1.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass1.hpp"
#include <unordered_map>

static std::unordered_map<bool, std::string> bool2str{ {false, "false"}, {true, "true"} };

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
          << "\"used\" : " << bool2str[used] << std::endl
          << "}\n"
          //-----members-----//
          << "}\n";
      return true;
  }

  void TestClass1::buildClass(JSONObject* aObject) {
      std::vector<JSONElement*> elements = aObject->getElement();
      JSONObject* membersObject = nullptr;

      for (auto element : elements) {
          if (element->getKey() == "members") {
              membersObject = element->getObject();
          }
      }

      std::vector<JSONElement*> members = membersObject->getElement();

      for (auto member : members) {
          std::string memberName = member->getKey();
          if (memberName == "name") {
              name = member->getConst()->getValue();
          }
          else if (memberName == "count") {
              std::string temp = member->getConst()->getValue();
              count = std::stoi(temp);
          }
          else if (memberName == "amount") {
              std::string temp = member->getConst()->getValue();
              amount = std::stof(temp);
          }
          else if (memberName == "used") {
              std::string temp = member->getConst()->getValue();
              used = temp == "true" ? true : false;
          }
          else
              continue;
      }
  }

}
