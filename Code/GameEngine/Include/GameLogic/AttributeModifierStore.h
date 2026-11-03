// Target facts: GameEngine::init pushes sizeof 0x24 at RVA 0x0022F486, calls ctor 0x0022CA95 at 0x0022F49B, then registers its result with "TheAttributeModifierStore" (VA 0x00BE7BEC) and singleton VA 0x00DFE1D4 at 0x0022F4C5. The parser 0x00214C4E and caller 0x00403E72 use that singleton. The ctor calls SubsystemInterface's ctor 0x001B4E63, installs VA 0x00BE5348 at +0 (0x0022CAA8), and constructs three-word vector headers at +0x0C/+0x18 through 0x00211E58. Dtor 0x002149AA restores the same table at 0x002149BD, deletes four-byte pointer entries from both vectors, frees their buffers and calls the parent dtor at 0x00214A5A. Parent ctor/dtor 0x001B4E63/0x001B4E74 install VA 0x00BD77A0, clear byte +4 and own AsciiString +8; that table belongs to the parent. The ctor/dtor rows currently use Rva0022CA95; this object has virtual functions.
// Target facts: VA 0x00BE5348 contains fourteen code pointers (target RVAs): 0=00214A6E (deleting dtor calling 002149AA), 1=00214AC7, 2=001B5384, 3=000B3FD0, 4=0021494B, 5=002146E1, 6=000D43D0, 7=0047A69C, 8/9/10/12=000B3FD0, 11=005CB9FF, 13=0047A69C. The following word at VA 0x00BE5380 is not a code pointer. Slot 4 references the AttributeModifier reload string at VA 0x00BE52A8. Slots 2/3/6/7/8/11/12/13 equal the parent table VA 0x00BD77A0 and stay inherited; slots 0/1/4/5/9/10 are overrides. Lookup 0x00214713 and query 0x00214762 read begin/end +0x0C/+0x10; replacement 0x00214BB0 appends the old record to +0x18. The six neutral address words preserve these two vector representations without claiming their element type or original member names.
// Ledger method declarations: rva00214713 0x00214713, getDuration 0x00214738, getModifier 0x00214762, getFX 0x002147A1, getEndFX 0x002147D1, rva00214801 0x00214801, rva00214862 0x00214862, getDelayedUpgrade 0x002148C3, GetCategoryContainer 0x00214983, rva002149A5 0x002149A5, replaceModifier 0x00214BB0 and parseModifierListDefinition 0x00214C4E. All methods and the virtual destructor are declared out of line.
#pragma once

#ifndef BFME2_ATTRIBUTEMODIFIERSTORE_H
#define BFME2_ATTRIBUTEMODIFIERSTORE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class INI;
class Object;
class Rva0040450E;

class AttributeModifierStore : public SubsystemInterface
{
public:
    AttributeModifierStore();
    virtual void init();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    virtual void update();

    int rva00214713(int key);
    void *getDuration(int index);
    bool getModifier(int index, void *key, float *value, const StringBase<char> *name);
    void *getFX(int index, Object *object);
    void *getEndFX(int index, Object *object);
    void *rva00214801(void *out, int index);
    void *rva00214862(void *out, int index);
    void *getDelayedUpgrade(int index);
    void *GetCategoryContainer(int index);
    void *rva002149A5(int index);
    Rva0040450E *replaceModifier(int index);
    static void parseModifierListDefinition(INI *ini);

protected:
    virtual ~AttributeModifierStore();

private:
    int m_0C;
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    int m_20;
};

typedef char AttributeModifierStoreSizeIs0x24[(sizeof(AttributeModifierStore) == 0x24) ? 1 : -1];

#endif
