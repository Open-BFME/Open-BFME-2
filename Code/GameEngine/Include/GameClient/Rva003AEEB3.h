// Target facts (BFME2 1.06; code addresses are RVAs): copy constructor 0x003AEEB3 and constructor 0x0055BEE9 finish with primary table VA 0x00C1D5FC at +0 and table VA 0x00C1C780 at +0x14 and +0x18. The copy first stores the head table 0x00C1B590, copies the +4 handle through 0x0004CC19 and copies the +0x10 int; 0x0055BEF4 calls DefaultModuleHeadBase constructor 0x003A57C5. The handle belongs to that parent, rather than forming another base.
// Table 0x00C1D5FC has deleting destructor 0x003AEEFC followed by three __purecall entries (0x0003B810); the next primary table starts at 0x00C1D60C. The parent table 0x00C1B590 has two entries. Destructor 0x003A5817 restores 0x00C1C780 at +0x18 and +0x14, then jumps to parent destructor 0x003A57E7, which restores 0x00C1B590. These are destruction phases of the same object; its deleting destructor calls 0x003A5817 at 0x003AEEFF.
// The parent's extent is 0x14, and two four-byte secondary subobjects end at 0x1C; constructor 0x003A5856 calls this class at 0x003A5861 and constructs its next subobject at +0x1C (0x003A5866): sizeof 0x1C. Table 0x00C1C780 is one folded __purecall entry, followed by the independent table 0x00C1C784. Derived constructor 0x003AEDE9 stores secondary tables 0x00C1C61C at +0x14 and 0x00C1CA00 at +0x18: their sole slots are factory 0x003ACA24 (unsigned argument, pointer result, ret 4) and const class getter 0x003AD0FB (reference result), not destructors. The same derived primary table 0x00C1CF18 names const clone 0x003AEDB2 at slot 2. Primary tables 0x00C1C578 and 0x00C1C5BC have rowed DoXfer(Xfer &) overrides 0x0055EF39 and 0x0055F710 at slot 3; Snapshot adjustors 0x003ABD63 and 0x003ABDB8 subtract 0x1C and jump to those same bodies. Other slot names and secondary result types remain neutral ABI placeholders.

#pragma once

#ifndef __BFME2_RVA003AEEB3_H_
#define __BFME2_RVA003AEEB3_H_

#include "DefaultModuleHeadBase.h"
#include "Rva003AEEB3Bases.h"

class Xfer;

class Rva003AEEB3 : public DefaultModuleHeadBase, public Rva003AEEB3Slot14,
    public Rva003AEEB3Slot18
{
public:
    Rva003AEEB3(const Rva003AEEB3 &other);
    Rva003AEEB3(const RvaSmartPtr12 &smart, int value);
    virtual ~Rva003AEEB3();

    virtual void *vslot02() const = 0;
    virtual void DoXfer(Xfer &xfer) = 0;
};

typedef char Rva003AEEB3SizeCheck[sizeof(Rva003AEEB3) == 0x1C ? 1 : -1];

#endif
