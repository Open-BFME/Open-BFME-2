// LivingWorldPlayer: canonical BFME2 declaration.
// Target facts (code addresses are RVAs; tables and strings are VAs):
// Constructors 0x002E277A/393 and 0x002E2903/427, still rowed as Rva002E2AAE, install 0x00C04B50 at +0 (0x002E27A4 and 0x002E2925). Destructor 0x002E2AAE/257 installs the same table at 0x002E2AC1, then restores Snapshot's 0x00BBB554 at 0x002E2BA1. The latter table describes base destruction, not another LivingWorldPlayer layout. The stores at +0x258/+0x274 at 0x002E2B15/0x002E2B1B destroy embedded RegionBonusInfo snapshots.
// Table 0x00C04B50 has four slots: deleting destructor 0x002E2CF4 (calls 0x002E2AAE), loadPostProcess 0x002E07CC, GetSnapshotName 0x002E07C6 (returns "LivingWorldPlayer" at 0x00C04920), and xfer 0x002E30C8. Text begins at 0x00C04B60. These slots agree with the registered Snapshot name-slot profile. Lifetime and virtual providers retain the Rva002E2AAE ledger spelling; this header declares them without emitting replacement bodies.
// Allocations at 0x002BA955/0x002BA95A and 0x002BAAB5/0x002BAABA request 0x3C8 bytes before constructors 0x002E2903/0x002E277A. Constructor calls at +4 reach the nonpolymorphic 0x10-byte listener storage constructor 0x00330757. Its original base/template identity is unresolved, so its storage remains opaque.
// Constructors put the player ID at +0x14, LWPlayerDef at +0x18, a context pointer at +0x40, kind at +0x44, AsciiString at +0x48, and LivingWorldAI at +0x4C. LWPlayerDef's 0x002E0F1E destructor releases its UnicodeString at +4 and four AsciiStrings; the player's UnicodeString therefore lies at +0x1C. Player destructor calls 0x00036410 at +0x48/+0x1B4 (0x002E2B75/0x002E2B4B).
// Constructor 0x002E277A initializes three float triplets at +0x184/+0x190/+0x19C, twelve-byte vector headers at +0x1A8/+0x1B8/+0x1CC, scalar +0x1C4, float +0x1C8, and 128-byte storage +0x1D8. SetColorIndex 0x002E0F91 proves the RGB triplets; rva002E12F3 0x002E12F3 and GetRevivalUnitData 0x002E1451 prove the +0x1A8 vector's 0xD8-byte UnitRevivalEntry records. RemoveArmy 0x002E10FE and rva002E0B76 0x002E0B76 prove pointer-vector access at +0x1B8. The three-word storage declarations preserve these extents without imposing a container-library profile on declaration-only consumers.
// Constructor calls place RegionBonusInfo at +0x258/+0x274, tree headers at +0x29C/+0x2A8, and LivingWorldScoreKeeper at +0x2C8 (0x002E2863..0x002E28BD). Stores at 0x002E2883..0x002E288F and 0x002E28AD initialize +0x290/+0x294/+0x298/+0x2C4; 0x002E28CF/0x002E28D5 initialize byte flags +0x3C4/+0x3C5. Unexposed member storage stays opaque. GetConflictResolveType 0x002E0699 reads kind +0x44 and +0x2B4; OnUnitDequeued 0x002E0764 updates +0x298; AddUpgrade/RemoveUpgrade 0x002E1588/0x002E15BC address the +0x1D8 mask.
// Nonvirtual method declarations preserve the LivingWorldPlayer ledger rows: 0x002E06B8/0x002E06EF, 0x002E0699, 0x002E0764, 0x002E0B30/0x002E0B76, 0x002E0F91, 0x002E1001, 0x002E10FE, 0x002E1155/0x002E118E, 0x002E1257/0x002E12F3, 0x002E1451/0x002E14E9, 0x002E1588/0x002E15BC, 0x002E199E, 0x002E1D22/0x002E1FC2, 0x002E2225/0x002E246D, 0x002E2D8D/0x002E2F44, and 0x002E3442/0x002E3518. Pointer and record view spellings do not assert original argument identities. No Zero Hour LivingWorldPlayer declaration is available in the local donor tree.

#ifndef BFME2_LIVING_WORLD_PLAYER_H
#define BFME2_LIVING_WORLD_PLAYER_H

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER) || defined(BFME_SNAPSHOT_CONSTRUCTOR_ONLY)
#error LivingWorldPlayer requires the complete native Snapshot profile
#endif
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

namespace _STL {
template<class T> class allocator;
template<class T, class A> class vector;
}

class INI;
class GameSlot;
class SpawnArmy;
class ThingTemplate;
class Rva00318C32Ret;
struct LivingWorldArmy;
struct LivingWorldRevivalUnitDataView;
struct BfmeFixedStorage128;
struct Rva002E2690Element;
struct RevivalSourceView;
struct Rva002BA8F1Input;

class LivingWorldPlayer : public Snapshot
{
public:
    LivingWorldPlayer();
    LivingWorldPlayer(Rva002BA8F1Input *input, void *context);
    virtual ~LivingWorldPlayer();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    GameSlot *rva002E06B8();
    void *rva002E06EF();
    int GetConflictResolveType();
    void OnUnitDequeued(SpawnArmy *unit);
    bool rva002E0B30();
    bool rva002E0B76(Rva00318C32Ret *region);
    void SetColorIndex(int color);
    int GetNumRegionsOwned();
    void **RemoveArmy(void **&iter);
    bool rva002E1155(SpawnArmy *unit);
    bool HasArmyQueuedInAnyBuilding(void *key, int *outBuildingID, int excludedBuildingID);
    void *FindArmyWithHero(void *thing, int key);
    bool rva002E12F3(int key);
    void GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out);
    void rva002E14E9(const BfmeFixedStorage128 &mask);
    void AddUpgrade(void *upgrade, bool persistentOnly);
    void RemoveUpgrade(void *upgrade);
    int rva002E199E(const void *thing);
    static void ParseLivingWorldPlayer(INI *ini, void *instance);
    void CheckForRemovedMultiRegionBonuses();
    void RemoveRevivalUnit(int key);
    void AddArmy(LivingWorldArmy *army);
    void MarkUnitsForUpgrades(void *region);
    void ExtractRevivalUnitDataForCurrentMap(_STL::vector<Rva002E2690Element, _STL::allocator<Rva002E2690Element> > *out);
    void rva002E3442(const RevivalSourceView *const *source, const ThingTemplate *thing, int key);
    void InitBuildableHeroes();

    char field04[0x10];
    int m_14;
    char field18[4];
    UnicodeString field1C;
    char field20[0x20];
    void *field40;
    int field44;
    AsciiString field48;
    char field4C[0x134];
    int field180;
    RGBColor field184;
    RGBColor field190;
    RGBColor field19C;
    unsigned int field1A8[3];
    AsciiString field1B4;
    unsigned int field1B8[3];
    int field1C4;
    float field1C8;
    unsigned int field1CC[3];
    unsigned int field1D8[32];
    char field258[0x40];
    int field298;
    char field29C[0x18];
    int field2B4;
    char field2B8[0x10C];
    bool field3C4;
    bool field3C5;
    char field3C6[2];
};

#endif
