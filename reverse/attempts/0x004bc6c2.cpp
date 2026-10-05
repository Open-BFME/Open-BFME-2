// ?isValidToExecute@CrateCollide@@MBE_NPBVObject@@@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?isValidToExecute@CrateCollide@@MBE_NPBVObject@@@Z @0x004BC6C2 288B
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
	char m_pad00[0x5C];
	int m_5C;
};
class Rva002AA245MovzxByteChaseField {
public:
	unsigned int get() const;
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
class CrateCollide {
public:
	virtual ~CrateCollide();
protected:
	virtual bool isValidToExecute(const Object *other) const;
	const BfmeCrateCollideModuleData *getCrateCollideModuleData() const { return *(const BfmeCrateCollideModuleData *const *)((const char *)this + 0x04); }
	Object *getObject() const { return *(Object *const *)((const char *)this + 0x08); }
	const void *m_moduleData;
	Object *m_object;
	char m_pad0C[0x14 - 0x0C];
	bool m_everExecuted;
};
bool CrateCollide::isValidToExecute(const Object *other) const
{
	if (!other)
		return false;
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
		if ((unsigned char)((const Rva002AA245MovzxByteChaseField *)ctrl)->get() == 0)
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
