// ?onComingOutOfShroud@Drawable@@AAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// ?onComingOutOfShroud@Drawable@@AAEXXZ, retail 0x0027893E..0x00278C29 (747 bytes).
// Identity: WorldBuilder twin 0x00CA3700 (Drawable::onComingOutOfShroud in
// Drawable.cpp; its EnemyObjectSighted and EnemyCampSighted debug lines and
// the line 2084 assert about a castle without CastleBehavior). Retail offsets
// are target-measured: object +0xFC template +0x04 status bits +0x114 and the
// once-only bytes +0x445/+0x446 (WB's debug layout reads +0x104 +0x11C
// +0x44D +0x44E); template EVA events +0x59C/+0x5A0/+0x5A4/+0x5A8 and kind
// bits 7 and 47; object position +0x38 and status byte +0x438.
// Once the game is past frame 5 and the local player sees the object (the
// pinned 0x00294471 test): a not yet reported enemy whose template names a
// sighted event reports it (unless its owner already shows one through the
// 0x00272A6A iterate callback) at the nearest local object 0x00272AD5 finds
// and flags the 0x004A1828 holder's object; a castle member reports its
// castle's camp event once and marks the castle members through 0x002706F0;
// and the drawable reports the template's +0x5A4 event once. A shrouded
// object instead reports +0x5A8 once unless 0x00270260 says otherwise.
// Eva's report at 0x001DE2DA returns bool and takes two positions (it loads
// and null-tests [ebp+0x10] like [ebp+0xC] and ends in mov al,1 / xor al,al).

#include "Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Player;
class Object;
class Drawable;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
	char pad[0x10];
	Player *m_local;	// +0x10
public:
	Player *getLocalPlayer() const { return m_local; }
};
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;

class Eva
{
public:
	bool reportEvaEvent(int event, const Coord3D *position, const Coord3D *position2);
};
extern Eva *TheEva;

class ThingTemplate
{
	char pad[0x108];
	unsigned char m_kindOf[0x20];	// +0x108
	char pad128[0x59C - 0x128];
public:
	__forceinline bool isKindOf(int kind) const { return (m_kindOf[kind >> 3] & (1 << (kind & 7))) != 0; }
	int m_sightedEvent;	// +0x59C
	int m_sightedEventAlt;	// +0x5A0
	int m_revealedEvent;	// +0x5A4
	int m_shroudedEvent;	// +0x5A8
};

struct ModuleData
{
	char pad[0x4C];
	int m_campSightedEvent;	// +0x4C, CastleBehavior's
};

class Module
{
public:
	void *m_vtable;
	const ModuleData *m_moduleData;	// +0x04
	char pad08[0x18 - 0x08];
	ObjectID m_castleID;	// +0x18, CastleMemberBehavior's
};

class Rva003974CE
{
public:
	int apply(int (*func)(Object *obj, int arg), int arg);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

// The holder 0x004A1828 returns: slot 0 its object id, slot 5 a ready test.
class Rva004A1828Holder
{
public:
	virtual ObjectID getID();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool isReady();
};
struct Rva004A1828Owner;
int Rva004A1828Get(Rva004A1828Owner *owner);

class Object
{
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	char pad08[0x38 - 0x08];
	Coord3D m_position;	// +0x38
	char pad44[0x438 - 0x44];
	unsigned char m_privateStatus;	// +0x438
public:
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	bool rva00294471(void *player, int arg);
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	Drawable *getDrawable() const;
};

class Player
{
public:
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
};

int rva00272A6A(Object *obj, void *userData);
int rva002706F0(Object *obj, int arg);

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002706A8
{
public:
	void rva002706A8();
};

class Drawable
{
public:
	Object *rva00272AD5();
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
private:
	void onComingOutOfShroud();

	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	char pad08[0xFC - 0x08];
	Object *m_object;	// +0xFC
	char pad100[0x114 - 0x100];
	unsigned int m_status;	// +0x114
	char pad118[0x445 - 0x118];
	bool m_sightReported;	// +0x445
	bool m_useAltSightedEvent;	// +0x446
};

struct SightedEventData
{
	Drawable *drawable;
	int event;
};

void Drawable::onComingOutOfShroud()
{
	const ThingTemplate *tmpl = getTemplate();
	Object *obj = getObject();
	Player *localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
	if (!tmpl || !obj || !localPlayer || !TheGameLogic || TheGameLogic->getFrame() <= 5)
		return;

	if (obj->rva00294471(localPlayer, 1)) {
		if (!obj->isEffectivelyDead() && tmpl->m_sightedEvent != -1 && !tmpl->isKindOf(47) && !m_sightReported) {
			Rva004A1828Holder *holder = (Rva004A1828Holder *)Rva004A1828Get((Rva004A1828Owner *)obj);
			bool skip;
			if (holder && holder->isReady()) {
				skip = false;
			} else {
				Player *controller = obj->getControllingPlayer();
				if (controller) {
					SightedEventData data;
					data.drawable = this;
					data.event = tmpl->m_sightedEvent;
					if (controller->iterateObjects(rva00272A6A, &data) == 1)
						skip = false;
					else
						skip = true;
				} else {
					skip = true;
				}
			}
			if (!skip) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest) {
					int event = tmpl->m_sightedEvent;
					if (m_useAltSightedEvent && tmpl->m_sightedEventAlt != -1)
						event = tmpl->m_sightedEventAlt;
					if (TheEva->reportEvaEvent(event, nearest->getPosition(), obj->getPosition()) && holder && holder->isReady()) {
						m_sightReported = true;
						Object *holderObject = TheGameLogic->findObjectByID(holder->getID());
						if (holderObject) {
							Drawable *draw = holderObject->getDrawable();
							if (draw)
								((Rva002706A8 *)draw)->rva002706A8();
						}
					}
				}
			}
		}

		if (tmpl->isKindOf(7) && !(m_status & 0x40)) {
			static NameKeyType key_CastleMemberBehavior = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			Module *member = obj->findModule(key_CastleMemberBehavior);
			if (member) {
				Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
				if (castle) {
					Module *castleBehavior = castle->findModule(CastleBehavior::rva0003955DA());
					if (castleBehavior) {
						int event = castleBehavior->m_moduleData->m_campSightedEvent;
						if (event != -1) {
							Drawable *castleDraw = castle->getDrawable();
							if (castleDraw) {
								if (!(castleDraw->m_status & 0x40)) {
									Object *nearest = ((Drawable *)obj)->rva00272AD5();
									if (nearest)
										TheEva->reportEvaEvent(event, nearest->getPosition(), obj->getPosition());
								}
								((Rva003974CE *)castleBehavior)->apply(rva002706F0, 0);
							}
						}
					}
				}
			}
		}

		if (!(m_status & 0x80) && !obj->isEffectivelyDead()) {
			m_status |= 0x80;
			int event = tmpl->m_revealedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent(event, nearest->getPosition(), obj->getPosition());
			}
		}
	} else {
		if (((Rva00270260 *)this)->rva00270260())
			return;
		if (!(m_status & 0x80) && !obj->isEffectivelyDead()) {
			m_status |= 0x80;
			int event = tmpl->m_shroudedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent(event, nearest->getPosition(), obj->getPosition());
			}
		}
	}
}
