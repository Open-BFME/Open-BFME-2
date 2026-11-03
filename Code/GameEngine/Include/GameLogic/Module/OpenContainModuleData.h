// Target facts (code addresses are RVAs, tables are VAs): constructor 0x00465124 stores 0x00C43658 at 0x00465140; allocation 0x0024B730 requests 0x98 bytes before calling it at 0x0024B748, and TransportContainModuleData's 0x00468316 calls it before starting fields at +0x98. ModuleData occupies eight bytes; DieMuxData is constructed at +8 by 0x00465146. Destructor 0x00257481 destroys members before restoring Snapshot's 0x00BBB554 at 0x002574F7; this is the base teardown table, not this class's live table. Slot 0 of 0x00C43658 calls deleting destructor 0x00465221, which calls 0x00257481 at 0x00465224. The 31-slot live table inherits ModuleData's interface and overrides slot 8 with true (0x0050B5C6); its other slots match ModuleData. Constructors and the virtual destructor remain out of line.
// Target fields: 0x0046514B/0x0046514E null the sound handles at +0x38/+0x3C; 0x002574DF/0x002574EF release their pointees through 0x00050ED3. Calls 0x00465158/0x00465164 construct four-byte Rva003623E5Member handles at +0x40/+0x44. Calls 0x00465174, 0x00465180, 0x00465188 and 0x00465199 construct the list at +0x48, set at +0x4C, 16-byte bitset at +0x58 and 12-byte string vector at +0x88. Teardown 0x0025749F/0x002574AB/0x002574B7 bounds the vector, set and list; their unrecovered storage uses neutral placeholders. Constructor stores 0x004651A6..0x0046520A prove four-byte scalars at +0x68/+0x6C/+0x70/+0x74/+0x78/+0x94 and byte flags at +0x7C..+0x86.
// Target names: buildFieldParse 0x0046523D registers the 16-byte-entry table 0x00C438B0 and DieMuxData's table at offset 8. Entries 0x00C438B0..0x00C43A20 name ContainMax (+0x70), EnterSound (+0x38), ExitSound (+0x3C), DamagePercentToUnits (+0x6C), PassengerFilter (+0x40), ManualPickUpFilter (+0x44), PassengersTestCollisionHeight (+0x68), PassengersInTurret (+0x85), NumberOfExitPaths (+0x74), DoorOpenTime (+0x78), the nine flags at +0x7C..+0x84, ObjectStatusOfContained (+0x58), ModifierToGiveOnExit (+0x88) and ModifierRequiredTime (+0x94). Zero Hour's OpenContain.h supplies shared member spellings and unsigned DoorOpenTime; its UpdateModuleData inheritance and field placement are not used. No original name is asserted for the byte at +0x86 or the container storage.
#pragma once

#ifndef BFME2_OPENCONTAINMODULEDATA_H
#define BFME2_OPENCONTAINMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "../../Common/OpaqueRefElement4.h"
#include "DieMuxData.h"
#include "Rva003623E5Member.h"

class OpenContainModuleData : public ModuleData
{
public:
    OpenContainModuleData();
    virtual ~OpenContainModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    virtual bool slot08() const { return true; }

    DieMuxData m_dieMuxData;
    OpaqueRefElement4 m_enterSound;
    OpaqueRefElement4 m_exitSound;
    Rva003623E5Member m_passengerFilter;
    Rva003623E5Member m_manualPickUpFilter;
    void *m_slot48;
    unsigned char m_storage4C[0x0C];
    unsigned int m_objectStatusOfContained[4];
    float m_passengersTestCollisionHeight;
    float m_damagePercentToUnits;
    int m_containMax;
    int m_numberOfExitPaths;
    unsigned int m_doorOpenTime;
    bool m_allowOwnPlayerInsideOverride;
    bool m_allowAlliesInside;
    bool m_allowEnemiesInside;
    bool m_allowNeutralInside;
    bool m_showPips;
    bool m_collidePickup;
    bool m_ejectPassengersOnDeath;
    bool m_killPassengersOnDeath;
    bool m_enabled;
    bool m_passengersInTurret;
    bool m_slot86;
    unsigned char m_pad87;
    unsigned char m_storage88[0x0C];
    unsigned int m_modifierRequiredTime;
};

#endif
