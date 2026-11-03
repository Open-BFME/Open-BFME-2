// Target facts (retail RVAs): constructors 0x0037E352 (default), 0x0037E289 (ThingTemplate), 0x0037E94A (Object) and 0x002E134C (copy), and destructor 0x001EB63C have no vptr stores or base construction; UnitRevivalEntry has no virtual functions or parent. The vector accessor loads divisor 0xD8 at 0x0037E432 for division at 0x0037E437 and multiplies by 0xD8 at 0x0037E440, proving sizeof 0xD8. Copy stores at 0x002E1360..0x002E144E establish the member offsets below; original member names are unknown.
// 0x0037EC01 returns the Image pointer at +0; 0x0037ED5E stores an image-collection result at +4. 0x0037E366/0x0037E3C0 store floats at +8/+CC. The +14 member is copied through BfmeFixedStorage128's 0x0004548B at 0x002E1384 and cleared through 0x001EAE6F at 0x0037E371. Transfer calls 0x0037E4F9/0x0037E515 use unsigned +94/+9C; 0x002E13B3/0x002E13BF copy the +A0/+A1 bytes. +A2/+A3 are alignment padding. +B0 is a 0x18-byte subrecord copied at 0x002E13F6 through 0x001EB15A (three dwords, UnicodeString +C, AsciiString +10, byte +14); its representation stays opaque here. 0x001EB65A/0x001EB669 destroy AsciiStrings at +D4/+D0, then 0x001EB678 destroys the +B0 record through 0x001EB05E.
// Out-of-line method rows: getThingTemplate 0x0037E270, setThingTemplateName 0x0037E3D9, rva0037E473 0x0037E473, revivalEntryCalcCostToBuild 0x0037E18A, revivalEntryCalcTimeToBuild 0x0037E1FD, calcButtonImage 0x0037EBEA. Copy call 0x0037EFA9 and destructor call 0x0037F477 require declarations without inline bodies. Assignment of the same D8 record calls 0x002E0D93 at 0x002E17C1 in its vector copy; private users declare operator= out of line. No constructor or destructor vftable exists for this class.
#pragma once

#ifndef BFME2_UNITREVIVALENTRY_H
#define BFME2_UNITREVIVALENTRY_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../Common/BfmeFixedStorage128.h"

class Image;
class Object;
class Player;
class ThingTemplate;
class Xfer;

class UnitRevivalEntry
{
public:
    UnitRevivalEntry();
    UnitRevivalEntry(Object *object);
    UnitRevivalEntry(const ThingTemplate *thingTemplate);
    UnitRevivalEntry(const UnitRevivalEntry &other);
    ~UnitRevivalEntry();
    UnitRevivalEntry &operator=(const UnitRevivalEntry &other);

    void *getThingTemplate();
    void setThingTemplateName(const AsciiString &name);
    void rva0037E473(Xfer *xfer);
    int revivalEntryCalcTimeToBuild(const Player *player, Object *producer);
    int revivalEntryCalcCostToBuild(const Player *player, Object *producer);
    const Image *calcButtonImage(const Player *player);

    const Image *m_field00;
    const Image *m_field04;
    float m_field08;
    int m_field0C;
    int m_field10;
    BfmeFixedStorage128 m_field14;
    unsigned int m_field94;
    int m_field98;
    unsigned int m_field9C;
    bool m_fieldA0;
    bool m_fieldA1;
    int m_fieldA4;
    int m_fieldA8;
    int m_fieldAC;
    char m_fieldB0[0x18];
    int m_fieldC8;
    float m_fieldCC;
    AsciiString m_fieldD0;
    AsciiString m_fieldD4;
};

#endif
