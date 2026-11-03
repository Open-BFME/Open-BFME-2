// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x0048BC03 stores 0x00C4C110 at 0x0048BC20, constructs the four-byte list at +8 through 0x004EC36C at 0x0048BC26, and clears bytes +0xC/+0xD/+0xE at 0x0048BC2E/0x0048BC32/0x0048BC36. Factory 0x0024CF56 requests 0x10 bytes at 0x0024CF62 and calls the constructor at 0x0024CF77. The constructor and virtual destructor remain out of line.
// Target facts: destructor 0x0048BC46 restores 0x00C4C110 at 0x0048BC5A, drains the list at +8, calls its base destructor 0x004EC395 at 0x0048BCA1, then stores Snapshot's 0x00BBB554 at 0x0048BCAA. Constructor unwind 0x0078C551 also calls Snapshot's 0x0049B47C. The four-slot Snapshot table is base teardown; 0x00C4C110 is this class's live table. Its slot 0 is deleting destructor 0x0048C098, which calls 0x0048BC46 at 0x0048C09B; slots 1..30 equal ModuleData's table 0x00C549F8. The next table starts at 0x00C4C18C. ModuleFactory writes the tag at +4 at 0x00257237. ModuleData inheritance represents this eight-byte prefix and common interface; these bytes do not identify an intermediate base name. Slot 2's shared ModuleData name getter 0x00065212 is inherited.
// Target facts: parser 0x0048C0B4 adds table 0x00C4C210. HeroModeTrigger, ChargingModeTrigger and AliveOnly use parseBool (0x0002E850) with offsets +0xC/+0xD/+0xE. FireWeaponNugget uses callback 0x0048BCBB with offset zero; that callback appends at +8 at 0x0048BD03/0x0048BD09. The list's original member name and element declaration are unproven, so its four-byte representation has neutral storage. Zero Hour FireWeaponUpdate.h supplies the class and buildFieldParse names, but its weapon/delay members do not describe BFME2's layout.
#pragma once

#ifndef BFME2_FIREWEAPONUPDATEMODULEDATA_H
#define BFME2_FIREWEAPONUPDATEMODULEDATA_H

#include "../../Common/ModuleData.h"

class INI;
class MultiIniFieldParse;

class FireWeaponUpdateModuleData : public ModuleData
{
public:
    FireWeaponUpdateModuleData();
    virtual ~FireWeaponUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    unsigned char m_storage08[4];
    bool m_heroModeTrigger;
    bool m_chargingModeTrigger;
    bool m_aliveOnly;
};

#endif
