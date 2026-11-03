// Target facts (addresses are RVAs): constructor 0x0056AD80 (85 bytes) and destructor 0x0056AC26 (84 bytes) install tables 0x0086D058 at +0 and 0x0086D01C at +8. Destructor 0x0056AC26 restores registered Rva0056AC26Base2's table 0x00837298 at +8 and registered Rva0007DF07's table 0x007C6F20 at +0; 0x0007DF07 zeros that base's word +4, as does 0x0056AD8E. The registered parents supply the eight-byte and four-byte base subobjects.
// Target facts: 0x0056ADA4 passes +0x0C as the UnicodeString result of 0x003F855D; 0x0056AC54 passes it to releaseBuffer at 0x00036E70. 0x0056ADC3 stores the owner pointer at +0x10, which 0x0056AC44 loads for 0x003F88A7. The accessed extent is 0x14; derived constructor 0x0056B3F5 places its next polymorphic base at +0x14 (0x0056B412), bounding this base at 20 bytes. No standalone allocation of this abstract class proves its size.
// Target facts: primary table 0x0086D058 has five slots before the secondary table at 0x0086D06C: deleting destructor 0x0056ADD5, purecall 0x0003B810, RET4 stub 0x0047A69C, and RET stubs 0x000B3FD0 twice. Derived primary table 0x0086D19C has the rowed bool ac26Slot1() at 0x0056ABC0 in slot 1. Secondary table 0x0086D01C has 15 slots before 0x0086D058: slot 0 is 0x0056AC7A (this minus 8, then 0x0056ADD5); slots 1..14 equal registered parent table 0x00837298. Slot argument words and the field labels below assert no original names or semantic types.
#ifndef CANONICAL_RVA0056AC26_H
#define CANONICAL_RVA0056AC26_H

#include "Rva0007DF07.h"
#include "Rva0056AC26Base2.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class Rva0056AC26Owner;

class Rva0056AC26 : public Rva0007DF07, public Rva0056AC26Base2
{
public:
    Rva0056AC26(Rva0056AC26Owner *owner);
    virtual ~Rva0056AC26();
    virtual bool ac26Slot1() = 0;
    virtual void vslot02(int) {}
    virtual void vslot03() {}
    virtual void vslot04() {}

private:
    UnicodeString m_0C;
    Rva0056AC26Owner *m_10;
};

#endif
