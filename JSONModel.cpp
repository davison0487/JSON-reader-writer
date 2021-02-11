//
//  JSONModel.cpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#include "JSONModel.hpp"

namespace ECE141 {
  
  void JSONPart::debugDump(std::ostream &anOutput, int anIndent) {
  }
  
  //---------------------------------------

  JSONElement::JSONElement(const std::string &aKey,
                           JSONPart *aValue)
    : JSONPart(JSONType::element), key(aKey), value(aValue) {}

  //---------------------------------------

  JSONList::JSONList(const std::string &aName)
    : JSONPart(JSONType::list) {}


  JSONObject::JSONObject(const std::string &aName) : JSONPart(JSONType::object) {}
  

  //---------------------------------------

  JSONModel::JSONModel() : JSONPart(JSONType::object) {
  }

    
}
