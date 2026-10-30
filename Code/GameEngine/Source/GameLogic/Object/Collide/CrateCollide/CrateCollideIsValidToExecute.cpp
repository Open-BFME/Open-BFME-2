// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?isValidToExecute@CrateCollide@@MBE_NPBVObject@@@Z @0x004BC6C2 288B
// Zero Hour's CrateCollide::isValidToExecute plus BFME 2's ever-executed and
// controller checks; the body after the null test is that test's else block,
// which keeps retail's first shared return-false block.
// Evidence: vtable slot 13 of 5 CrateCollide vtables plus pin plus BFME1 donor CrateCollide_isValidToExecute plus caller Salvage isValidToExecute 0x004BD314.
#include "ascii_string.h"
template <int N> class BitFlags { unsigned char m_storage[0x1C]; };
typedef BitFlags<116> KindOfMaskType;
enum KindOfType { KINDOF_STRUCTURE = 7 };
enum ScienceType { SCIENCE_INVALID = -1 };
class Thing {
public:
	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const;
	bool isAboveTerrain() const;
};
class Player {
public:
	bool hasScience(ScienceType science) const;
	bool rva002AA245() const;
	char m_pad00[0x5C];
	int m_5C;
};
struct ThingTemplate { char m_pad[0x108]; unsigned char m_kindBits[0x10]; };
class Object : public Thing {
public:
	bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	void *getAIUpdateInterface() const { return m_ai; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	unsigned char getIsUndetectedDefector() const { unsigned char s = m_privateStatus; s >>= 1; s = (unsigned char)~s; return s & 1; }
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x258 - 0x08];
	void *m_ai;
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;
};
struct BfmeCrateCollideModuleData {
	char m_pad00[8];
	KindOfMaskType m_kindof;
	KindOfMaskType m_kindofnot;
	bool m_isForbidOwnerPlayer;
	bool m_isBuildingPickup;
	bool m_isHumanOnlyPickup;
	char m_pad43;
	int m_pickupScience;
};
class Object;
class ModuleData;
class Xfer;
struct Coord3D;
struct BfmeCrateCollideModuleData;

class BehaviorModule
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );
	virtual void behaviorModuleAnchor();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class InlineCollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CollideModule : public BehaviorModule, public InlineCollideModuleInterface, public ModuleInterface
{
public:
	// LINK: declaration-only base ctor (no body in this TU). CrateCollide's
	// base-init below E8-calls it; with no local body the call binds the kept
	// (retail) copy instead of this TU's loser copy, and the call bytes are
	// unchanged (same reloc name). No flags touched.
	CollideModule( Thing *thing, const ModuleData *moduleData );
	void xfer(Xfer *xfer);
};

class CrateCollide : public CollideModule
{
public:
	CrateCollide( Thing *thing, const ModuleData *moduleData );

	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual void xfer(Xfer *xfer);
	virtual bool isValidToExecute(const Object *other) const;
	const BfmeCrateCollideModuleData *getCrateCollideModuleData() const { return reinterpret_cast<const BfmeCrateCollideModuleData *>(m_moduleData); }
	Object *getObject() const { return m_object; }

private:
	bool m_everExecuted;			// +0x14, right after the three module bases
};
bool CrateCollide::isValidToExecute(const Object *other) const
{
	if (!other)
		return false;
	else
	{
		if (m_everExecuted)
			return false;
		if (other->isNeutralControlled())
			return false;
		const BfmeCrateCollideModuleData *md = getCrateCollideModuleData();
		bool validBuildingAttempt = md->m_isBuildingPickup && ((other->m_template->m_kindBits[0] & 0x80) != 0);
		if (other->getAIUpdateInterface() == 0 && !validBuildingAttempt)
			return false;
		if ((other->m_template->m_kindBits[0x15] & 0x40) != 0) {
			Player *ctrl = other->getControllingPlayer();
			if (ctrl == 0)
				return false;
			if (!ctrl->rva002AA245())
				return false;
		}
		if (!other->isKindOfMulti(md->m_kindof, md->m_kindofnot))
			return false;
		if (other->isEffectivelyDead())
			return false;
		if (getObject()->isAboveTerrain() && !validBuildingAttempt)
			return false;
		if (md->m_isForbidOwnerPlayer && getObject()->getControllingPlayer() == other->getControllingPlayer())
			return false;
		if (md->m_isHumanOnlyPickup && other->getControllingPlayer() != 0 && other->getControllingPlayer()->m_5C != 0)
			return false;
		if (md->m_pickupScience != SCIENCE_INVALID && other->getControllingPlayer() != 0 && !other->getControllingPlayer()->hasScience((ScienceType)md->m_pickupScience))
			return false;
		return getObject()->getIsUndetectedDefector();
	}
}
