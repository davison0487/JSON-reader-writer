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
#include <vector>

namespace ECE141 {

  enum class TokenType {
    openObject, openList, closeList, closeObject,
    constant, quoted, colon, unknown};

  enum class JSONType {object, list, element, constant, unknown};

  //-----JSONPart-----//

  struct JSONPart {
      JSONPart(JSONType aType) : type(aType) {};
      virtual ~JSONPart() {};

      virtual void debugDump(std::ostream& anOutput, int indent = 0) {};
      virtual void addElement(JSONPart* const aPart) {};
      
      JSONType type;
  };

  //-----JSONPart-----//

  //-----JSONStrConst-----//

  struct JSONStrConst : public JSONPart {
  public:
      JSONStrConst(const std::string& aValue)
          : JSONPart(JSONType::constant), value(aValue) {};

      virtual ~JSONStrConst() {};

      virtual void debugDump(std::ostream &anOutput, int anIndent=0);
      
  protected:
      std::string value;
  };

  //-----JSONStrConst-----//

  //-----JSONElement-----//

  class JSONElement : public JSONPart {
  public:
      JSONElement(const std::string &aKey, JSONPart *aValue=nullptr) : 
          JSONPart(JSONType::element),
          key(aKey),
          value(aValue) {};

      virtual ~JSONElement();

      virtual void debugDump(std::ostream& anOutput, int indent = 0);
      virtual void addElement(JSONPart* const aPart);

  protected:
      std::string key;
      JSONPart    *value;
  };

  //-----JSONElement-----//

  //-----JSONList-----//

  class JSONList : public JSONPart {
  public:
      JSONList(const std::string &aName) : 
          listName(aName),
          JSONPart(JSONType::list) {};

      virtual ~JSONList();

      virtual void debugDump(std::ostream& anOutput, int indent = 0);
      virtual void addElement(JSONPart* const aPart);
      

  protected:
      //STUDENT: add something to hold list of items...
      std::string listName;
      std::vector<JSONPart*> elementList;
    
  };

  //-----JSONList-----//

  //-----JSONObject-----//

  class JSONObject : public JSONPart{
  public:
      JSONObject(const std::string &aName) :
          objectName(aName),
          JSONPart(JSONType::object) {};

      virtual ~JSONObject();

      virtual void debugDump(std::ostream& anOutput, int indent = 0);
      virtual void addElement(JSONPart* const aPart);
      
  protected:
      //STUDENT: add something to hold key value pairs...
      std::string objectName;
      std::vector<JSONPart*> elementList;
    
  };

  //-----JSONObject-----//

  //-----JSONModel-----//

  class JSONModel : public JSONPart {
  public:
      JSONModel() : 
          baseObject(nullptr), 
          JSONPart(JSONType::unknown) {};

      virtual ~JSONModel();

      virtual void debugDump(std::ostream& anOutput, int indent = 0);

      void setBase(JSONPart* const aPart);

  protected:
      JSONPart* baseObject;

  };

  //-----JSONModel-----//

}
#endif /* JSONModel_hpp */
