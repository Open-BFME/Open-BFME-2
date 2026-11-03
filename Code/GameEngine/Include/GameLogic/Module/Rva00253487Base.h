// Target facts (code addresses are RVAs, tables are VAs): constructor 0x00253487 stores 0x00BF2558 at +0 and calls Rva0025342CMember::construct (0x0025342C) at +8. Factory 0x00254DB3 allocates 0x118 bytes at 0x00254DB4 and calls that constructor at 0x00254DC5. The eight-byte ModuleData primary base has its tag stored at +4 by 0x00257237; factory 0x0024CCF4 allocates eight bytes at 0x0024CD00. The member occupies +8..+0x117.
// Table 0x00BF2558 has 31 slots and a zero word at 0x00BF25D4. It agrees with ModuleData's 0x00C4ED70 except slot 10, which uses 0x0050B5C6 (true) instead of 0x0047A699 (false). Slot 0 calls destructor 0x0049B47C through 0x004A10FD. That destructor stores Snapshot's 0x00BBB554, also stored by Snapshot constructor 0x000053A6; CommandSet cleanup 0x00771D21 jumps to it and complete destructor 0x002561EF restores it at 0x00256212. It is the teardown table, not this class's live table.
// Member routine 0x0025342C calls Rva001EAE6FHelper::clear80 (0x001EAE6F, memset of 0x80 bytes) at relative +0 and +0x80, writes dwords -1/0/0 at +0x100/+0x104/+0x108 and zero bytes at +0x10C/+0x10D/+0x10E, and returns this. Its four-byte alignment gives size 0x110. The ledger names construct, clear80, the base constructor and its virtual destructor; all remain declared out of line. Other member names and slot10 are neutral.
#pragma once

#ifndef BFME2_RVA00253487BASE_H
#define BFME2_RVA00253487BASE_H

#include "../../Common/ModuleData.h"
#include "Rva0025342CMember.h"

class Rva00253487Base : public ModuleData
{
public:
    Rva00253487Base();
    virtual ~Rva00253487Base();
    virtual bool slot10() const { return true; }

private:
    Rva0025342CMember m_member08;
};

#endif
