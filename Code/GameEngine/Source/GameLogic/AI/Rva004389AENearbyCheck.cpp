// cl: /MD /GX
//
//   0x004388E3  true when the third argument's +0x1C mask
//               meets the object's +0x284 mask, an alive object of kind 94
//               lies within 50 of the position (the partition filter chain
//               AIStructureCreepTactic.cpp documents), or TheTerrainLogic's
//               0x0027F108 finds something within 50 of it
//   0x004389AE  the same test, taken only when the third argument's +0x9C or +0x00
//               bit 0 is set (both REL32 in 0x004D990E with ECX the
//               TheGameLogic +0x178 member)
//   0x0043912F  whether an object other than this one, alive, passing
//               0x002614DF and 0x0026118B, of the TheGlobalData +0xEB4
//               object filter for the object's player and relationship 4
//               (the third argument's +0x9C bit 1) or 1 to it lies within its
//               template radius times the third argument's +0x14 scale of the
//               position (searched within this +0x10 times that scale, 3D
//               distance); its ID goes to the fourth argument when given

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C17F08, allow 0x0026118B: no members of its own.
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};


#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);	// 0x00406F9C
private:
	unsigned m_data[32];
};

#include "../../../Include/Common/ThingTemplate.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_74;			// +0x74 the ID
	char m_pad078[0x284 - 0x78];
	unsigned m_284[32];		// +0x284
	char m_pad304[0x438 - 0x304];
	unsigned char m_438;		// +0x438
};

#include "../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

// Native 0x27F108 takes four 32-bit argument slots and returns the result
// word at temporary+0x14. The caller only tests that full word for zero.
// Reuse the verified provider contract; no pointer-result identity is assumed.
class BfmeThingCME
{
public:
	int rva0027F108(void *position, float radius, int flag, int unused);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct Rva004388E3Template
{
	unsigned char m_00;		// +0x00 bit 0
	char m_pad01[0x14 - 0x01];
	float m_scale;			// +0x14 the scale
	char m_pad18[0x1C - 0x18];
	Rva00406F9C m_kindOfMask;		// +0x1C
	unsigned char m_9C;		// +0x9C bits 0 and 1
};


#include "../../../Include/Common/GlobalData.h"
extern class GlobalData *TheWritableGlobalData;

class Rva004389AE
{
public:
	bool rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate);
	bool rva004389AE(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate);
	bool rva0043912F(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate, ObjectID *out);
private:
	char m_pad00[0x10];
	float m_10;		// +0x10 the scale
};

bool Rva004389AE::rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate)
{
	if (checkTemplate->m_kindOfMask.rva00406F9C(obj->m_284))
		return true;

	Object *other = ThePartitionManager->getClosestObject(pos, 50.0f, 0,
		Rva0026119DFilter().link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 94),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)));
	if (other && !other->isEffectivelyDead())
		return true;

	return reinterpret_cast<BfmeThingCME *>(TheTerrainLogic)->rva0027F108(
		const_cast<Coord3D *>(pos), 50.0f, 1, 0) ? true : false;
}

bool Rva004389AE::rva004389AE(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate)
{
	if (((checkTemplate->m_9C & 1) || (checkTemplate->m_00 & 1)) && rva004388E3(obj, pos, checkTemplate))
		return true;
	return false;
}

bool Rva004389AE::rva0043912F(Object *obj, const Coord3D *pos, Rva004388E3Template *checkTemplate, ObjectID *out)
{
	int flags = (checkTemplate->m_9C & 2) ? 4 : 1;
	Rva002614DFFilter notThis(obj);
	Rva0026119DFilter alive;
	Rva0026118BFilter third;
	Rva002611BFFilter notSelf(obj);
	Rva002614ECFilter same(&TheWritableGlobalData->m_camouflageDetectorObjectFilter, obj->getControllingPlayer(), true);
	Rva00260EB1Filter relationship(obj, flags, true);
	notThis.link(&alive);
	notThis.link(&third);
	notThis.link(&notSelf);
	notThis.link(&same);
	notThis.link(&relationship);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos,
		m_10 * checkTemplate->m_scale, 2, &notThis, 0);
	Object *other;
	while ((other = hits.next()) != 0) {
		float radius = other->m_template->m_camouflageDetectionMultiplier * checkTemplate->m_scale;
		float dx = pos->x - other->m_pos.x;
		float dy = pos->y - other->m_pos.y;
		float dz = pos->z - other->m_pos.z;
		if (dx * dx + dy * dy + dz * dz < radius * radius) {
			if (out)
				*out = other->m_74;
			return true;
		}
	}
	return false;
}
