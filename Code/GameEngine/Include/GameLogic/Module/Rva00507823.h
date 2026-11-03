// Target facts (RVAs): constructor 0x0050775B and destructor 0x00507823 both store table 0x00864010 (VA 0x00C64010) at +0; neither constructs a base. Constructor stores +0x104 (4 bytes) and +0x124 (1 byte); derived constructor 0x0050B6B4 starts its data at +0x128, bounding the four-byte-aligned base to 0x128 bytes.
// Target table: 14 slots before the next table at 0x00864048, installed by the derived constructor at 0x00507C89. Slot 0 is deleting destructor 0x00507807; 1/2 are 0x005075D6/0x0050774A (RET 8, byte result); 3/4/9 are 0x0050B238 (RET 8); 5/6/7 are __purecall 0x0003B810; 8 is rva00507877 at 0x00507877; 10/11 are 0x000D43D0 (zero EAX); 12/13 are 0x0047A699 (zero AL). Caller 0x002CAAC4 invokes slot 7 without arguments and tests AL at 0x002CAAC7; 0x002CAAE6 and 0x005079E7 invoke slots 5/6 with two arguments. The rowed prerequisite methods retain their nonvirtual ledger spellings.
// Target storage and calls: 0x00507779/0x00507784 clear 0x80 bytes at +4/+0x84 through 0x001EAE6F; 0x0050779A/0x005077AD construct 12-byte vectors at +0x108/+0x114 through 0x00211E58; 0x005077BE constructs the four-byte filter at +0x120 through 0x003623E5. Destructor calls 0x00360D26 at +0x120 and 0x0002CC70 at +0x114/+0x108. Out-of-line methods are 0x00507558, 0x005075D6, 0x0050774A and 0x00507877; 0x005078AA/0x005078E8 index the two masks by four-byte words. Storage names and unproved slot names are neutral.
#pragma once

#ifndef __BFME2_RVA00507823_H_
#define __BFME2_RVA00507823_H_

class Object;

class Rva00507823
{
public:
    Rva00507823();
    virtual ~Rva00507823();

    virtual unsigned char vslot01(const void *, Object *);
    virtual unsigned char vslot02(const void *, int);
    virtual void vslot03(const void *, void *);
    virtual void vslot04(const void *, void *);
    virtual void vslot05(const void *, void *) = 0;
    virtual void vslot06(const void *, void *) = 0;
    virtual bool vslot07() = 0;
    virtual void rva00507877();
    virtual void vslot09(const void *, void *);
    virtual void *vslot10();
    virtual void *vslot11();
    virtual bool vslot12();
    virtual bool vslot13();

    unsigned char rva00507558(const void *);
    unsigned char rva005075D6(const void *, Object *);
    unsigned char rva0050774A(const void *, int);

    unsigned long m_mask04[32];
    unsigned long m_mask84[32];
    int m_field104;
    unsigned char m_storage108[12];
    unsigned char m_storage114[12];
    int m_field120;
    bool m_flag124;
};

#endif
