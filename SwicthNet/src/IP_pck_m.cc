//
// Generated file, do not edit! Created by opp_msgc 4.1 from IP_pck.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "IP_pck_m.h"

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




Register_Class(IP_pck);

IP_pck::IP_pck(const char *name, int kind) : cPacket(name,kind)
{
    this->verHlengthTos_var = 0;
    this->length_var = 0;
    this->ident_var = 0;
    this->f_frOffset_var = 0;
    this->ttl_var = 0;
    this->protocol_var = 0;
    this->checkSum_var = 0;
    for (unsigned int i=0; i<4; i++)
        this->destIp_var[i] = 0;
    for (unsigned int i=0; i<4; i++)
        this->srcIp_var[i] = 0;
}

IP_pck::IP_pck(const IP_pck& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

IP_pck::~IP_pck()
{
}

IP_pck& IP_pck::operator=(const IP_pck& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->verHlengthTos_var = other.verHlengthTos_var;
    this->length_var = other.length_var;
    this->ident_var = other.ident_var;
    this->f_frOffset_var = other.f_frOffset_var;
    this->ttl_var = other.ttl_var;
    this->protocol_var = other.protocol_var;
    this->checkSum_var = other.checkSum_var;
    for (unsigned int i=0; i<4; i++)
        this->destIp_var[i] = other.destIp_var[i];
    for (unsigned int i=0; i<4; i++)
        this->srcIp_var[i] = other.srcIp_var[i];
    return *this;
}

void IP_pck::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->verHlengthTos_var);
    doPacking(b,this->length_var);
    doPacking(b,this->ident_var);
    doPacking(b,this->f_frOffset_var);
    doPacking(b,this->ttl_var);
    doPacking(b,this->protocol_var);
    doPacking(b,this->checkSum_var);
    doPacking(b,this->destIp_var,4);
    doPacking(b,this->srcIp_var,4);
}

void IP_pck::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->verHlengthTos_var);
    doUnpacking(b,this->length_var);
    doUnpacking(b,this->ident_var);
    doUnpacking(b,this->f_frOffset_var);
    doUnpacking(b,this->ttl_var);
    doUnpacking(b,this->protocol_var);
    doUnpacking(b,this->checkSum_var);
    doUnpacking(b,this->destIp_var,4);
    doUnpacking(b,this->srcIp_var,4);
}

unsigned short IP_pck::getVerHlengthTos() const
{
    return verHlengthTos_var;
}

void IP_pck::setVerHlengthTos(unsigned short verHlengthTos_var)
{
    this->verHlengthTos_var = verHlengthTos_var;
}

unsigned short IP_pck::getLength() const
{
    return length_var;
}

void IP_pck::setLength(unsigned short length_var)
{
    this->length_var = length_var;
}

unsigned short IP_pck::getIdent() const
{
    return ident_var;
}

void IP_pck::setIdent(unsigned short ident_var)
{
    this->ident_var = ident_var;
}

unsigned short IP_pck::getF_frOffset() const
{
    return f_frOffset_var;
}

void IP_pck::setF_frOffset(unsigned short f_frOffset_var)
{
    this->f_frOffset_var = f_frOffset_var;
}

unsigned char IP_pck::getTtl() const
{
    return ttl_var;
}

void IP_pck::setTtl(unsigned char ttl_var)
{
    this->ttl_var = ttl_var;
}

unsigned char IP_pck::getProtocol() const
{
    return protocol_var;
}

void IP_pck::setProtocol(unsigned char protocol_var)
{
    this->protocol_var = protocol_var;
}

unsigned short IP_pck::getCheckSum() const
{
    return checkSum_var;
}

void IP_pck::setCheckSum(unsigned short checkSum_var)
{
    this->checkSum_var = checkSum_var;
}

unsigned int IP_pck::getDestIpArraySize() const
{
    return 4;
}

unsigned char IP_pck::getDestIp(unsigned int k) const
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    return destIp_var[k];
}

void IP_pck::setDestIp(unsigned int k, unsigned char destIp_var)
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    this->destIp_var[k] = destIp_var;
}

unsigned int IP_pck::getSrcIpArraySize() const
{
    return 4;
}

unsigned char IP_pck::getSrcIp(unsigned int k) const
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    return srcIp_var[k];
}

void IP_pck::setSrcIp(unsigned int k, unsigned char srcIp_var)
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    this->srcIp_var[k] = srcIp_var;
}

class IP_pckDescriptor : public cClassDescriptor
{
  public:
    IP_pckDescriptor();
    virtual ~IP_pckDescriptor();

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

Register_ClassDescriptor(IP_pckDescriptor);

IP_pckDescriptor::IP_pckDescriptor() : cClassDescriptor("IP_pck", "cPacket")
{
}

IP_pckDescriptor::~IP_pckDescriptor()
{
}

bool IP_pckDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IP_pck *>(obj)!=NULL;
}

const char *IP_pckDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IP_pckDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int IP_pckDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *IP_pckDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "verHlengthTos",
        "length",
        "ident",
        "f_frOffset",
        "ttl",
        "protocol",
        "checkSum",
        "destIp",
        "srcIp",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int IP_pckDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "verHlengthTos")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "ident")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "f_frOffset")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "protocol")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "checkSum")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destIp")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcIp")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IP_pckDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
        "unsigned short",
        "unsigned short",
        "unsigned char",
        "unsigned char",
        "unsigned short",
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *IP_pckDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int IP_pckDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IP_pck *pp = (IP_pck *)object; (void)pp;
    switch (field) {
        case 7: return 4;
        case 8: return 4;
        default: return 0;
    }
}

std::string IP_pckDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IP_pck *pp = (IP_pck *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getVerHlengthTos());
        case 1: return ulong2string(pp->getLength());
        case 2: return ulong2string(pp->getIdent());
        case 3: return ulong2string(pp->getF_frOffset());
        case 4: return ulong2string(pp->getTtl());
        case 5: return ulong2string(pp->getProtocol());
        case 6: return ulong2string(pp->getCheckSum());
        case 7: return ulong2string(pp->getDestIp(i));
        case 8: return ulong2string(pp->getSrcIp(i));
        default: return "";
    }
}

bool IP_pckDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IP_pck *pp = (IP_pck *)object; (void)pp;
    switch (field) {
        case 0: pp->setVerHlengthTos(string2ulong(value)); return true;
        case 1: pp->setLength(string2ulong(value)); return true;
        case 2: pp->setIdent(string2ulong(value)); return true;
        case 3: pp->setF_frOffset(string2ulong(value)); return true;
        case 4: pp->setTtl(string2ulong(value)); return true;
        case 5: pp->setProtocol(string2ulong(value)); return true;
        case 6: pp->setCheckSum(string2ulong(value)); return true;
        case 7: pp->setDestIp(i,string2ulong(value)); return true;
        case 8: pp->setSrcIp(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *IP_pckDescriptor::getFieldStructName(void *object, int field) const
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
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<9) ? fieldStructNames[field] : NULL;
}

void *IP_pckDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IP_pck *pp = (IP_pck *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


