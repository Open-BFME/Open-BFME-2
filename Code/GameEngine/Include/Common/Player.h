#pragma once
// Target Player ABI: ctor RVA 2B0F3C and dtor 2B11A7 install
// BFDF3C at +0, BFDF30 at +4, BFDF18 at +8. Allocation 2A7FBF
// is 0x758. Primary slots 4..7 are the matched AI delegates.
// Unknown member storage remains opaque; no donor layout is imported.
// Mixing Snapshot spelling variants would introduce extra primary slots.
#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error Player requires the Snapshot name-slot surface before first inclusion
#endif
#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT)
#error Player requires Snapshot loadPostProcess, const GetSnapshotName, xfer slots
#endif
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Source/Common/Rva00380200.h"
class Player;
class AIPlayer;
class Object;
class Waypoint;
class SpecialPowerTemplate;
class CreateAHeroData;
struct Coord3D;
enum ObjectID;
enum ScienceType;
// Structural name retained from the matched constructor. The original base
// identity is unknown. Table BE2B78 is three pure slots; Player's BFDF30
// contains 2B118A (this-4 to hasScience), 30D377 (Player+0x24 integer getter),
// and 2B1192 (this-4 to rva002AB855, AL stored through second argument).
class Rva002B0F3CIface {
public:
 virtual bool v0(ScienceType) const = 0;
 virtual int v1() const = 0;
 virtual void v2(CreateAHeroData *, bool *) const = 0;
};
class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200 {
public:
 Player(int);
 virtual ~Player();
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);
 virtual void computeSuperweaponTarget(const SpecialPowerTemplate *, Coord3D *, int, float);
 virtual bool checkBridges(Object *, Waypoint *);
 virtual bool getAiBaseCenter(Coord3D *);
 virtual void repairStructure(ObjectID);
 // Secondary-table overrides; names are structural, not recovered identities.
 virtual bool v0(ScienceType) const;
 virtual int v1() const;
 virtual void v2(CreateAHeroData *, bool *) const;
 virtual bool rva0038037C(int);
 virtual void rslot02(int);
 virtual void rslot03();
 virtual void rslot04(const void *);
 virtual bool rslot05();
 void onUnitCreated(Object *, Object *);
 bool rva002A9CA4(int);
 int getPlayerIndex() const { return m_playerIndex; }
 bool isLocalPlayer() const;
 bool isSkirmishAIPlayer();
 bool rva002A9CB8();
private:
 unsigned char m_opaque34[0x54 - 0x34];
 int m_playerIndex; // constructor 2B0F94/97 stores the int argument at +54
 unsigned char m_opaque58[0x2DC - 0x58];
 AIPlayer *m_ai; // retail delegates use +0x2DC
 unsigned char m_opaque2E0[0x758 - 0x2E0];
};
typedef char PlayerCanonicalSizeCheck[sizeof(Player) == 0x758 ? 1 : -1];
