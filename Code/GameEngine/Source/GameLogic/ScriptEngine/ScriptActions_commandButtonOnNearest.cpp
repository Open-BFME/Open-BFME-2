// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// BFME2 script actions: a named unit uses a command button on the nearest
// enemy (the unit's controlling player, relationship flags 4) of some kind.
// Each resolves the unit (getUnitNamed 0x003588E7) and the button
// (ControlBar::findCommandButton 0x0031BE3C), requires CommandButton::isReady
// and the unit's 0x002922D9 gate, then searches from the unit's position and
// hands the hit to the unit (0x00297000 with the object, or 0x00297149 with
// its position when the button's +0x1C bit 5 is set), source 1. Zero Hour
// has the team versions (doTeamUseCommandButtonOnNearest*); these named
// ones are BFME2's, so the names stay address-derived. All are called from
// the action dispatcher 0x003CA4BE.
//
//   0x003BD905  none of kinds 54, 89, 130
//   0x003BDB03  kind 7 and the 0x0026144C(true) filter (Zero Hour's
//               Garrisonable in doTeamUseCommandButtonOnNearestGarrisonedBuilding)
//   0x003BDC65  the given kind
//   0x003BDE5D  kind 7 (Zero Hour's ...OnNearestBuilding)
//   0x003BDFA5  kind 7 and the given kind (...OnNearestBuildingClass)
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1). Retail updates the unwind state only after the kind filters
// are built, so the bitset and kind-filter ctors are declared throw() here.
#include <string.h>
#include "ascii_string.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

class CommandButton;

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva003BD905Mask
{
	Rva003BD905Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00C1FE34, allow 0x002614BC: +0x08 the source object, +0x0C the
// command button, +0x10 whether a valid target allows, +0x14 the command
// source (Zero Hour's PartitionFilterValidCommandButtonTarget).
class Rva002614BCFilter : public Rva000421C8
{
public:
	Rva002614BCFilter(Object *source, const CommandButton *button, bool match, int cmdSource)
		: m_source(source), m_button(button), m_match(match), m_cmdSource(cmdSource) {}
	virtual bool allow(Object *obj);
	Object *m_source;
	const CommandButton *m_button;
	bool m_match;
	int m_cmdSource;
};

// vftable 0x00C1FE04, allow 0x0026144C: +0x08 a flag (Zero Hour's
// PartitionFilterGarrisonable in the matching team action).
class Rva0026144CFilter : public Rva000421C8
{
public:
	Rva0026144CFilter(bool match) : m_match(match) {}
	virtual bool allow(Object *obj);
	bool m_match;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Coord3D;

class Object
{
public:
	Player *getControllingPlayer() const;						// 0x0028AFA9
	bool rva002922D9(const CommandButton *button);					// 0x002922D9
	void rva00297000(const CommandButton *button, Object *target, int source, int flags);	// 0x00297000
	void rva00297149(const CommandButton *button, const Coord3D *pos, int source, int flags);	// 0x00297149
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
};

class CommandButton
{
public:
	bool isReady(const Object *obj) const;	// 0x0035B069
	bool rva003BDCCA() const { return (m_options >> 5) & 1; }
	char m_pad00[0x1C];
	unsigned int m_options;	// +0x1C
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);	// 0x003588E7
};
extern ScriptEngine *TheScriptEngine;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
public:
	void rva003BDB03(const AsciiString &unitName, const AsciiString &ability);
	void rva003BD905(const AsciiString &unitName, const AsciiString &ability);
	void rva003BDC65(const AsciiString &unitName, const AsciiString &ability, int kindofBit);
	void rva003BDFA5(const AsciiString &unitName, const AsciiString &ability, int kindofBit);
	void rva003BDE5D(const AsciiString &unitName, const AsciiString &ability);
};

void ScriptActions::rva003BD905(const AsciiString &unitName, const AsciiString &ability)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(ability);
	if (!button)
		return;
	if (!obj->rva002922D9(button))
		return;
	if (!button->isReady(obj))
		return;
	Rva003BD905Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (button->rva003BDCCA()) {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261409Filter(obj->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
					*(BfmeFixedStorage0004543D *)&mask)
					.link(&Rva002611BFFilter(obj))));
		if (target)
			obj->rva00297149(button, target->getPosition(), 1, 0);
	} else {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261409Filter(obj->getControllingPlayer(), true, 4)
				.link(Rva002614BCFilter(obj, button, true, 1)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
						*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(obj)))));
		if (target)
			obj->rva00297000(button, target, 1, 0);
	}
}

void ScriptActions::rva003BDB03(const AsciiString &unitName, const AsciiString &ability)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(ability);
	if (!button)
		return;
	if (!button->isReady(obj))
		return;
	if (!obj->rva002922D9(button))
		return;
	Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
		Rva00261409Filter(obj->getControllingPlayer(), true, 4)
			.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(Rva0026144CFilter(true).link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj))))));
	if (target)
		obj->rva00297000(button, target, 1, 0);
}

void ScriptActions::rva003BDC65(const AsciiString &unitName, const AsciiString &ability, int kindofBit)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(ability);
	if (!button)
		return;
	if (!button->isReady(obj))
		return;
	if (!obj->rva002922D9(button))
		return;
	if (button->rva003BDCCA()) {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261409Filter(obj->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
					*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
					.link(&Rva002611BFFilter(obj))));
		if (target)
			obj->rva00297149(button, target->getPosition(), 1, 0);
	} else {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261409Filter(obj->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
					*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
					.link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj)))));
		if (target)
			obj->rva00297000(button, target, 1, 0);
	}
}

void ScriptActions::rva003BDE5D(const AsciiString &unitName, const AsciiString &ability)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(ability);
	if (!button)
		return;
	if (!button->isReady(obj))
		return;
	if (!obj->rva002922D9(button))
		return;
	Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
		Rva00261409Filter(obj->getControllingPlayer(), true, 4)
			.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj)))));
	if (target)
		obj->rva00297000(button, target, 1, 0);
}

void ScriptActions::rva003BDFA5(const AsciiString &unitName, const AsciiString &ability, int kindofBit)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(ability);
	if (!button)
		return;
	if (!button->isReady(obj))
		return;
	if (!obj->rva002922D9(button))
		return;
	Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
		Rva00261409Filter(obj->getControllingPlayer(), true, 4)
			.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
					*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
					.link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj))))));
	if (target)
		obj->rva00297000(button, target, 1, 0);
}
