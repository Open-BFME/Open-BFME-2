// ?rva0027B18C@Drawable@@QAEXPBUDamageInfo@@@Z
// partial score=0.85 date=2026-10-10
// NEAR (score ~0.85): ?rva0027B18C@Drawable@@QAEXPBVDamageInfo@@@Z retail 0x0027B18C 755 bytes
// (Drawable damage Eva/radar handler; WB twin 0x00CB7E40; caller 0x00296065 at 0x002965F6).
// Structure frame EH states and all calls line up (757 vs 755 bytes). Remaining:
// esi/edi swapped between the this->template chain (retail esi) and the
// DamageInfo/damage type/alt-event chain (retail edi); the first source null
// test is cmp [ebp+8],0 then mov ecx where retail loads ecx and tests it (2 bytes).
// Needs pin ?tryUnderAttackEvent@Radar@@QAEXPBVObject@@@Z=0x002D8B9D (log name).
// Filter vtable 0x00BFAF88 has no ledger name. Target file would be
// Code/GameEngine/Source/GameClient/Drawable_rva0027B18C.cpp
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord3D.h"

class Object;
class Player;
class Drawable;
enum ObjectID {};
enum KindOfType {};
enum EvaEventID {};

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

// vftable 0x00BFAF88: allow 0x00271B3C, keyed by an Eva event id.
class Rva00271B3CFilter : public Rva000421C8
{
public:
	Rva00271B3CFilter(int value) : m_value(value) {}
	virtual bool allow(Object *obj);
	int m_value;
};

// vftable 0x00BFAD04: is the candidate controlled by the +0x08 player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class Player
{
public:
	bool isLocalPlayer() const;
	char m_pad00[0x54];
	int m_playerIndex;	// +0x54
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad00[0x40];
	unsigned int m_frame;	// +0x40
};
extern GameLogic *TheGameLogic;

class Radar
{
public:
	void tryUnderAttackEvent(const Object *obj);
};
extern Radar *TheRadar;

class Eva
{
public:
	bool isEventBlockedByTimeout(EvaEventID id) const;
	bool isEventAboutToPlay(EvaEventID id) const;
	void rva001DE2DA(int id, const Coord3D *pos, int playerIndex);
};
extern Eva *TheEva;

class RadarWindowOverrideSource
{
public:
	void rva002D3756(void *obj);
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Rva00271B03
{
public:
	void rva00271B03();
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class ThingTemplate
{
public:
	char m_pad000[0x10E];
	unsigned char m_10E;
	char m_pad10F[0x113 - 0x10F];
	unsigned char m_113;
	char m_pad114[0x118 - 0x114];
	unsigned char m_118;
	char m_pad119[0x580 - 0x119];
	int m_evaEvent580;
	int m_evaEvent584;
	int m_evaEvent588;
	int m_evaEventAlt58C;
	float m_evaRadius590;
	int m_pad594;
	int m_evaEvent598;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isKindOf(KindOfType kind) const;
	bool rva00293926(KindOfType kind);
	bool rva00294471(void *player, int flag);
	Drawable *getDrawable() const { return reinterpret_cast<const Thing *>(this)->getDrawable(); }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
	char m_pad44[0x260 - 0x44];
	void *m_260;			// +0x260
};

class DamageInfo
{
public:
	char m_pad00[8];
	ObjectID m_sourceID;	// +0x08
	unsigned int m_sourcePlayerMask;	// +0x0C
	int m_damageType;		// +0x10
	int m_pad14;
	int m_18;				// +0x18
	int m_deathType;		// +0x1C
	char m_pad20[0x25 - 0x20];
	bool m_25;				// +0x25
	char m_pad26[0x70 - 0x26];
	float m_actualDamageDealt;	// +0x70
};

class Drawable
{
public:
	void rva0027B18C(const DamageInfo *info);
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0xFC - 0x08];
	Object *m_object;		// +0xFC
	char m_pad100[0x388 - 0x100];
	unsigned int m_388;		// +0x388
	char m_pad38C[0x440 - 0x38C];
	bool m_440;				// +0x440
};

void Drawable::rva0027B18C(const DamageInfo *info)
{
	Object *obj = getObject();
	if (!obj)
		return;
	if ((obj->m_template->m_10E & 0x40) && (obj->m_template->m_118 & 0x40))
		return;
	Player *player = obj->getControllingPlayer();
	const ThingTemplate *tmpl = getTemplate();
	if (!(info->m_actualDamageDealt > 0.0f))
		return;
	if (info->m_damageType == 10 || info->m_damageType == 7)
		return;
	if (info->m_deathType == 0x16)
		return;
	if (info->m_18 == 2)
		return;
	if (info->m_sourcePlayerMask & (1 << player->m_playerIndex))
		return;
	if (!player->isLocalPlayer())
		return;
	if (info->m_25) {
		if (obj->m_260 != 0)
			TheRadar->tryUnderAttackEvent(obj);
		if (tmpl) {
			Object *source = TheGameLogic->findObjectByID(info->m_sourceID);
			int evt = tmpl->m_evaEvent598;
			int alt;
			if (evt != -1 && !obj->isKindOf((KindOfType)0x9d)
				&& !obj->rva00293926((KindOfType)0x3f) && !obj->rva00293926((KindOfType)0x25)
				&& source && !source->rva00294471(player, 1)) {
				alt = tmpl->m_evaEventAlt58C;
			} else if (info->m_damageType == 0x17 && (evt = tmpl->m_evaEvent588) != -1) {
				alt = -1;
			} else if (info->m_damageType != 0x17 && source && source->getDrawable()
				&& source->getDrawable()->m_440 && (evt = tmpl->m_evaEvent584) != -1) {
				alt = tmpl->m_evaEventAlt58C;
			} else {
				evt = tmpl->m_evaEvent580;
				alt = tmpl->m_evaEventAlt58C;
			}
			if (evt != -1) {
				unsigned int frame = TheGameLogic->m_frame;
				if (m_388 <= frame
					&& (TheEva->isEventBlockedByTimeout((EvaEventID)evt) || TheEva->isEventAboutToPlay((EvaEventID)evt))
					&& alt != -1)
					TheEva->rva001DE2DA(alt, obj->getPosition(), 0);
				else
					TheEva->rva001DE2DA(evt, obj->getPosition(), 0);
				float radius = tmpl->m_evaRadius590;
				if (radius <= 0.0f || tmpl->m_evaEvent580 == -1) {
					reinterpret_cast<Rva00271B03 *>(this)->rva00271B03();
				} else {
					Rva00271B3CFilter eventFilter(tmpl->m_evaEvent580);
					Rva00260E2AFilter playerFilter(player);
					eventFilter.link(&playerFilter);
					BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(
						reinterpret_cast<const BFMERopeDrawable *>(this)->getPosition(), radius, 2, &eventFilter, 0);
					Object *other;
					while ((other = hits.next()) != 0) {
						if (other->getDrawable())
							reinterpret_cast<Rva00271B03 *>(other->getDrawable())->rva00271B03();
					}
				}
			}
		}
	}
	if (getTemplate()->m_113 & 4)
		theRadarWindowOverrideSource->rva002D3756(obj);
}
