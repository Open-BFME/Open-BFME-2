// Target facts (code addresses are RVAs; table addresses are VAs): 0x004FC807 calls the 0x10-byte Rva00330757Member constructor 0x00330757 at +8, initializes observer table 0x00C62A20 at +4, then installs its own tables 0x00C63530 at +0 and 0x00C63528 at +4. Destructor 0x004FC4D1 first installs those same own tables, then restores observer 0x00C62A20 and Snapshot 0x00BBB554 during base teardown. Allocation 0x003F27A9 pushes 0x38 before new at 0x003F27AE and constructor call 0x003F27D0; 0x003F3D54/0x003F3D7F corroborate the size.
// Primary table 0x00C63530 has four slots: deleting destructor 0x004FC563 (calls 0x004FC4D1), empty postprocess 0x000B3FD0, name getter 0x004FC55D (returns "LivingWorldBuildPlot" at VA 0x00C63540), and DoXfer 0x004FC57F. Observer table 0x00C63528 has BeginTurn 0x004FC23E and inherited RET8 callback 0x0050B238; there is no observer virtual destructor. Snapshot's supported capitalized name-slot surface gives the primary slot order.
// Constructor stores prove int +0x18, region pointer +0x1C, owned pointers +0x20/+0x24, Coord2D +0x28, int +0x30 and bools +0x34/+0x35; member names are neutral. Destructor calls 0x000AD6F4 on +0x24 and +0x20. CreateIcon 0x004FC185 passes +0x28 to the icon constructor and assigns holder +0x24; ConstructBuildingImmediately 0x004FC3DC assigns +0x20. Ledger rows prove the out-of-line method declarations and class-key below; no copy or assignment body is established.
#pragma once

#ifndef BFME2_LIVINGWORLDBUILDPLOT_H
#define BFME2_LIVINGWORLDBUILDPLOT_H

#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../Common/RegionTurnObserverView.h"
#include "../Common/Rva00330757Member.h"
#include "../Common/Rva000AD6F4.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"


class AsciiString;
class LivingWorldRegion;
struct Rva003F1BD3TemplateView;

class LivingWorldBuildPlot : public Snapshot, public Rva00330757Member,
                            public RegionTurnObserverView
{
public:
    LivingWorldBuildPlot(int id, LivingWorldRegion *region, const Coord2D &position);
    virtual ~LivingWorldBuildPlot();
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
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif
    virtual void BeginTurn(int, int);

    void CreateIcon(const AsciiString &iconName);
    void ConstructBuildingImmediately(const Rva003F1BD3TemplateView *templ);

    int field18;
    LivingWorldRegion *field1C;
    Rva000AD6F4 field20;
    Rva000AD6F4 field24;
    Coord2D field28;
    int field30;
    bool field34;
    bool field35;
};

typedef char LivingWorldBuildPlotSizeCheck[sizeof(LivingWorldBuildPlot) == 0x38 ? 1 : -1];

#endif
