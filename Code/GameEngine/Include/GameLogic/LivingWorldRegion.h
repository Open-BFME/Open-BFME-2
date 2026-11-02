// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x003F3967 installs 0x00C36FA4 at +0; destructor 0x003F332E installs the same table before restoring Snapshot's 0x00BBB554 at 0x003F3407. The latter is the base teardown table, not a competing LivingWorldRegion table. Snapshot is the only polymorphic base; the 0x00330757 constructor at +4 initializes a nonvirtual 0x10-byte listener header, whose unrecovered storage stays opaque here.
// Table 0x00C36FA4 has four slots: 0=0x003F36EC (deleting destructor, calls 0x003F332E), 1=0x003F08EE (loadPostProcess), 2=0x003F3418 (const GetSnapshotName, returns "LivingWorldRegion"), 3=0x003F3BFF (DoXfer). The following word at 0x00C36FB4 is string data, so there is no fifth slot. The registered Snapshot header supplies this four-slot layout; its xfer spelling is selected as DoXfer when included here.
// Parser 0x00210620 pushes 0x1B4 at 0x00210649 before allocation and calls 0x003F3967 at 0x00210684: sizeof is 0x1B4. That constructor builds the 0x118-byte descriptor at +0x14 (0x003F3749), writes ID +0x12C, owner pointer +0x130, dwords +0x134/+0x138/+0x13C/+0x140/+0x14C/+0x150/+0x154/+0x17C/+0x198/+0x19C, zeroes two floats +0x144/+0x148, initializes twelve-byte headers +0x158/+0x164/+0x170/+0x180/+0x18C/+0x1A8, and clears bytes +0x1A0..+0x1A4. Descriptor teardown 0x003F2D03 ends at +0x12C.
// GetFortressPortrait 0x003F0442 proves AsciiString +0x120; GetFortressDisplayName 0x003F0466 and GetFortressDisplayDescription 0x003F04E0 prove strings +0x124/+0x128; SetupRegionOwnership 0x003F300A proves the string at +0xE0. Descriptor construction 0x003F3749 copies the supplied name to its first word, region +0x14. GetGarrisonArmyPlacementSpot 0x003F0F13 reads the eight-byte-element range +0xF0/+0xF4; its unrecovered container spelling remains opaque.
// The descriptor constructor writes dword +0x44 at 0x003F37B4 (region +0x58), bytes +0x94/+0x95 at 0x003F37F6/0x003F37FC (region +0xA8/+0xA9), dwords +0xF4/+0xF8 at 0x003F3893/0x003F389D (region +0x108/+0x10C), and byte +0x108 at 0x003F38AC (region +0x11C). Retail reads region +0x58 at 0x00503707, +0xA9 at 0x003F34F1, and +0x11C at 0x003F2220/0x002B0743. These fields keep neutral names.
// The out-of-line declarations below preserve the ledger's member names, access and signatures, with each row's RVA beside it. No LivingWorldRegion declaration exists in the supplied Zero Hour tree, so unnamed storage has neutral offset names. All owned-container storage remains opaque; constructor and destructor bodies are declared only.
#pragma once

#ifndef BFME2_GAMELOGIC_LIVINGWORLDREGION_H
#define BFME2_GAMELOGIC_LIVINGWORLDREGION_H

#ifdef __SNAPSHOT_H_
#error Include LivingWorldRegion.h before Snapshot.h to select its retail DoXfer slot.
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#define xfer DoXfer
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#undef xfer
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

class CreateAHeroData;
class Image;
class INI;
class LivingWorldBattle;
class LivingWorldBuilding;
class Rva002E2903Player;
class Rva003F1C56Plot;
class Rva003F7BB4;
class SpawnArmy;
class UnicodeString;
class Xfer;
struct Elem003B2540;
struct LivingWorldBuildPlot;
struct PlacementRange;
struct Rva003F0F13Elem;
struct Rva003F1BD3TemplateView;
struct Rva0059E647Entry;
class Rva005CB29ADisplay;
enum NameKeyType;

