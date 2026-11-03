// Target facts (code addresses are RVAs; tables are VAs): constructor 0x002D76A6 clears words +4/+8 and installs 0x00C7506C. Factory 0x0004F84E allocates 0x24 for derived constructor 0x0004EF5D, which calls 0x002D76A6 and begins its own storage at +0x0C; the inferred RadarMarker base extent is 12 bytes. Its holder 0x0004E4C9 calls AddReference (0x002D76B7), connecting this constructor to the named reference API.
// Table 0x00C7506C has four slots before the separately installed 0x00C7507C (constructor 0x005CDB8F): deleting destructor 0x005FAA31 and three __purecall entries (0x0003B810). The deleting destructor calls 0x004E84A4, which restores the registered Rva0007DF07 parent's 0x00BC6F20 table; that parent's constructor 0x0007DF07 clears +4 and its sole slot is deleting destructor 0x0007E5EE. The differing tables describe derived construction and base teardown, with the first eight bytes inherited once and no observed virtual base.
// AddReference (0x002D76B7) increments the dword at +8; DeleteReference (0x002D76BB) decrements it and dispatches slot 1 at zero. Assignment 0x004C9B8F calls both out of line. Derived table 0x00BC4DDC has slot 1 at 0x0004F7F4, slot 2 at 0x005C4AD9 (address of +0x14), and slot 3 at 0x00330CC2 (copies three dwords from its pointer argument to +0x14); caller 0x004C9D64 passes a Coord3D position through forwarder 0x005CB265 to slot 3. Unrecovered slots and storage retain neutral names; the class is polymorphic and lifetime methods remain declarations.
#ifndef BFME2_RADARMARKER_H
#define BFME2_RADARMARKER_H

#include "../Common/Rva0007DF07.h"

struct Coord3D;

class RadarMarker : public Rva0007DF07
{
public:
    RadarMarker();
    virtual ~RadarMarker();
    virtual void v1() = 0;
    virtual const Coord3D *slot02() const = 0;
    virtual void slot03(const Coord3D *position) = 0;

    void AddReference();
    void DeleteReference();

    int m_08;
};

#endif
