// Target facts (code addresses are RVAs, tables are VAs): constructor 0x0047978F calls OpenContainModuleData at 0x004797A2, then installs 0x00C462D8 at 0x004797A9. Factory 0x00254F90 requests 0xAC bytes at 0x00254F9C and calls that constructor at 0x00254FB4; HordeGarrisonContainModuleData's constructor 0x0047A251 calls it at 0x0047A254 and starts its fields at +0xAC. The registered parent occupies 0x98 bytes. The 31-slot table at 0x00C462D8 inherits slots 1..30 unchanged from the parent's 0x00C43658; slot 0 is deleting destructor 0x0047981E, which calls destructor 0x00257507 at 0x00479821. Destructor 0x00257507 releases the string at +0xA4 through 0x00036410 at 0x00257522, then calls the parent at 0x0025752D, without installing a table; the parent's store of Snapshot's 0x00BBB554 at 0x002574F7 belongs to base teardown. Constructors and the virtual destructor remain out of line.
// Target fields: constructor stores at 0x004797B2, 0x004797F1, 0x004797F7, 0x004797FD, 0x00479803 and 0x00479809 prove the four-byte string at +0xA4, byte flags at +0xA0/+0x98/+0xA1, four-byte count at +0xA8 and float at +0x9C. buildFieldParse 0x00254F75 calls the parent's parser and registers 0x00BF3360 at 0x00254F85; its entries name MobileGarrison (+0xA0), HealObjects (+0x98), TimeForFullHeal (+0x9C), InitialRoster (parser 0x0025363A) and ImmuneToClearBuildingAttacks (+0xA1). parseInitialRoster calls StringBase<char>::set at 0x00253674 on +0xA4 and stores the integer at +0xA8 at 0x00253679. The remaining bytes are padding, with no asserted field identity.
// Names and methods: Zero Hour's GeneralsMD GameLogic/Module/GarrisonContain.h supplies the shared field spellings and InitialRoster grouping; its IsEnclosingContainer field is not asserted for BFME2. Ledger rows name GarrisonContainModuleData's constructor (0x0047978F), destructor (0x00257507), buildFieldParse (0x00254F75), parseInitialRoster (0x0025363A) and friend_newModuleData (0x00254F90); the factory calls the constructor and passes buildFieldParse out of line. The inherited Snapshot name getter 0x00065212 returns "ModuleData", as it does for the parent; the distinct constructor, 0xAC allocation and deleting-destructor table establish this derived identity.
#pragma once

#ifndef BFME2_GARRISONCONTAINMODULEDATA_H
#define BFME2_GARRISONCONTAINMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "OpenContainModuleData.h"

class INI;

class GarrisonContainModuleData : public OpenContainModuleData
{
public:
    struct InitialRoster
    {
        AsciiString templateName;
        int count;
    };

    GarrisonContainModuleData();
    virtual ~GarrisonContainModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static void parseInitialRoster(INI *ini, void *instance, void *store, const void *);
    static ModuleData *friend_newModuleData(INI *ini);

    bool m_doIHealObjects;
    float m_framesForFullHeal;
    bool m_mobileGarrison;
    bool m_immuneToClearBuildingAttacks;
    InitialRoster m_initialRoster;
};

#endif
