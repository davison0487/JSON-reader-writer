//
//  JSONReader.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "JSONReader.hpp"
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstring>


namespace ECE141 {

  using parseCallback = bool(char aChar);

  bool isWhitespace(char aChar) {
    static const char* theWS = " \t\r\n\b\xff";
    return strchr(theWS,aChar);
  }

  bool isColon(char aChar) {return kColon==aChar ? true  : false;}
  bool isComma(char aChar) {return kComma==aChar ? true  : false;}
  bool isQuote(char aChar) {return kQuote==aChar ? true  : false;}
  bool isContant(char aChar) {return isalnum(aChar) || '.'==aChar;}

  //------------------------------------------------------

  JSONReader::JSONReader(JSONModel &aModel, std::istream &anInput) : JSONParser(anInput), model(aModel) {
    anInput >> std::skipws;
  }
  
  //-----------------------------------------------------

  TokenType determineType(char aChar) {
    const char* kConstantChars="01234567890tf";
    switch(aChar) {
      case kQuote: return TokenType::quoted;
      case kColon: return TokenType::colon;
      case kBraceOpen: return TokenType::openObject;
      case kBracketOpen: return TokenType::openList;
      case kBraceClose: return TokenType::closeObject;
      case kBracketClose: return TokenType::closeList;
      default:
        return strchr(kConstantChars, aChar)
          ? TokenType::constant : TokenType::unknown;
    }
    return TokenType::unknown;
  }

  //--- handle the goo inside our container ------------------

  bool JSONReader::parseElements(char aChar) {
    bool theResult=true;
    
    TokenType theType = determineType(aChar);
    std::string temp("");

    switch(theType) {
    case TokenType::openObject: {
        if (partStack.size() != 0) {
            //not the base object
            JSONPart* theObject = new JSONObject(temp);
            JSONPart* topPart = partStack.top();
            topPart->addElement(theObject);
            partStack.push(theObject);
        }
        else {
            //is base object
            JSONPart* theBaseObject = new JSONObject("base");
            partStack.push(theBaseObject);
        }
        break;
    }
    
    case TokenType::openList: {
        JSONPart* topPart = partStack.top();
        JSONPart* theList = new JSONList(temp);
        topPart->addElement(theList);
        partStack.push(theList);
        break;
    }
    
    case TokenType::closeList: {
        partStack.pop();          //pop list
        JSONPart* topPart = partStack.top();
        if (topPart->type == JSONType::element) {
            //element complete
            partStack.pop();
        }
        break;
    }
    
    case TokenType::closeObject: {
        JSONPart* topPart = partStack.top();
        partStack.pop();          //pop object
        if (partStack.size() == 0) {
            //base object complete, set the baseObject to top object
            model.setBase(topPart);
            break;
        }
        topPart = partStack.top();
        if (topPart->type == JSONType::element) {
            //element complete
            partStack.pop();
        }
        break;
    }
    
    case TokenType::quoted: {
        temp = readUntil(isQuote, false);
        skipIfChar(kQuote);
        JSONPart* topPart = partStack.top();
        if (topPart->type == JSONType::element) {
            //if top part is an element, complete it and pop out of stack
            JSONPart* newStrConst = new JSONStrConst(temp); 
            topPart->addElement(newStrConst);
            partStack.pop();
        }
        else if (topPart->type == JSONType::list) {
            //if top part is a list, add a new element to it
            JSONPart* newStrConst = new JSONStrConst(temp);
            topPart->addElement(newStrConst);
        }
        else {
            //if it is not, add a new element to the top part and push to stack
            JSONPart* newElement = new JSONElement(temp);
            topPart->addElement(newElement);
            partStack.push(newElement);
        }
        break;
    }
    
    case TokenType::constant: {
        temp = readWhile(isContant, false);
        temp.insert(0, 1, aChar);
        JSONPart* topPart = partStack.top();
        JSONPart* newStrConst = new JSONStrConst(temp);
        topPart->addElement(newStrConst);
        if (topPart->type == JSONType::element) {
            //if top part is an element, it is completed
            partStack.pop();
        }
        break;
    }
        
        
    case TokenType::colon: {
        break; //likely between key/value
    }
                         
    default: break;
    }
    
    skipWhile(isWhitespace);
    return theResult;
  }
  
//--------------------------------------------------------------------

  bool JSONReader::willTokenize() {    
    return true;
  }

  //--------------------------------------------------------------------

  bool JSONReader::tokenize() {
    if(willTokenize()) {
      
      bool isValid=true;
      while(isValid) {
        skipWhile(isWhitespace);
        if(!input.eof()) {
          char theChar=input.get();
          isValid = parseElements(theChar);
          skipWhile(isWhitespace);
          skipIfChar(kComma);
        }
        else break;
      }
      
      return didTokenize(isValid);
    }
    return true;
  }

  //-----------------------------------------------------------

  bool JSONReader::didTokenize(bool aState) {
    return aState;    
  }
  

}
