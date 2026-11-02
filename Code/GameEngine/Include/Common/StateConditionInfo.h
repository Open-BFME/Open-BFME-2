// Target facts: State::rva004D7127 (RVA 0x004D7127) tests the first dword for a null sentinel and advances by 0x0C at 0x004D7139, proving a 12-byte record. State::friend_checkForTransitions pushes +8 and State*, calls the pointer at +0 (0x004D7192..0x004D719C), tests AL, and reads the destination dword at +4 (0x004D71AA); 0x004D7252..0x004D7266 independently repeats that cdecl callback ABI. The static records at VA 0x00C698F0 are {0x009430E7, 5005, 0} and {0, 0, 0}; AIGuardMachine's constructor passes that address at RVA 0x005431E7. StateConditionInfo has no virtual functions, vptr or base: +0 holds the callback itself, not a vtable. There are no rowed StateConditionInfo methods, constructors or destructors; the two ledger signatures at 0x004D7127 and 0x004D7B0F mangle it as a struct.
// Donor facts: Zero Hour GeneralsMD Common/StateMachine.h names the fields test, toStateID and userData and the callback Bool(State*, void*); its unsigned StateID agrees with the target's four-byte destination field. Retail's static records require aggregate initialization rather than Zero Hour's user-provided constructor.

#pragma once

#ifndef BFME2_STATECONDITIONINFO_H
#define BFME2_STATECONDITIONINFO_H

class State;

struct StateConditionInfo
{
    bool (*test)(State *state, void *userData);
    unsigned int toStateID;
    void *userData;
};

#endif
