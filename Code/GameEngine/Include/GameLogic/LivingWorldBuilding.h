// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x004E119C calls the 0x00330757 nonvirtual 0x10-byte listener-header constructor at +8, initializes observer table 0x00C62A20 at +4, then installs 0x00C61618 at +0 and 0x00C61610 at +4 (stores 0x004E11E9/0x004E11EF). Destructor 0x004E0D67 installs those same derived tables (0x004E0D7C/0x004E0D82), then restores observer 0x00C62A20 at 0x004E0E2F and Snapshot 0x00BBB554 at 0x004E0E4B. These later tables belong to base teardown. The registered Snapshot, Rva00330757Member and RegionTurnObserverView headers supply the bases; no vbptr is stored.
// Table 0x00C61618 has four slots: deleting destructor 0x004E0E5C (calls destructor 0x004E0D67), LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x004E0777 (returns the LivingWorldBuilding literal at 0x00C046E8), and DoXfer 0x004E0E78. String data starts at 0x00C61628. Observer table 0x00C61610 has BeginTurn 0x004E06B8 and inherited OnTurnEnding 0x0050B238, ending at the primary table. BeginTurn uses this-4 at 0x004E06D4, proving the +4 receiver. The base observer table has two RET8 entries at 0x0050B238; its constructor 0x0020E346 and destructor 0x004EDFFF install it. No registered class has this constructor, destructor, derived table or Snapshot name.
// Allocation 0x004FC356 pushes 0x54 before allocator 0x004FC358 and constructor call 0x004FC383, proving sizeof 0x54. Constructor 0x004E119C writes ID +18, dwords +1C/+20, region pointer +24, template pointer +28, icon pointer +2C, three-word range +30/+34/+38 through 0x00211E58, counted pointer +3C, cached pointers +40/+44, Coord2D +48/+4C and bytes +50/+51. Destructor 0x004E0D67 frees the ranges +30 and +8 and releases +3C; scan 0x004E0809 assigns virtual-call pointer results to +40/+44. DoXfer 0x004E0E78 transfers the position and byte +51. Other out-of-line rows are rva004E060C 0x004E060C, createIcon 0x004E063F, rva004E0809 0x004E0809, rva004E0845 0x004E0845, rva004E0860 0x004E0860, createGhostObject 0x004E0A96 and updateArmySummaryEntryRepresentation 0x004E0BDC. Unproved field identities retain offset names; all rowed methods remain declarations.
#pragma once

#ifndef BFME2_GAMELOGIC_LIVINGWORLDBUILDING_H
#define BFME2_GAMELOGIC_LIVINGWORLDBUILDING_H

#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../Common/Rva00330757Member.h"
#include "../Common/RegionTurnObserverView.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

class LivingWorldRegion;
class LivingWorldBuildingTemplate;
class Rva003F7BB4;
struct Rva003F1BD3TemplateView;
struct Rva004E0790Inner;
struct EmitVtableTag;

class LivingWorldBuilding : public Snapshot, public Rva00330757Member, public RegionTurnObserverView
{
public:
    LivingWorldBuilding(LivingWorldRegion *, const Coord2D &, const Rva003F1BD3TemplateView *, int);
    // Existing non-retail table-emission overload in OpaqueScalarDeletingDtorsB11.cpp.
    LivingWorldBuilding(EmitVtableTag *);
    virtual ~LivingWorldBuilding();
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif
    virtual void BeginTurn(int, int);

    void rva004E060C(unsigned char);
    void createIcon();
    void rva004E0809();
    void rva004E0845();
    void rva004E0860(Rva003F7BB4 *);
    void createGhostObject();
    void updateArmySummaryEntryRepresentation(const Rva004E0790Inner &);

    int field18;
    int field1C;
    int field20;
    LivingWorldRegion *field24;
    const LivingWorldBuildingTemplate *field28;
    void *field2C;
    void **field30;
    void **field34;
    void **field38;
    Rva004E0790Inner *field3C;
    void *field40;
    void *field44;
    Coord2D field48;
    unsigned char field50;
    bool field51;
};

typedef char LivingWorldBuildingSizeCheck[sizeof(LivingWorldBuilding) == 0x54 ? 1 : -1];

#endif
