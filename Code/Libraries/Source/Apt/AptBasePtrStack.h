// Target facts (BFME2 1.06, RVAs): AptBasePtrStack has no virtual functions or bases. At 0x006FE580 reads the signed count at +0 and the pointer array at +8; Push 0x006FE6E0 compares count with signed capacity at +4, stores four-byte pointers and increments +0. Interpreter construction 0x006FE980 zeroes +0/+4/+8 and starts the next stack at +0xC, establishing sizeof 0xC without a vptr.
// Target facts: destructor 0x006FDD40 tests +0/+8, frees +8 with capacity*4 through 0x006DB270 and never stores a vtable; interpreter destruction calls it directly at 0x006FEAD5. Assertions in 0x006FDD40, 0x006FDDB0 and 0x006FE6E0 name m_nElements, m_nCapacity and m_aElements; 0x006FE0B0 uses the same offsets with the value-stack assertion spelling m_nSize. The virtual calls in Push dispatch on the stored value, not this stack.
// Target facts: ledger methods are At 0x006FE580, Push 0x006FE6E0, PopNoDec 0x006FDF70, PopAndPush 0x006FDFA0 and neutral methods 0x006E3AA0, 0x006FDDB0, 0x006FDE50, 0x006FDEE0, 0x006FDF30, 0x006FE050, 0x006FE0B0, 0x006FE120, 0x006FE5D0, 0x006FE7B0, 0x006FE880, 0x006FE920, 0x00700170 and 0x007062F0. Their declarations retain the ledger's BfmeAptValue006DCD20 pointer spelling and out-of-line bodies.
#pragma once

#ifndef BFME2_APT_BASE_PTR_STACK_H
#define BFME2_APT_BASE_PTR_STACK_H

class BfmeAptValue006DCD20;

class AptBasePtrStack
{
public:
    ~AptBasePtrStack();

    BfmeAptValue006DCD20 *At(int nPos);
    void Push(BfmeAptValue006DCD20 *pValue);
    void PopNoDec();
    void PopAndPush(int nItems, BfmeAptValue006DCD20 *pValue);
    void rva006E3AA0(int nItems);
    void rva006FDDB0(int nCapacity);
    void rva006FDE50();
    void rva006FDEE0(BfmeAptValue006DCD20 *pValue);
    void rva006FDF30(BfmeAptValue006DCD20 *pValue);
    void rva006FE050(int nItems);
    void rva006FE0B0(int nSize);
    void rva006FE120();
    BfmeAptValue006DCD20 *rva006FE5D0();
    void rva006FE7B0(BfmeAptValue006DCD20 *pValue);
    void rva006FE880(int nItems, BfmeAptValue006DCD20 *pValue);
    void rva006FE920();
    void rva00700170(void *first, void *second);
    BfmeAptValue006DCD20 *rva007062F0();

    int m_nElements;
    int m_nCapacity;
    BfmeAptValue006DCD20 **m_aElements;
};

#endif
