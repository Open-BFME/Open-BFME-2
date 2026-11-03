// Target facts (BFME2 1.06; code addresses are RVAs): constructor 0x003A57C5 stores table VA 0x00C1B590 at +0, calls RvaSmartPtr12's copy constructor 0x0004CC19 on +4, and stores its int argument at +0x10. Destructor 0x003A57E7 restores the same table and conditionally unlinks the +4 handle through 0x0004CBC0. No parent constructor or parent table is present.
// Table RVA 0x0081B590 has two slots: deleting destructor 0x003A57FB and __purecall 0x0003B810. The next table at 0x0081B598 belongs to the +0x1C subobject constructed by 0x003A5856 (store at 0x003A5884). The extra clone and transfer slots of derived tables are not slots of this base; slot01's original name is unknown.
// The handle occupies 12 bytes (copy loops 0x0004CC82 and 0x0004CCCD); the int ends at +0x14, where constructor 0x003AA228 places its next base. sizeof is 0x14. Copy constructors 0x003AEEB3 and 0x003AF50D inline this head's copy: store its table, call 0x0004CC19 on +4, copy the int at +0x10, then construct the next base at +0x14. The member names below are neutral placeholders.

#pragma once

#ifndef __BFME2_DEFAULTMODULEHEADBASE_H_
#define __BFME2_DEFAULTMODULEHEADBASE_H_

#include "../Common/RvaSmartPtr12.h"

class DefaultModuleHeadBase
{
public:
    DefaultModuleHeadBase(const RvaSmartPtr12 &smart, int value);
    __forceinline DefaultModuleHeadBase(const DefaultModuleHeadBase &other)
        : field04(other.field04), field10(other.field10)
    {
    }
    virtual ~DefaultModuleHeadBase();
    virtual void slot01() = 0;

    RvaSmartPtr12 field04;
    int field10;
};

typedef char DefaultModuleHeadBaseSizeCheck[sizeof(DefaultModuleHeadBase) == 0x14 ? 1 : -1];

#endif
