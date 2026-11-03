// Target facts: this is a nonvirtual allocator view. Retail 0x00033B90 writes a byte at +0; 0x006C4A50 calls it at 0x006C4A8E and installs no vtable, and the nonvirtual destructor 0x006C3CC0 calls 0x00034D00 on the same receiver at 0x006C3D08. There are no virtual slots or constructor/destructor vtables to reconcile.
// Retail 0x006C4A50 initializes +0x510..+0x560, the 64-bit sequence at +0x568 (returned by 0x006C1B50), clears 0x100 bytes at +0x570 (0x006C4BD4..0x006C4BE8), and initializes +0x678/+0x67C/+0x680 and the 0x20-byte table at +0x684 through +0x6A0. The initialized extent is 0x6A4; MSVC's 8-byte sequence alignment makes this declaration 0x6A8. No retail allocation site for 0x006C4A50 is known. The registered GeneralAllocator base occupies 0x510 and owns the +0x4E4 lock.
// Retail 0x006C1EB0/0x006C1F60 prove the +0x514 flag, +0x534 float and +0x538/+0x53C unsigned bounds; 0x006C3840 proves +0x540/+0x544; 0x006C38D0 proves +0x510 and self +0x678. Method declarations retain ledger rows 0x00033ED0, 0x006C1AA0, 0x006C1CC0, 0x006C1DC0, 0x006C1E20, 0x006C1EB0, 0x006C1F60, 0x006C33D0, 0x006C3660, 0x006C37E0, 0x006C3810, 0x006C3840, 0x006C38D0, 0x006C39E0 and 0x006C3CC0, plus the existing 0x00033D50 pin. The destructor calls table +0x684 through 0x006C17B0 and base +0 through 0x00034D00; table storage below does not supply its member destructor. Constructor identity under this address-derived name is unproved.
#pragma once
#ifndef __BFME2_RVA006C1F60_H_
#define __BFME2_RVA006C1F60_H_

#include "GeneralAllocator.h"

struct Slot64;

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
    ~Rva006C1F60();
    void *rva00033ED0(unsigned int size, int flags);
    bool rva00033D50();
    Slot64 *rva006C1AA0(unsigned int index);
    void *rva006C1CC0(unsigned int size, int flags);
    int rva006C1DC0(unsigned int block);
    bool rva006C1E20(const void *block, int addressType);
    void rva006C1EB0(float scale, unsigned int mn, unsigned int mx);
    int rva006C1F60(unsigned int value);
    void rva006C33D0(int policy, int limit);
    void rva006C3660(void *block);
    void TraceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes);
    void *TakeSnapshot(int blockTypes, bool copy, void *storage, unsigned int storageSize);
    void rva006C3840(int first, int second);
    bool rva006C38D0();
    void rva006C39E0();

    unsigned char m_510;
    unsigned char m_pad511[3];
    int m_514;
    unsigned int m_518;
    unsigned int m_51C;
    unsigned int m_520;
    unsigned int m_524;
    unsigned int m_528;
    unsigned int m_52C;
    int m_530;
    float m_534;
    unsigned int m_538;
    unsigned int m_53C;
    int m_540;
    int m_544;
    unsigned int m_548;
    unsigned int m_54C;
    void *m_550;
    void *m_554;
    unsigned int m_558;
    unsigned int m_55C;
    bool m_560;
    unsigned char m_pad561[7];
    unsigned __int64 m_568;
    unsigned int m_570[64];
    unsigned int m_670;
    unsigned int m_674;
    Rva006C1F60 *m_678;
    unsigned int m_67C;
    bool m_680;
    unsigned char m_pad681[3];
    unsigned char m_684[0x20];
};

#endif
