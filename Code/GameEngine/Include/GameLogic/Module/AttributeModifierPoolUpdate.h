/* Target facts (code addresses are RVAs; table addresses are VAs): 0x00403BEF calls UpdateModule's constructor at 0x00253390, then stores 0x00C3856C at +0, 0x00BEFF90 at +0x0C and 0x00C38560 at +0x10. The factory at 0x0024C6B1 allocates 0xA8 bytes. UpdateModule occupies +0..+0x1F. The vector constructor at 0x00211E58 initializes the first two pointer words directly and the third through 0x0014F3C4; the header exposes its two-word EraseRange access view at +0x20 and its capacity word separately at +0x28. The destructor at 0x00403A12 restores the same three tables, destroys the vector at +0x20 through 0x00403960 and calls ~UpdateModule at 0x0024A797. That base destructor restores BehaviorModule's 0x00BEEA7C and 0x00BEE9C0 during base teardown; they are not this class's tables.
   The primary table has 13 slots: deleting destructor 0x00403C8C, loadPostProcess 0x00497805, name getter 0x00403A5B, xfer 0x0040426D, getModuleNameKey 0x00403A61, four empty inherited slots 0x000B3FD0, onCapture 0x0050B238, two inherited null getters 0x000D43D0 and getUpdatePhase 0x0022C4CB. The +0x10 table has update 0x00403CA8, disabled-mask getter 0x003908A7 and wake helper 0x0044DF8D. The +0x0C table is UpdateModule's unchanged 47-slot interface table, whose slot 9 is 0x002533D3. The constructor builds three vector words at +0x20 through 0x00211E58 and calls EraseRange at 0x002983DA; that ledger spelling supplies the vector access view below. It writes 0x3FFFFFFF at +0x2C and initializes 15 four-byte entries at +0x30 and 15 counters at +0x6C. The +0x30 iterator calls the folded zero-word constructor 0x00326BE6; 0x004031DD compares these words with GameLogic's frame, and 0x00403415 writes frame values to them. No string teardown runs for that array. 0x004031C9 reads the +0x6C array. Other out-of-line methods are rowed at 0x00403170, 0x00403382, 0x00403448, 0x00403744 and 0x00403E72. Member spellings without established source names remain offset placeholders. */

#pragma once

#ifndef __BFME2_ATTRIBUTEMODIFIERPOOLUPDATE_H_
#define __BFME2_ATTRIBUTEMODIFIERPOOLUPDATE_H_

#include "UpdateModule.h"

class AsciiString;
class Rva00297360Element;

class Rva002983DAVector
{
public:
    Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);

    Rva00297360Element *m_field00;
    Rva00297360Element *m_field04;
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
    AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~AttributeModifierPoolUpdate();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;

    const char *name() const;
    int rva004031C9(int index);
    unsigned char isCategoryDisabled(int index);
    bool rva00403170(unsigned int frame, const void *entry, int includeCategories);
    bool rva00403382(int attribute, float *bonus, int name);
    void rva00403415(int *mask, int value);
    bool rva00403448(int attribute, float *multiplier, int name, int includeCategories);
    void rva00403744(const AsciiString &name);
    bool addModifierToPool(const AsciiString &name, int duration);

    Rva002983DAVector m_field20;
    Rva00297360Element *m_field28;
    unsigned int m_field2C;
    unsigned int m_field30[15];
    unsigned int m_field6C[15];

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
};

typedef char AttributeModifierPoolUpdateSize[(sizeof(AttributeModifierPoolUpdate) == 0xA8) ? 1 : -1];

#endif
