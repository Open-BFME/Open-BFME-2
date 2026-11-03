// Target facts: Rva003623E5Member is a nonvirtual four-byte pool-index handle with no base and no virtual functions. Constructor RVA 0x003623E5 writes only the dword at +0 (0x003623F8 and 0x00362421); destructor RVA 0x00360D26 forwards this to 0x00360CB0, which reads +0 at 0x00360CB5 and resets it to -1 at 0x00360CE6. Neither installs a vtable. OpenContainModuleData constructs handles at +0x40/+0x44 (0x00465151/0x00465158 and 0x0046515D/0x00465164), then another member at +0x48 (0x0046516C/0x00465174), bounding the handle to four bytes. The index comes from the ledger's int-returning 0x00361790; m_x is a neutral placeholder because the field's original name is unknown.
// Target record distinction: 0x003623E5 reserves a separate 0x94-byte stack record at 0x003623EF, constructs it through 0x00360F55 at 0x00362401, interns it through 0x00361790 at 0x00362411 and destroys it through 0x00360FDB at 0x00362423. This record is not handle storage; the handle has no constructor/destructor vftables or inherited slots.
// Target methods: ledger rows declare the constructor (0x003623E5), initFromStorages (0x00362087) and rva00362192 (0x00362192); both methods consume two 28-byte values and return with ret 0x38 (0x0036211D and 0x0036223D). The existing destructor pin names 0x00360D26 and construct pin names 0x003623E5; retail 0x0045A1E2 calls the latter on the entry's +4 member. All methods remain out of line.
#pragma once

#ifndef __BFME2_RVA003623E5MEMBER_H_
#define __BFME2_RVA003623E5MEMBER_H_

class BfmeFixedStorage0004543D;
class Rva00045411BitSet;

class Rva003623E5Member
{
public:
    Rva003623E5Member();
    ~Rva003623E5Member();
    void construct();
    void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
    void rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second);

    int m_x;
};

#endif
