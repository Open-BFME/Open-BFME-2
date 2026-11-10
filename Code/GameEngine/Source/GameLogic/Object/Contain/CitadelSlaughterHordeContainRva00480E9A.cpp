// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?rva00480E9A@CitadelSlaughterHordeContain@@UAEXPAVObject@@@Z, retail 0x00480E9A, 328 bytes.
// Slot 32 of ??_7CitadelSlaughterHordeContain 0x00C48CC0 (SlaughterHordeContain's
// own slot 32 is the empty default 0x0047A69C; slot 33 is the rowed 0x004807C7).
// For the object handed in: idle its AI with the source its slot 143 reports,
// drop its AiOrdersManager orders, set the module data's +0xEC status bits on
// it when any are set, destroy the object closest to the citadel that passes
// the 0x002614EC filter over the data's +0xFC and the object's controlling
// player, grant the data's +0x100 upgrades to the citadel (player upgrades
// through the citadel's controlling player), play the +0x10C FX on the
// citadel, and remember the object's ID at +0x9EC (the ID the rowed
// CitadelSlaughterHordeContain::update consumes).
//
// Evidence (target): the vftable slot, every call (all rowed), the filter's
// vftable 0x00BCECF0 and its base 0x00BC26E0 restored after the query (the
// filter view CivilianSpawnUpdateUpdate.cpp and ModelConditionSpecialAbility
// use), the search radius read from .data 0x009C9EB4 (only this body reads
// it). Method identity is not established; the name stays address-derived.

#include <vector>
#include "ascii_string.h"

class Object;
class Player;
class FXList;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../../Common/GameLogicObjectLookupView.h"

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_NOT_AVAILABLE = 1,
	UPGRADE_STATUS_COMPLETE = 2
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

namespace _STL
{
template <unsigned N> struct _Base_bitset;
template <> struct _Base_bitset<4>
{
	bool _M_is_any() const;
	unsigned int _M_w[4];
};
}

class Rva00346BC0
{
public:
	bool any() const { return m_bits._M_is_any(); }
private:
	_STL::_Base_bitset<4> m_bits;
};

#include "../../../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

class Upgrade;
#include "../../../../Include/Common/Player.h"

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class AIUpdateInterfaceVtbl
{
public:
	SLOT08(v00,v01,v02,v03,v04,v05,v06,v07)
	SLOT08(v08,v09,v0A,v0B,v0C,v0D,v0E,v0F)
	SLOT08(v10,v11,v12,v13,v14,v15,v16,v17)
	SLOT08(v18,v19,v1A,v1B,v1C,v1D,v1E,v1F)
	SLOT08(v20,v21,v22,v23,v24,v25,v26,v27)
	SLOT08(v28,v29,v2A,v2B,v2C,v2D,v2E,v2F)
	SLOT08(v30,v31,v32,v33,v34,v35,v36,v37)
	SLOT08(v38,v39,v3A,v3B,v3C,v3D,v3E,v3F)
	SLOT08(v40,v41,v42,v43,v44,v45,v46,v47)
	SLOT08(v48,v49,v4A,v4B,v4C,v4D,v4E,v4F)
	SLOT08(v50,v51,v52,v53,v54,v55,v56,v57)
	SLOT08(v58,v59,v5A,v5B,v5C,v5D,v5E,v5F)
	SLOT08(v60,v61,v62,v63,v64,v65,v66,v67)
	SLOT08(v68,v69,v6A,v6B,v6C,v6D,v6E,v6F)
	SLOT08(v70,v71,v72,v73,v74,v75,v76,v77)
	SLOT08(v78,v79,v7A,v7B,v7C,v7D,v7E,v7F)
	SLOT08(v80,v81,v82,v83,v84,v85,v86,v87)
	virtual void v88(); virtual void v89(); virtual void v8A(); virtual void v8B();
	virtual void v8C(); virtual void v8D(); virtual void v8E();
	virtual CommandSourceType rva143();
	unsigned char m_pad04[0x20 - 0x04];
};


#include "../object.h"

#include "../../../../Include/GameLogic/AiOrdersManager.h"
extern AiOrdersManager *TheAiOrdersManager;

extern GameLogic *TheGameLogic;

// BFME2's partition filter chain (the view CivilianSpawnUpdateUpdate.cpp uses).
#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
#include "../../../../Include/GameLogic/Rva002614ECFilter.h"

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

// The closest-enemy search range (.data VA 0x00DC9EB4, retail value 9999.0f);
// no unit defined it, so its only user does.
extern float g_00DC9EB4;
float g_00DC9EB4 = 9999.0f;

struct CitadelSlaughterHordeContainModuleData
{
	unsigned char m_pad00[0xEC];
	Rva00346BC0 m_statusToSet;                  // +0xEC
	unsigned char m_filterWhat[4];              // +0xFC
	_STL::vector<AsciiString> m_upgrades;       // +0x100
	const FXList *m_fx;                         // +0x10C
};

class SlaughterHordeContain
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	virtual void rva00480E9A(Object *obj);
	virtual bool rva004807C7(Object *obj);
protected:
	const CitadelSlaughterHordeContainModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
	const CitadelSlaughterHordeContainModuleData *m_moduleData; // +0x04
	Object *m_object;                                           // +0x08
	unsigned char m_pad0C[0x9EC - 0x0C];
};

class CitadelSlaughterHordeContain : public SlaughterHordeContain
{
public:
	virtual void rva00480E9A(Object *obj);
private:
	ObjectID m_9EC;
};

// ?rva00480E9A@CitadelSlaughterHordeContain@@UAEXPAVObject@@@Z @0x00480E9A
void CitadelSlaughterHordeContain::rva00480E9A(Object *obj)
{
	AIUpdateInterface *ai = obj->getAI();
	Object *me = getObject();
	ai->aiIdle(ai->vslot143());
	TheAiOrdersManager->rva003551D3(obj->getID());

	const CitadelSlaughterHordeContainModuleData *citadelSlaughterHordeContainModuleData = getModuleData();
	if (citadelSlaughterHordeContainModuleData->m_statusToSet.any())
		obj->rva0028CDEB(citadelSlaughterHordeContainModuleData->m_statusToSet, false);

	Object *closest = ThePartitionManager->getClosestObject(me->getPosition(), g_00DC9EB4, 3,
		&Rva002614ECFilter(citadelSlaughterHordeContainModuleData->m_filterWhat, obj->getControllingPlayer(), true));
	if (closest)
		TheGameLogic->destroyObject(closest);

	if (citadelSlaughterHordeContainModuleData->m_upgrades.size() > 0)
	{
		for (_STL::vector<AsciiString>::const_iterator it = citadelSlaughterHordeContainModuleData->m_upgrades.begin(); it != citadelSlaughterHordeContainModuleData->m_upgrades.end(); ++it)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(*it);
			if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER)
				me->getControllingPlayer()->addUpgrade(upgrade, UPGRADE_STATUS_COMPLETE, 0);
			else
				me->rva00293077(upgrade);
		}
	}

	const FXList *fx = citadelSlaughterHordeContainModuleData->m_fx;
	if (fx)
		FXList::doFXObj(fx, me, 0);

	m_9EC = obj->getID();
}
