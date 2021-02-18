//
//  Document.hpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#ifndef TestDocument_h
#define TestDocument_h

#include <vector>

#include "TestClass1.hpp"
#include "TestClass2.hpp"
#include "TestClass3.hpp"

namespace ECE141 {
    
  class TestDocument : public Storable {
  public:

    TestDocument() :
        child1a("oneA",false,3.14,1234),
        child1b("oneB",true,6.28, 567),
        child2("two", 99, ECE141::Metadata{'A',42,true}),
        child3("three", Color::red, "RKG")
    {
        price=35.99;
    };
    
    ~TestDocument() {}

    virtual bool toJSON(std::ostream &aStream) {
        aStream << "{\n"
            //-----meta------//
            << "\"meta\" : {\n"
            << "\"class\" : \"TestDocument\",\n"
            << "\"version\" : 1.0\n"
            << "},\n"
            //-----meta-----//
            //-----members-----//
            << "\"members\" : {\n"
            << "\"child1a\" : ";
        child1a.toJSON(aStream);
        aStream << ",\n"
            << "\"child1b\" : ";
        child1b.toJSON(aStream);
        aStream << ",\n"
            << "\"child2\" : ";
        child2.toJSON(aStream);
        aStream << ",\n"
            << "\"child3\" : ";
        child3.toJSON(aStream);
        aStream << ",\n"
            << "\"price\" : " << price << std::endl
            << "}\n"
            //-----members-----//
            << "}\n";
        return true;
    }
    
  protected:
    TestClass1 child1a;
    TestClass1 child1b;
    TestClass2  child2;
    TestClass3  child3;
    float price;
  };

}

#endif /* TestDocument_h */
