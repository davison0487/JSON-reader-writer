//
//  JSONModel.hpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#ifndef JSONModel_hpp
#define JSONModel_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>

namespace ECE141 {

  enum class TokenType {
    openObject, openList, closeList, closeObject,
    constant, quoted, colon, unknown};

  enum class JSONType {object, list, element, constant, unknown};

  //-----------------------------

  struct JSONPart {
    JSONPart(JSONType aType) : type(aType) {}
    virtual void debugDump(std::ostream &anOutput, int indent=0);

    JSONType type;
  };

  //-----------------------------

  struct JSONStrConst : public JSONPart {
    JSONStrConst(const std::string &aValue)
      : JSONPart(JSONType::constant), value(aValue) {}

    virtual void debugDump(std::ostream &anOutput, int anIndent=0);

    std::string value;
  };

  //-----------------------------

  class JSONElement : public JSONPart {
  public:

    JSONElement(const std::string &aKey, JSONPart *aValue=nullptr);

  protected:
    std::string key;
    JSONPart    *value;
  };

  //-----------------------------

  class JSONList : public JSONPart {
  public:
    JSONList(const std::string &aName);

  protected:

    //STUDENT: add something to hold list of items...
  };

  //-----------------------------

  class JSONObject : public JSONPart{
  public:

    JSONObject(const std::string &aName);

  protected:

    //STUDENT: add something to hold key value pairs...
  };

  class JSONModel : public JSONPart {
  public:
    JSONModel();
   
    //STUDENT: implement these methods...

  };
 

}
#endif /* JSONModel_hpp */
