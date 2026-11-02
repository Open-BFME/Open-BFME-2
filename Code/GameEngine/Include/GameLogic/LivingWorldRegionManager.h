// LivingWorldRegionManager: canonical BFME2 layout and out-of-line declarations.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0021042D stores the observer base table 0x00C62A20 at +4 (0x00210448), then installs this class's tables 0x00BE4358 at +0 and 0x00BE4350 at +4 (0x00210455/0x0021045B). Destructor 0x00210B38 installs the same derived tables (0x00210B50/0x00210B56), then restores 0x00C62A20 at +4 and Snapshot's 0x00BBB554 at +0 (0x00210BFF/0x00210C05). These stores describe base and derived lifetime stages. The registered Snapshot and RegionTurnObserverView headers supply the two four-byte bases; the original observer name remains unknown.
// Table 0x00BE4358 contains exactly four slots: deleting destructor 0x00210C17, loadPostProcess 0x002102CA, GetSnapshotName 0x002104B0 and xfer 0x00210202. The getter returns the LivingWorldRegionManager string at 0x00BE4368, immediately after the table. The deleting destructor calls the complete destructor at 0x00210C1A and conditionally calls scalar delete at 0x00210C27. The secondary table 0x00BE4350 has BeginTurn 0x0020EB07 and OnTurnEnding 0x0020FB41, both receiving the +4 subobject; the next word begins the primary table. Its base table 0x00C62A20 has two ret-8 callbacks at 0x0050B238 and no destructor slot. The constructor registers this+4 with its argument+0x1C at 0x00210490..0x00210498; the destructor unregisters the same subobject at 0x00210BB8..0x00210BC2.
// LivingWorldLogic's constructor pushes allocation size 0x40 at 0x002B95CB, calls scalar new at 0x002B95D1, calls 0x0021042D at 0x002B95E5 and stores the result at +0xB0 (0x002B95F5). The manager constructor zeroes four-byte fields +8/+0xC/+0x10/+0x2C/+0x30 and constructs twelve-byte vector headers at +0x14/+0x20/+0x34 through 0x00211E58. Destructor 0x00210B38 releases those three buffers. SelectPendingBattle 0x0020E794 reads LivingWorldBattle pointers through +0x14/+0x18 and calls LivingWorldBattle::rva003F4831; EnumerateCompletedBattles 0x0020E7E8 passes +0x20/+0x24 elements as void pointers to its callback. The first two vector headers expose their pointer storage; the third remains opaque. Template identities are not inferred from the folded constructor.
// SelectCampaign 0x0020F1F3 selects a pointer at +8 from the +0x34/+0x38 collection. SetActiveBattleID 0x0020E63F writes +0xC and conditionally +0x10. EnumeratePendingBattles 0x0020E7BD reads +0x14/+0x18; EnumerateCompletedBattles 0x0020E7E8 reads +0x20/+0x24. Field names remain neutral because these accesses establish storage and roles, not original names.
// Method names and parameter spellings below follow the matched LivingWorldRegionManager ledger rows. Retail callers additionally prove the int-region overload of GetRegionCenterPoint (0x0020F27E), the typed reinforcement and popup-point signatures (0x0020EEC8/0x0020F2A2), and rva0020FAEA (0x0020FAEA, called at 0x002B286E); these keep their existing caller spellings. All rowed bodies remain out of line.
// Additional ledger entries place rva0020E4C8 at 0x0020E4C8, rva0020E501 at 0x0020E501, rva0020E53D at 0x0020E53D, rva0020E57F at 0x0020E57F, rva0020E5BB at 0x0020E5BB, rva0020E5FD at 0x0020E5FD and rva0020E6C0 at 0x0020E6C0. GetDefaultArmyPlacementPos is at 0x0020EE8F, GetRegionCenterPoint's pointer overload at 0x0020EA58, UpdateBattleMarkers at 0x0020EBA0, ValidateArmyRegionEntry at 0x0020EC99, XferRegions at 0x0020EFA0, rva0020FB8B at 0x0020FB8B, AddBattle at 0x0020FC0F, CheckForBattles at 0x0020FDDF, rva0020E813 at 0x0020E813 and the static INI callback rva00210620 at 0x00210620.
#pragma once

#ifndef __BFME2_LIVINGWORLDREGIONMANAGER_H_
#define __BFME2_LIVINGWORLDREGIONMANAGER_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../Common/RegionTurnObserverView.h"

class LivingWorldLogic;
class LivingWorldBattle;
class LivingWorldPendingBattle;
class PendingBattleVisitor;
class Rva0020E7E8Callback;
class Rva0020E89C;
class Rva00318C32Ret;
class Coord2D;
class AsciiString;
class ModuleData;
class INI;
template<class Char> class StringBase;
struct LivingWorldArmy;
struct Pair8;
struct RegionBattleView;
struct RegionBattlePoint;
namespace _STL {
template<class T> class allocator;
template<class T, class Alloc> class vector;
}

class LivingWorldRegionManager : public Snapshot, public RegionTurnObserverView
{
public:
    LivingWorldRegionManager(LivingWorldLogic *logic);
    virtual ~LivingWorldRegionManager();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
    virtual void BeginTurn(int, int);
    virtual void OnTurnEnding(int, int);

    void SelectCampaign(const StringBase<char> &name);
    void SetActiveBattleID(int key, int value);
    LivingWorldBattle *SelectPendingBattle();
    void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
    void EnumerateCompletedBattles(Rva0020E7E8Callback *visitor);
    void UpdateBattleMarkers();
    void CheckForBattles();
    void XferRegions(Xfer *xfer);
    void AddBattle(RegionBattleView *, const _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > &, const _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > &, const RegionBattlePoint &);
    int ValidateArmyRegionEntry(LivingWorldArmy *, Rva00318C32Ret *, Rva00318C32Ret *, int, int);
    bool GetRegionCenterPoint(Rva0020E89C *, Coord2D *);
    bool GetRegionCenterPoint(int regionID, Coord2D *);
    bool GetRegionUiPopupPoint(int regionID, void *);
    bool GetRegionUiPopupPoint(int regionID, Coord2D *);
    bool GetDefaultArmyPlacementPos(int regionID, Pair8 *);
    void SetRegionReinforcements(int, int, int, int, int, int, int);
    void SetRegionReinforcements(int, const AsciiString &, int, int, int, bool, bool);
    bool rva0020E4C8();
    LivingWorldPendingBattle *rva0020E501(int);
    LivingWorldPendingBattle *rva0020E53D(int);
    LivingWorldPendingBattle *rva0020E57F(unsigned int);
    LivingWorldPendingBattle *rva0020E5BB(int);
    LivingWorldPendingBattle *rva0020E5FD(int);
    LivingWorldPendingBattle *rva0020E6C0();
    bool rva0020E813(RegionBattleView *) const;
    Rva00318C32Ret *rva0020FAEA(const Coord2D *, Rva00318C32Ret *);
    void rva0020FB8B(LivingWorldBattle *);
    static void rva00210620(INI *, void *, void *, const void *);

    void *field08;
    int field0C;
    int field10;
    LivingWorldBattle **field14;
    LivingWorldBattle **field18;
    LivingWorldBattle **field1C;
    void **field20;
    void **field24;
    void **field28;
    int field2C;
    int field30;
    unsigned int field34[3];
};

#endif
