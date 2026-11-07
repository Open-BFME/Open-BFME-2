// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
#define BFME_SNAPSHOT_NAME_SLOT
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Thing;
class Player;
class ModuleData;
class Module;
class UpgradeTemplate;
class CastleUpgrade;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
	friend class CastleUpgrade;

public:
	void rva00293003(const void *upgrade);
	void rva00293077(const void *upgrade);
	Player *getControllingPlayer() const;
	char pad00[0x38]; Coord3D m_position; // rowed: applies the upgrade to the object's upgrade modules

protected:
	Module *findModule(NameKeyType key) const;
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA(); // rowed pool-key getter
};

// Castle-side behaviour found under CastleBehavior's key; 0x00397357 grants it the upgrade.
// Module found under "CastleMemberBehavior": the owning castle's ID at +0x18 (retail-measured).
struct CastleMemberBehaviorView
{
	unsigned char m_pad00[0x18];
	ObjectID m_castleID; // +0x18
};

#include "../../../../Include/GameLogic/Module/CastleUpgradeModuleData.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


// The class is CastleUpgrade.h's, over the canonical UpgradeModule.h (retail's
// table facts are there); BFME_SNAPSHOT_NAME_SLOT is defined before the first
// Snapshot.h include above.
#include "../../../../Include/GameLogic/Module/CastleUpgrade.h"

// BFME1 CastleUpgradeImplementation donor874e38488 supplies upgrade grant
// semantics; the target's additional radius pass is proven by 4B68B6 and
// its primary-this call at4B6A28. Partition helper interfaces and 28-byte
// masks follow the independently verified providers in BFME2.
struct Rva0006EE7A { unsigned int words[7]; Rva0006EE7A(int,int,int,int,int); };
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../../Include/GameLogic/PartitionFilter.h"
class Rva003959FA : public Rva000421C8
{
public:
 Rva003959FA(const BfmeFixedStorage0004543D &);
 virtual ~Rva003959FA() {}
 virtual bool allow(Object *);
 BfmeFixedStorage0004543D mask;
};
extern PartitionManager *ThePartitionManager;
void CastleUpgrade::rva004B68B6(const UpgradeTemplate *upgrade)
{
 Object *object = getObject();
 if (!object) return;
 const CastleUpgradeModuleData *data = getCastleUpgradeModuleData();
 if (!data) return;
 Rva0006EE7A mask(0,0xBD,0x9C,0x96,0x3D);
 BfmeWideResult result = ThePartitionManager->iterateObjectsInRange(
  &object->m_position,data->m_radius,1,
  &Rva003959FA(*(const BfmeFixedStorage0004543D *)&mask),0);
 Object *other = result.next();
 if (other) do
 {
  if (object->getControllingPlayer()==other->getControllingPlayer()) other->rva00293077(upgrade);
 } while ((other = result.next()) != 0);
}

CastleUpgrade::CastleUpgrade(Thing *thing, const ModuleData *moduleData)
 : UpgradeModule(thing, moduleData) {}

// The Xfer operand types (AsciiString is ascii_string.h's, above).
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

// ?xfer@CastleUpgrade@@MAEXPAVXfer@@@Z: slot 3 of 0x00C58880 is 0x004B8710,
// version 1 then UpgradeModule's xfer; retail folds the body with
// ArmorUpgrade::xfer (ArmorUpgradeXfer.cpp).
void CastleUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpgradeModule::xfer(xfer);
}
