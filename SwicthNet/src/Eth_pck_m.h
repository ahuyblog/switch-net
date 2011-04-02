//
// Generated file, do not edit! Created by opp_msgc 4.1 from Eth_pck.msg.
//

#ifndef _ETH_PCK_M_H_
#define _ETH_PCK_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Eth_pck.msg</tt> by opp_msgc.
 * <pre>
 * packet Eth_pck {
 * 
 * 
 * 
 * 
 * 
 *     
 *     unsigned char preamble[8];
 *     unsigned char macDest[6];
 *     unsigned char macSrc[6];
 *     unsigned short length;
 *     unsigned long fcs;
 * }
 * </pre>
 */
class Eth_pck : public ::cPacket
{
  protected:
    unsigned char preamble_var[8];
    unsigned char macDest_var[6];
    unsigned char macSrc_var[6];
    unsigned short length_var;
    unsigned long fcs_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Eth_pck&);

  public:
    Eth_pck(const char *name=NULL, int kind=0);
    Eth_pck(const Eth_pck& other);
    virtual ~Eth_pck();
    Eth_pck& operator=(const Eth_pck& other);
    virtual Eth_pck *dup() const {return new Eth_pck(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getPreambleArraySize() const;
    virtual unsigned char getPreamble(unsigned int k) const;
    virtual void setPreamble(unsigned int k, unsigned char preamble_var);
    virtual unsigned int getMacDestArraySize() const;
    virtual unsigned char getMacDest(unsigned int k) const;
    virtual void setMacDest(unsigned int k, unsigned char macDest_var);
    virtual unsigned int getMacSrcArraySize() const;
    virtual unsigned char getMacSrc(unsigned int k) const;
    virtual void setMacSrc(unsigned int k, unsigned char macSrc_var);
    virtual unsigned short getLength() const;
    virtual void setLength(unsigned short length_var);
    virtual unsigned long getFcs() const;
    virtual void setFcs(unsigned long fcs_var);
};

inline void doPacking(cCommBuffer *b, Eth_pck& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Eth_pck& obj) {obj.parsimUnpack(b);}


#endif // _ETH_PCK_M_H_
