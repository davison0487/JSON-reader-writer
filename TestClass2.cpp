//
//  TestClass2.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass2.hpp"
#include <unordered_map>

static std::unordered_map<bool, std::string> bool2str{ {false, "false"}, {true, "true"} };

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
          << "\"prop3\" : " << bool2str[meta.prop3] << "\n"
          << "}\n"
          //-----Metadata-----//
          << "}\n"
          //-----members-----//
          << "}\n";
      return true;
  }

  void TestClass2::buildClass(JSONObject* aObject) {
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
          else if (memberName == "size") {
              std::string temp = member->getConst()->getValue();
              size = (size_t)std::stoi(temp);
          }
          else if (memberName == "meta") {
              std::vector<JSONElement*> metaElements = member->getObject()->getElement();
              for (auto metaElement : metaElements) {
                  std::string metaElementName = metaElement->getKey();
                  if (metaElementName == "prop1") {
                      meta.prop1 = metaElement->getConst()->getValue()[0];
                  }
                  else if (metaElementName == "prop2") {
                      meta.prop2 = metaElement->getConst()->getValue()[0];
                  }
                  else {
                      std::string temp = metaElement->getConst()->getValue();
                      meta.prop3 = temp == "true" ? true : false;
                  }
              }
          }
          else
              continue;
      }
  }

}
