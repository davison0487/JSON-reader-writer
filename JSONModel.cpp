//
//  JSONModel.cpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#include "JSONModel.hpp"

namespace ECE141 {
    //-----JSONStrConst-----//
    
    void JSONStrConst::debugDump(std::ostream& anOutput, int anIndent) {
        anOutput << value << std::endl;
    }
    
    std::string JSONStrConst::getValue() {
        return value;
    }

    //-----JSONStrConst-----//
    
    //-----JSONElement-----//
    
    JSONElement::~JSONElement() {
        delete value;
    }
    
    void JSONElement::debugDump(std::ostream& anOutput, int indent) {
        for (int i = 0; i < indent; ++i)
            anOutput << " ";
        anOutput << key << "=";

        if (value->type == JSONType::constant)
            value->debugDump(anOutput);
        else {
            for (int i = 0; i < indent; ++i)
                anOutput << " ";
            anOutput << "\n";
            value->debugDump(anOutput, indent + 4);
        }
    }

    void JSONElement::addElement(JSONPart* const aPart) {
        value = aPart;
    }

    JSONList* JSONElement::getList() {
        if (value->type != JSONType::list) {
            return nullptr;
        }
        return dynamic_cast<JSONList*>(value);
    }

    JSONObject* JSONElement::getObject() {
        if (value->type != JSONType::object) {
            return nullptr;
        }
        return dynamic_cast<JSONObject*>(value);
    }

    JSONStrConst* JSONElement::getConst() {
        if (value->type != JSONType::constant) {
            return nullptr;
        }
        return dynamic_cast<JSONStrConst*>(value);
    }
    
    //-----JSONElement-----//
    
    //-----JSONList-----//
    
    JSONList::~JSONList() {
        for (auto cur : elementList)
            delete cur;
    }
    
    void JSONList::debugDump(std::ostream& anOutput, int indent) {
        for (int i = 0; i < indent; ++i)
            anOutput << " ";
        anOutput << "(list):\n";
        
        for (int i = 0; i < elementList.size(); ++i)
            elementList[i]->debugDump(anOutput, indent + 4);
    }

    void JSONList::addElement(JSONPart* const aPart) {
        elementList.push_back(aPart);
    }

    std::vector<JSONStrConst*> JSONList::getStrConst() {
        if (elementList[0]->type != JSONType::constant) {
            return {};
        }
        std::vector<JSONStrConst*> newConstList;
        for (auto element : elementList) {
            newConstList.push_back(dynamic_cast<JSONStrConst*>(element));
        }
        return newConstList;
    };
    
    //-----JSONList-----//
    
    //-----JSONObject-----//
    
    JSONObject::~JSONObject() {
        for (auto cur : elementList)
            delete cur;
    }
    
    void JSONObject::debugDump(std::ostream& anOutput, int indent) {
        for (int i = 0; i < indent; ++i)
            anOutput << " ";
        anOutput << "(object):\n";
        
        for (int i = 0; i < elementList.size(); ++i)
            elementList[i]->debugDump(anOutput, indent + 4);
    }

    void JSONObject::addElement(JSONPart* const aPart) {
        elementList.push_back(aPart);
    }

    std::vector<JSONElement*> JSONObject::getElement() {
        std::vector<JSONElement*> newElementList;
        for (auto element : elementList) {
            newElementList.push_back(dynamic_cast<JSONElement*>(element));
        }
        return newElementList;
    }

    //-----JSONObject-----//
    
    //-----JSONModel-----//
    
    JSONModel::~JSONModel() {
        delete baseObject;
    }
    
    void JSONModel::debugDump(std::ostream& anOutput, int indent) {
        baseObject->debugDump(anOutput, 0);
    }
    
    void JSONModel::setBase(JSONPart* const aPart) {
        baseObject = aPart;
    }
    
    //-----JSONModel-----//

}
