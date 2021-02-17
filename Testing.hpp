//
//  Testing.hpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#ifndef Testing_h
#define Testing_h

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cstring>
#include <cctype>
#include "JSONReader.hpp"
//#include "JSONWriter.hpp"
#include "Builder.hpp"

namespace ECE141 {
  
  struct Testing  {

    const int kMinDumpSize=600;

    Testing() {
    }
    
    ~Testing() {
      std::cout << "Test Version 1.2\n";
    }

    //---------------------------

    bool doCompileTest() {
      return true;
    }

    //---------------------------
    
    uint32_t crc32(const std::string &aString) {
      const char* aBuffer=aString.c_str();
      uint32_t theResult = ~0; const char *end = aBuffer + aString.size();
      while(aBuffer < end) {
        theResult ^= *aBuffer++;
        for(int i = 0; i < 8; i++) {
          uint32_t temp = ~((theResult&1) - 1);
          theResult = (theResult>>1) ^ (0xEDB88320 & temp);
        }
      }
      return ~theResult;
    }
     
    //improved version of write test validator...
    bool validateWriteTest(const std::string &aString) {
      //std::cout << aString << "\n";
      
      if(aString.size()<kMinDumpSize)
        return false; //too small...

      static std::map<std::string, std::string> thePairs = {
        {"\"version\"", "1.0"},
        {"\"members\"", "{"},
        {"child1a", "{"},
        {"child1b", "{"},
        {"child2", "{"},
        {"child3", "{"},
        {"\"price\"", "35.99"},
        {"count", "oneA"},
        {"amount", "3.14"},
        {"size", "99"},
      };
      //class,name,used,amount,count, meta
      
      std::stringstream theInput(aString);
      const int kBufSize=1024;
      char theBuffer[1024];
      
      std::string theValue;
      std::string theKey;
      
      while(!theInput.eof()) {
        theInput.getline(theBuffer, kBufSize);
        if(std::strlen(theBuffer)) {
          
          std::string temp(theBuffer);
          
          temp.erase(std::remove_if(temp.begin(),temp.end(),
                                    ::isspace), temp.end());
          
          auto thePos=temp.find(':');
          if (thePos!=std::string::npos) {
            theValue=temp.substr(thePos+1);
            theKey=temp.substr(0,thePos);
            if(theValue[theValue.size()-1]==',') {
              theValue.pop_back();
            }
            
            if("\"used\""==theKey) {
              char theChar=tolower(theValue[0]);
              if(theChar!='t' && theChar!='f')
                return false;
            }
            else if("\"amount\""==theKey) {
              if(theValue!="3.14" && theValue!="6.28")
                return false;
            }
            else if("\"count\""==theKey) {
              if(theValue!="1234" && theValue!="567")
                return false;
            }
            else if (thePairs.count(theKey) > 0) {
              if(thePairs[theKey]!=theValue) {
                return false;
              }
            }
            
          }

        }
      } //while
      return true;
    }
    
    //write doc as JSON to stream, and verify output
    bool doWriteTest() {
      std::stringstream theStream;
      TestDocument theDocument;
      
      if(theDocument.toJSON(theStream)) {
        std::string theString=theStream.str();
        return validateWriteTest(theString);
      }
      return false;
    }

    //---------------------------
    
    bool generateTestFile(std::ostream &aStream) {
      const char* theLines[] = {
        "{",
          "\"courseId\":\"ECE-141A\",",
          "\"courseName\":\"Software Foundations\",",
          "\"studentList\":[",
          "  {",
          "    \"id\":\"foo\",",
          "    \"name\":\"Foo Bar\",",
          "    \"pId\":\"A22222222\",",
          "    \"gpa\":3.95,",
          "    \"isGradStudent\":true",
          "  },",
          "  {",
          "    \"id\":\"bar\",",
          "    \"name\":\"Bar Foo\",",
          "    \"pId\":\"A99999999\",",
          "    \"gpa\":3.85,",
          "    \"isGradStudent\":false",
          "  }",
          "],",
          "\"schedule\": {",
          "  \"lectures\": \"Tu-Thu 9:30AM\",",
          "  \"discussions\": \"Mon 4:00PM\"",
          "}",
        "}"
      };
      for(auto theLine : theLines) {
        aStream << theLine << "\n";
      }
      return true;
    }
      
