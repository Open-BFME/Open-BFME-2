// Target facts (BFME2 game.dat 1.06; addresses below are RVAs):
// 0x0004120E stores the mutex argument at +0 and zeroes byte +4, then calls
// 0x00041037(-1) when its second argument is zero. It stores no vptr or vbptr
// and calls no base constructor: MilesMutexGuard has no base or virtual methods.
// 0x00041037 reads the pointer at +0, calls its pointee's virtual slot 0 with
// an int, and stores AL at +4. 0x00041055 calls that pointee's slot 1 and stores
// its inverted byte result at +4. Those tables belong to the mutex, not the guard.
// Mutex table VA 0x00BC16C4 selects lock 0x00040EF8 and unlock 0x00040F4C;
// critical-section table VA 0x00BC16DC selects 0x00041004 and 0x00041024.
// Constructor 0x000411C1 installs 0x00BC16DC on that separate lock object.
// 0x0004122F tests byte +4 and tail-calls 0x00041055 when set; no vptr is restored.
// 0x000530DF reserves eight stack bytes for the guard at EBP-8 and calls
// 0x0004120E / 0x0004122F on that address. A 4-byte pointer and a byte flag,
// with 4-byte pointer alignment, give sizeof 8; +5 through +7 are tail padding.
// The ledger names these four public, nonvirtual, out-of-line methods; its
// constructor signature is (void *, int). m_mutex and m_held describe the
// observed pointer and acquisition state, without claiming historical spelling.

#pragma once

#ifndef BFME2_MILESMUTEXGUARD_H
#define BFME2_MILESMUTEXGUARD_H

class Rva00041037Mutex;

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
    bool rva00041037(int timeout);
    bool rva00041055();

private:
    Rva00041037Mutex *m_mutex;
    bool m_held;
};

#endif
