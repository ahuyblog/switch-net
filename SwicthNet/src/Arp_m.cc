//
// Generated file, do not edit! Created by opp_msgc 4.1 from Arp.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Arp_m.h"

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




Register_Class(Arp);

Arp::Arp(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
    for (unsigned int i=0; i<4; i++)
        this->ip_var[i] = 0;
    for (unsigned int i=0; i<6; i++)
        this->mac_var[i] = 0;
}

Arp::Arp(const Arp& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

Arp::~Arp()
{
}

Arp& Arp::operator=(const Arp& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->type_var = other.type_var;
    for (unsigned int i=0; i<4; i++)
        this->ip_var[i] = other.ip_var[i];
    for (unsigned int i=0; i<6; i++)
        this->mac_var[i] = other.mac_var[i];
    return *this;
}

void Arp::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->ip_var,4);
    doPacking(b,this->mac_var,6);
}

void Arp::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->ip_var,4);
    doUnpacking(b,this->mac_var,6);
}

unsigned short Arp::getType() const
{
    return type_var;
}

void Arp::setType(unsigned short type_var)
{
    this->type_var = type_var;
}

unsigned int Arp::getIpArraySize() const
{
    return 4;
}

unsigned char Arp::getIp(unsigned int k) const
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    return ip_var[k];
}

void Arp::setIp(unsigned int k, unsigned char ip_var)
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    this->ip_var[k] = ip_var;
}

unsigned int Arp::getMacArraySize() const
{
    return 6;
}

unsigned char Arp::getMac(unsigned int k) const
{
    if (k>=6) throw cRuntimeError("Array of size 6 indexed by %lu", (unsigned long)k);
    return mac_var[k];
}

void Arp::setMac(unsigned int k, unsigned char mac_var)
{
    if (k>=6) throw cRuntimeError("Array of size 6 indexed by %lu", (unsigned long)k);
    this->mac_var[k] = mac_var;
}

class ArpDescriptor : public cClassDescriptor
{
  public:
    ArpDescriptor();
    virtual ~ArpDescriptor();

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

Register_ClassDescriptor(ArpDescriptor);

ArpDescriptor::ArpDescriptor() : cClassDescriptor("Arp", "cPacket")
{
}

ArpDescriptor::~ArpDescriptor()
{
}

bool ArpDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Arp *>(obj)!=NULL;
}

const char *ArpDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ArpDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ArpDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ArpDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "ip",
        "mac",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ArpDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "ip")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mac")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ArpDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ArpDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int ArpDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Arp *pp = (Arp *)object; (void)pp;
    switch (field) {
        case 1: return 4;
        case 2: return 6;
        default: return 0;
    }
}

std::string ArpDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Arp *pp = (Arp *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getType());
        case 1: return ulong2string(pp->getIp(i));
        case 2: return ulong2string(pp->getMac(i));
        default: return "";
    }
}

bool ArpDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Arp *pp = (Arp *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2ulong(value)); return true;
        case 1: pp->setIp(i,string2ulong(value)); return true;
        case 2: pp->setMac(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *ArpDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *ArpDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Arp *pp = (Arp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