    //--------------------------------------------------------
      
    bool validateReaderDump(const std::string &aString) {
      static std::map<std::string, std::string> theTestData = {
        {"ECE-141A", "courseId"},
        {"SoftwareFoundations", "courseName"},
        {"foo", "id"},
        {"FooBar", "name"},
        {"A22222222", "pId"},
        {"3.95", "gpa"},
        {"true", "isGradStudent"},
        {"bar", "id"},
        {"BarFoo", "name"},
        {"A99999999", "pId"},
        {"3.85", "gpa"},
        {"false", "isGradStudent"},
        {"Tu-Thu9:30AM", "lectures"},
        {"Mon4:00PM", "discussions"},
      };
      
      const int kMinLen=250;
      if(aString.size()>kMinLen) {
        std::stringstream theInput(aString);
        const int kBufSize=1024;
        char theBuffer[1024];
        
        std::string theValue;
        std::string theKey;
        
        while(!theInput.eof()) {
          theInput.getline(theBuffer, kBufSize);
          if(std::strlen(theBuffer)) {
            
            std::string temp(theBuffer);
            
            temp.erase(std::remove_if(temp.begin(),temp.end(),
                                      ::isspace), temp.end());
            
            auto thePos=temp.find('=');
            if (thePos!=std::string::npos) {
              theKey=temp.substr(thePos+1);
              theValue=temp.substr(0,thePos);
              //std::cout << theKey << ":" << theValue << "\n";
              if (theTestData.count(theKey) > 0) {
                if(theTestData[theKey]!=theValue)
                  return false;
              }
            }

          }
        } //while
        return true;
      }
      return false;
    }

    //--------------------------------------------------------
    
    //read json doc from stream, and
    //write all the key value pairs to output stream;
    //confirm key/value pairs
    bool doReadTest() {
      std::stringstream theOutput;
      if(generateTestFile(theOutput)) {
        std::string theStr=theOutput.str();
        //std::cout << theStr << "\n";
        std::stringstream theInput(theStr);
        JSONModel theModel;
        JSONReader theReader(theModel, theInput);
        if(theReader.tokenize()) {
          std::stringstream theDumpStream;
          theModel.debugDump(theDumpStream);
          std::cout << "dump " << theDumpStream.str() << "\n";
          return validateReaderDump(theDumpStream.str());
        }        
      }
      std::cout << "can't make JSON test file\n";
      return false;
    }

    //---------------------------
   
    bool doRoundTripTest() {
      bool theResult=false;
      std::stringstream theDocStream;
      
      TestDocument theDocument;
      if(theDocument.toJSON(theDocStream)) {
        std::string theDocJSON=theDocStream.str();
        if(theDocJSON.size()>kMinDumpSize) {
          std::stringstream theInput(theDocJSON);
          JSONModel theModel;
          JSONReader theReader(theModel, theInput);
          if(theReader.tokenize()) {
            std::stringstream theDump;
            theModel.debugDump(theDump);
            if(theDump.str().size()>kMinDumpSize) {
              if(TestDocument *theClone=Builder::create(theModel)) {
                std::stringstream theCloneStream;
                if(theClone->toJSON(theCloneStream)) {
                  std::string theCloneJSON=theCloneStream.str();
                  if(theDocJSON.size()==theCloneJSON.size()) {
                    theResult=crc32(theDocJSON)==crc32(theCloneJSON);
                  }
                }
                delete theClone;
              }
            }
          }
        }
      }
      return theResult;
    }
        
  };

}

#endif /* Testing_h */
