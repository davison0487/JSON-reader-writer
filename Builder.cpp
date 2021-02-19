//
//  MetaFactory.cpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#include "Builder.hpp"

namespace ECE141 {

  TestDocument* Builder::create(JSONModel &aModel) {
      TestDocument* newTestDocument = new TestDocument();
      newTestDocument->buildClass(aModel.getBaseObject());
      return newTestDocument;
  }

}
