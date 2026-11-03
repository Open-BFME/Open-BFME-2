// Target facts (code addresses are RVAs; table addresses are VAs):
// 0x004B57AA calls Rva00253487Base's 0x00253487 at +0, stores the live table 0x00BF2558 at +0, calls the 16-byte reset 0x0024CA24 at +0x118, then sets bit 3 there. The factory 0x00250252 allocates 0x128 bytes and calls 0x004B57AA; the object ends at +0x128.
// 0x00253487 stores the same table and calls 0x0025342C at +8. That member calls the 0x80-byte clear at 0x001EAE6F twice and initializes fields through member +0x10E, placing the base's end at +0x118. Its original type and member names are unproven; the ledger names the base Rva00253487Base.
// The 31 words at 0x00BF2558 end before zero at 0x00BF25D4. Slots 0..3 are 0x004A10FD, 0x000B3FD0, 0x00065212 and 0x0047A69C; slots 4..9, 11..13 and 15 return false (0x0047A699), slots 10 and 30 return true (0x0050B5C6), slot 14 returns AsciiString with one int argument (0x000B69A1), and slots 16..29 return null (0x000D43D0). This is a polymorphic data class; no additional derived slots are present.
// Slot 0's 0x004A10FD calls 0x0049B47C, which stores Snapshot's four-slot table 0x00BBB554, then conditionally frees the object. That table describes base teardown, not the live object's 31-slot interface. Destructors remain declarations.
// The ModuleData prefix is represented by its registered header: table 0x00C549F8 differs from 0x00BF2558 only in slots 0 and 10, and ModuleFactory::newModuleDataFromINI writes the module tag at +4 at 0x00257237. Slot 10 is overridden to true and the remaining base storage is opaque. This inheritance is a structural inference from that interface and the +8 base-member construction, not a recovered original base name.
// buildFieldParse at 0x004B56F6 adds the table returned by 0x004CE29D with offset 8, then table 0x00C58020: its WeaponCondition token (0x00C58010), parser 0x002C8C06 and field offset 0x118 agree with the constructor. The factory passes this parse procedure out of line. No Zero Hour declaration supplies this class's layout or names.
#pragma once

#ifndef BFME2_WEAPONSETUPGRADEMODULEDATA_H
#define BFME2_WEAPONSETUPGRADEMODULEDATA_H

#include "Rva00253487Base.h"

class INI;
class MultiIniFieldParse;

class WeaponSetUpgradeModuleData : public Rva00253487Base
{
public:
    WeaponSetUpgradeModuleData();
    virtual ~WeaponSetUpgradeModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    unsigned long m_field118[4];
};

#endif
