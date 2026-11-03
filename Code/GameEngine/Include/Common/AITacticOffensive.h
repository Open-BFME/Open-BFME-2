// Target facts (addresses are RVAs unless marked VA): 0x005DC722 calls AITactic's constructor 0x004ED3D1 with (name,true), then stores VA 0x00C767DC at +0. 0x005DC73C stores the same table and tail-calls 0x004EDCE9, whose VA 0x00C629E4 store is the parent teardown. Slot 0 at VA 0x00C767DC targets the deleting destructor 0x005DC747, which calls 0x005DC73C and conditionally operator delete 0x0002FD60. The constructor and virtual destructor are out of line.
// Target facts: VA 0x00C767DC contains eleven slots before AITacticSiege's VA 0x00C76808: 0x005DC747, purecall (0x0003B810), purecall, 0x004ECE61, 0x000910FB, 0x004EDA8C, purecall, purecall, 0x004EDDAA, purecall, 0x0047A699. Slots 1-8 preserve AITactic's table. AISimpleAttackTactic's VA 0x00C71F80 slot 9 targets its ledger-named create returning AITactic* (0x005AA703). Slot 10 is unnamed: 0x005DC805 calls it through +0x28 and consumes AL; 0x0047A699 is xor al,al; ret.
// Target facts: 0x005AA70E allocates 0x58 bytes for AISimpleAttackTactic; its constructor 0x005AA6B4 calls 0x005DC722 at 0x005AA6DD and adds only its table. AITactic's constructor initializes through dword +0x54; AITacticOffensive adds no storage. AITacticSiege's constructor 0x005DC85F calls 0x005DC722 then initializes its first added dword at +0x58. checkTarget (0x005DC763, unsigned char(void*)) reads the inherited owner at +0x24 (0x005DC773 and 0x005DC811). All data members belong to the registered AITactic base.

#pragma once

#ifndef __BFME2_AITACTICOFFENSIVE_H_
#define __BFME2_AITACTICOFFENSIVE_H_

#include "AITactic.h"

class AITacticOffensive : public AITactic
{
public:
    AITacticOffensive(const AsciiString &name);
    virtual ~AITacticOffensive();

    virtual AITactic *create() = 0;
    virtual bool slot10() { return false; }

    unsigned char checkTarget(void *target);
};

#endif
