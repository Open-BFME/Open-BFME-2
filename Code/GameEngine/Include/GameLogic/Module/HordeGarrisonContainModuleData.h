// Target facts (code addresses are RVAs, tables are VAs): constructor 0x0047A251 calls GarrisonContainModuleData's 0x0047978F at 0x0047A254, clears the four-byte ExitDelay at +0xAC at 0x0047A259, and installs 0x00BF4328 at 0x0047A263. Its MOVSS stores at 0x0047A26F..0x0047A2A0 zero three floats each at +0xB0, +0xBC and +0xC8. Factory 0x0024BAD1 requests 0xD4 bytes at 0x0024BADD and calls the constructor at 0x0024BAF5: sizeof is 0xD4 and the registered GarrisonContainModuleData base occupies 0xAC bytes.
// Target virtual interface: the 31-slot table 0x00BF4328 ends at 0x00BF43A4 and matches GarrisonContainModuleData's 0x00C462D8 except at slots 0 and 29. Slot 0 is deleting destructor 0x002579E9, which calls destructor 0x00257A05 at 0x002579EC; that destructor only jumps to GarrisonContainModuleData's 0x00257507, without a vptr store. The inherited Snapshot table 0x00BBB554 stored during base teardown at 0x002574F7 is not the live table. novtable preserves the explicit constructor store and the destructor's store-free tail call. Slot 29 is 0x0047A6A9 (8B C1 C3, returning this), so its neutral inherited name is overridden; all other slots come from the registered parent. Slot 2 remains 0x00065212, returning "ModuleData" at 0x00BC5AFC; this inherited name does not identify the derived class.
// Target fields and methods: buildFieldParse 0x0047A025 calls GarrisonContainModuleData::buildFieldParse at 0x0047A029 and registers 0x00C46388 at 0x0047A035. Its four entries name ExitDelay (+0xAC, INI::parseDurationUnsignedInt at 0x00338B30), EntryOffset (+0xB0), EntryPosition (+0xBC) and ExitOffset (+0xC8); the latter three use INI::parseCoord3D (0x0002F507). The ledger names the constructor, virtual destructor, buildFieldParse and friend_newModuleData (0x0024BAD1); the factory passes buildFieldParse at 0x0024BB0B. These rowed bodies remain out of line. TunnelContainModuleData's 0x0025797E calls this constructor at 0x00257990 and adds a float at +0xD4 at 0x002579B4, establishing a distinct larger derived object despite its shared 0x00BF4328 table.
#pragma once

#ifndef BFME2_HORDEGARRISONCONTAINMODULEDATA_H
#define BFME2_HORDEGARRISONCONTAINMODULEDATA_H

#include "GarrisonContainModuleData.h"

class __declspec(novtable) HordeGarrisonContainModuleData : public GarrisonContainModuleData
{
public:
    HordeGarrisonContainModuleData();
    virtual ~HordeGarrisonContainModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);
    virtual const void *slot29() const { return this; }

    unsigned int m_exitDelay;
    float m_entryOffset[3];
    float m_entryPosition[3];
    float m_exitOffset[3];
};

#endif