class LivingWorldRegion : public Snapshot
{
    friend void Rva005CB2D2(Rva005CB29ADisplay *, LivingWorldRegion *);
    friend int GetMaxCommandPoints(void *);
    friend class Rva005CB748;

public:
    LivingWorldRegion(void *, int, const AsciiString &); // 0x003F3967
    virtual ~LivingWorldRegion(); // 0x003F332E
    virtual void loadPostProcess(); // 0x003F08EE
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // 0x003F3418
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void DoXfer(Xfer *); // 0x003F3BFF

    bool IsOwnedByTeam(int) const; // 0x003EFD3D
    bool CanSpawnUnitWithinCPLimit(SpawnArmy *) const; // 0x003F0259
    bool rva003F0201(SpawnArmy *) const; // 0x003F0201
    void rva003EFE72(void *, Rva0059E647Entry *); // 0x003EFE72
    int rva003F0189(Rva002E2903Player *) const; // 0x003F0189
    const Image *GetFortressPortrait(); // 0x003F0442
    UnicodeString GetFortressDisplayName(); // 0x003F0466
    UnicodeString GetFortressDisplayDescription(); // 0x003F04E0
    void *rva003F0588(); // 0x003F0588
    int rva003F05CE(); // 0x003F05CE
    int rva003F0614(CreateAHeroData *) const; // 0x003F0614
    int rva003F066B(CreateAHeroData *) const; // 0x003F066B
    int rva003F06C2(CreateAHeroData *) const; // 0x003F06C2
    LivingWorldBuilding *GetBuildingByIndex(int) const; // 0x003F0711
    LivingWorldBuildPlot *rva003F088C(int) const; // 0x003F088C
    bool DebugValidatePlacementSpot(const Coord2D &, Coord2D *, const char *); // 0x003F0DCB
    void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *); // 0x003F0F13
    void rva003F0F48(PlacementRange *, void *); // 0x003F0F48
    void rva003F0FA3(void *); // 0x003F0FA3
    int rva003F1053(); // 0x003F1053
    bool rva003F1B7C(CreateAHeroData *, const Rva003F1BD3TemplateView *, int *); // 0x003F1B7C
    bool rva003F1BD3(NameKeyType, int *); // 0x003F1BD3
    void BuildBuilding(Rva003F1C56Plot *, const Rva003F1BD3TemplateView *); // 0x003F1C56
    void rva003F2150(Rva003F7BB4 *); // 0x003F2150
    void CreateBuildPlots(); // 0x003F274C
    void SetupRegionOwnership(); // 0x003F300A
    void PrepareSkirmishOpponents(LivingWorldBattle *); // 0x003F34DD
    Elem003B2540 *rva003F3708(int); // 0x003F3708

    class ModuleData
    {
    public:
        class BuildingRestriction
        {
        public:
            static void ParseINI(INI *, void *); // 0x003F2576
        };
    };

    char m_storage04[0x10];
    AsciiString m_field14;
    char m_storage18[0x58 - 0x18];
    int m_field58;
    char m_storage5C[0xA8 - 0x5C];
    bool m_fieldA8;
    bool m_fieldA9;
    char m_storageAA[0xE0 - 0xAA];
    AsciiString m_fieldE0;
    char m_storageE4[0x108 - 0xE4];
    int m_field108;
    int m_field10C;
    char m_storage110[0x11C - 0x110];
    bool m_field11C;
    char m_storage11D[0x120 - 0x11D];
    AsciiString m_field120;
    AsciiString m_field124;
    AsciiString m_field128;
    int m_field12C;
    void *m_field130;
    int m_field134;
    int m_field138;
    int m_field13C;
    int m_field140;
    Coord2D m_field144;
    int m_field14C;
    int m_field150;
    int m_field154;
    char m_storage158[0x17C - 0x158];
    LivingWorldBuildPlot *m_field17C;
    char m_storage180[0x198 - 0x180];
    void *m_field198;
    int m_field19C;
    bool m_field1A0;
    bool m_field1A1;
    bool m_field1A2;
    bool m_field1A3;
    bool m_field1A4;
    char m_storage1A5[0x1B4 - 0x1A5];

private:
    int rva003EFD6F(Rva002E2903Player *) const; // 0x003EFD6F
    int rva003EFDB3(Rva002E2903Player *) const; // 0x003EFDB3
};

#endif
