// Target facts (BFME2 1.06; code addresses are RVAs, tables are VAs): 0x00493009 is primary slot 3 of SpecialPowerModule's 0x00C4E868 table. Constructor 0x00493C5A calls BehaviorModule 0x00253330 at 0x00493C74, installs the interface's pure table 0x00C4E2B0 at +0x10 (0x00493C81), then installs 0x00C4E868/+0, 0x00BEFCF8/+0x0C and 0x00C5E080/+0x10 at 0x00493C8F/95/9C. Destructor 0x00493DEF restores these same three tables at 0x00493E06/0C/13 before restoring BehaviorModule's 0x00BEEA7C/+0 and 0x00BEE9C0/+0x0C at 0x00493E87/8D; these are successive base-lifetime tables, not competing layouts.
// The primary table has 14 slots: 0 is deleting destructor 0x004941D7 (calls 0x00493DEF); 1/2/3/4 are 0x00493B1E/0x00493DA4/0x00493009/0x00493DAA; 5..11 retain BehaviorModule's slots; 12/13 are 0x00493805/0x00493EA7. Slot 2 returns "SpecialPowerModule" at 0x00BF47D4. The +0x0C table has BehaviorModuleInterface's 47 slots with slot 8 returning the +0x10 interface; that interface has 25 slots and no virtual destructor (0x00492FB9 stores its pure table). Both bases use their registered headers. Rva00493009 is the ledger's xfer-owner spelling; the registered SpecialPowerModule.h defines only SpecialPowerModuleInterface. Zero Hour Common/BitFlags.h uses a size_t template parameter under __BitFlags_H_; an existing full declaration supplies that type, while the registered BFME2 headers use the int forward declaration below.
// Allocation 0x0024DC5F requests 0x34 bytes and calls 0x00493C5A at 0x0024DC7B. Stores 0x00493CA2..0x00493CB9 initialize words +0x14/18/1C/20/2C, float +0x24 and bools +0x28/30; xfer 0x00493037/42/4D/58/63/6E/7A/8E proves their offsets and types (ObjectID via 0x003060B2). The xfer's base call is 0x004C9C7D at 0x0049302A; derived xfer 0x004C447D calls it at 0x004C449E and transfers its own byte at +0x34. No Rva00493009 constructor, copy or assignment row exists; all declared methods remain out of line.

#pragma once

#ifndef __BFME2_RVA00493009_H_
#define __BFME2_RVA00493009_H_

#include "Module/BehaviorModule.h"
#include "Module/SpecialPowerModule.h"

enum ObjectID;
#ifndef __BitFlags_H_
template <int N> class BitFlags;
#endif

class Rva00493009 : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
    virtual ~Rva00493009();
    virtual SpecialPowerModuleInterface *getSpecialPower();
    virtual void vslot12();
    virtual void vslot13(Object *object, int frame, const BitFlags<11> *flags);

protected:
    virtual void xfer(Xfer *xfer);

public:
    unsigned int m_14;
    unsigned int m_18;
    int m_1c;
    unsigned int m_20;
    float m_24;
    bool m_28;
    ObjectID m_2c;
    bool m_30;
};

#endif
