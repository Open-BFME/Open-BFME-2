// cl: /MD /GX
//
// AIPlayer::isLocationSafe, retail 0x004F08A8, 295 bytes (caller 0x004F2C0B,
// beside the matched checkForSupplyCenter 0x004F29E9 in AIPlayer.cpp, which
// is built without /arch:SSE). Zero Hour's body over BFME2's linked filters
// (built inner first): no enemy within the AI data's supply-centre safe
// radius (+0x84) plus the template's bounding radius (+0xB0) that is not an
// ally or neutral (relationship flags 10), alive, passes the player filter
// in place of Zero Hour's stealth one, is significant, and is neither a
// kind-14 (harvester) nor a kind-16 (dozer) object.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// Opaque target view: allow 0x00261246 dispatches through slots +0x10 and
// +0x114 of the object stored at Object+0x250. The slot meanings remain
// address-derived; this declaration only fixes the observed ABI.
class Rva00261246SubobjectView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual bool slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual int slot69(int arg) = 0;
};

class Object
{
public:
	bool isStructure() const;
	int isNonFactionStructure() const;
	char m_pad000[0x250];
	Rva00261246SubobjectView *m_250;
	char m_pad254[4];
	int m_258;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00C1A268, allow 0x0026115D: reject objects satisfying the
// set/clear masks (ZH's PartitionFilterRejectByKindOf).
class PartitionFilterRejectByKindOf : public Rva000421C8
{
public:
	PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
#include "../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	Rva00261058(Player *player, bool flag) : m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00C07160, allow 0x00261246: two flags (Zero Hour's
// PartitionFilterInsignificantBuildings(allowNonBuildings, allowInsignificant)).
class Rva00261246Filter : public Rva000421C8
{
public:
	Rva00261246Filter(bool allowNonBuildings, bool allowInsignificant) : m_a(allowNonBuildings), m_b(allowInsignificant) {}
	virtual bool allow(Object *obj);
	unsigned char m_a;
	unsigned char m_b;
};

// Target identity: slot 1 of the pinned 0x00807160 filter vtable, also
// constructed inline by AIPlayer::isLocationSafe at 0x004F08A8. Object
// offsets and the +0x10/+0x114 dispatches below come from this retail body.
// The Zero Hour PartitionFilterInsignificantBuildings name is donor evidence.
bool Rva00261246Filter::allow(Object *obj)
{
	if ((unsigned char)obj->isStructure() != 0) {
		if ((unsigned char)obj->isNonFactionStructure() == 0)
			goto ret_true;
		if (m_b)
			goto ret_true;
		if (obj->m_258 != 0)
			goto ret_true;
		Rva00261246SubobjectView *subobject = obj->m_250;
		if (subobject != 0) {
			if (subobject->slot04()) {
				if (subobject->slot69(0) != 0)
					goto ret_true;
			}
			goto ret_false;
		}
		goto ret_true;
	ret_false:
		return false;
	ret_true:
		return true;
	}
	return m_a;
}

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class ThingTemplate
{
public:
	float getBoundingCircleRadius() const { return m_boundingRadius; }
	char m_pad000[0xB0];
	float m_boundingRadius;		// +0xB0
};

#include "../../../Include/GameLogic/TAiData.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

enum DistanceCalculationType
{
	FROM_BOUNDINGSPHERE_2D = 3
};

#include "../../../Include/GameLogic/AIPlayerClass.h"

bool AIPlayer::isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing)
{
	if (tthing == 0)
		return false;

	float radius = TheAI->getAiData()->m_supplyCenterSafeRadius;
	radius += tthing->getBoundingCircleRadius();

	Object *enemy = ThePartitionManager->getClosestObject(pos, radius, FROM_BOUNDINGSPHERE_2D,
		Rva00261409Filter(m_player, false, 10)
			.link(Rva0026119DFilter()
			.link(Rva00261058(m_player, false)
			.link(Rva00261246Filter(true, false)
			.link(PartitionFilterRejectByKindOf(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 16),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
			.link(&PartitionFilterRejectByKindOf(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 14),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)))))));
	if (enemy != 0)
		return false;
	return true;
}
