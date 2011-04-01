//
// Generated file, do not edit! Created by opp_msgc 4.1 from Eth_pck.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Eth_pck_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Eth_pck);

Eth_pck::Eth_pck(const char *name, int kind) : cPacket(name,kind)
{
    this->preamble_var = 0;
    this->macDest_var = 0;
    this->macSrc_var = 0;
    this->length_var = 0;
    this->data_var = 0;
}

Eth_pck::Eth_pck(const Eth_pck& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

Eth_pck::~Eth_pck()
{
}

Eth_pck& Eth_pck::operator=(const Eth_pck& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->preamble_var = other.preamble_var;
    this->macDest_var = other.macDest_var;
    this->macSrc_var = other.macSrc_var;
    this->length_var = other.length_var;
    this->data_var = other.data_var;
    return *this;
}

void Eth_pck::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->preamble_var);
    doPacking(b,this->macDest_var);
    doPacking(b,this->macSrc_var);
    doPacking(b,this->length_var);
    doPacking(b,this->data_var);
}

void Eth_pck::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->preamble_var);
    doUnpacking(b,this->macDest_var);
    doUnpacking(b,this->macSrc_var);
    doUnpacking(b,this->length_var);
    doUnpacking(b,this->data_var);
}

const char * Eth_pck::getPreamble() const
{
    return preamble_var.c_str();
}

void Eth_pck::setPreamble(const char * preamble_var)
{
    this->preamble_var = preamble_var;
}

const char * Eth_pck::getMacDest() const
{
    return macDest_var.c_str();
}

void Eth_pck::setMacDest(const char * macDest_var)
{
    this->macDest_var = macDest_var;
}

const char * Eth_pck::getMacSrc() const
{
    return macSrc_var.c_str();
}

void Eth_pck::setMacSrc(const char * macSrc_var)
{
    this->macSrc_var = macSrc_var;
}

short Eth_pck::getLength() const
{
    return length_var;
}

void Eth_pck::setLength(short length_var)
{
    this->length_var = length_var;
}

const char * Eth_pck::getData() const
{
    return data_var.c_str();
}

void Eth_pck::setData(const char * data_var)
{
    this->data_var = data_var;
}

class Eth_pckDescriptor : public cClassDescriptor
{
  public:
    Eth_pckDescriptor();
    virtual ~Eth_pckDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Eth_pckDescriptor);

Eth_pckDescriptor::Eth_pckDescriptor() : cClassDescriptor("Eth_pck", "cPacket")
{
}

Eth_pckDescriptor::~Eth_pckDescriptor()
{
}

bool Eth_pckDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Eth_pck *>(obj)!=NULL;
}

const char *Eth_pckDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Eth_pckDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int Eth_pckDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *Eth_pckDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "preamble",
        "macDest",
        "macSrc",
        "length",
        "data",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int Eth_pckDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "preamble")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "macDest")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "macSrc")==0) return base+2;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Eth_pckDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "short",
        "string",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *Eth_pckDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Eth_pckDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Eth_pck *pp = (Eth_pck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Eth_pckDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Eth_pck *pp = (Eth_pck *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getPreamble());
        case 1: return oppstring2string(pp->getMacDest());
        case 2: return oppstring2string(pp->getMacSrc());
        case 3: return long2string(pp->getLength());
        case 4: return oppstring2string(pp->getData());
        default: return "";
    }
}

bool Eth_pckDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Eth_pck *pp = (Eth_pck *)object; (void)pp;
    switch (field) {
        case 0: pp->setPreamble((value)); return true;
        case 1: pp->setMacDest((value)); return true;
        case 2: pp->setMacSrc((value)); return true;
        case 3: pp->setLength(string2long(value)); return true;
        case 4: pp->setData((value)); return true;
        default: return false;
    }
}

const char *Eth_pckDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *Eth_pckDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Eth_pck *pp = (Eth_pck *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


