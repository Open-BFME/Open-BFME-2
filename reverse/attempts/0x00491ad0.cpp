// ?rva00491AD0@AttachUpdate@@QAEXXZ
// partial score=0.85 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
//
// AttachUpdate (vftable 0x00C4DB20, UpdateModuleInterface view 0x00C4DB14;
// ctor 0x00491A0F, data AttachUpdateModuleData 0x00491968).
//
//   0x00491AD0  attach to a parent: with no +0x20 parent yet, the closest
//               object within the data's ScanRange (+0x1C) that is not
//               this object, not effectively dead, and passes the data's
//               ObjectFilter (+0x08) for the controlling player (BFME2's
//               partition filter chain, the view AIStructureCreepTactic.cpp
//               documents). A parent whose 0x002931BA holds hands over to its
//               +0x274 object when that one's template has +0x115 bit 5; a
//               parent whose template has +0x11D bit 6 needs its player's
//               0x002AA245. Remember its ID, set the data's ParentStatus on
//               it when any, give this object status 0x62, play AttachFX,
//               and when both the local player and the parent's player exist
//               play the owner, ally or enemy attachment EVA event at the
//               parent and keep the matching died event in +0x24.
//
//   0x00491D2F  update (UpdateModuleInterface slot): attach; with a parent
//               that is gone or effectively dead (+0x438 bit 0) forget it,
//               play the kept died event at this object, kill it with 8 and
//               sleep forever; otherwise move to 0x00491C84's anchor point
//               when not there yet, teleporting when AlwaysTeleport (+0x20).

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

namespace _STL {
template <int _Words> struct _Base_bitset
{
	bool _M_is_any() const;	// 0x000454BA
	unsigned long _M_w[_Words];
};
}

struct Coord3D
{
	float x;
	float y;
	float z;
	bool equals(const Coord3D &r) const;	// 0x00003702
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int distCalc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA00491AD0_98 = 0x62
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	bool rva002AA245() const;	// 0x002AA245
	Relationship getRelationship(const Player *that) const;	// 0x002AC3E0
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
	char m_pad00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

class ThingTemplate
{
public:
	char m_pad000[0x115];
	unsigned char m_115;	// +0x115 (bit 5 tested)
	char m_pad116[0x11D - 0x116];
	unsigned char m_11D;	// +0x11D (bit 6 tested)
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class Eva
{
public:
	void rva001DE2DA(int event, const Coord3D *pos, int flag);	// 0x001DE2DA
};
extern Eva *TheEva;

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool rva002931BA();	// 0x002931BA
	void rva0028CDEB(const _STL::_Base_bitset<4> *mask, bool set);	// 0x0028CDEB
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	void rva0029660C(const Coord3D *pos, int flag);	// 0x0029660C
	void setPosition(const Coord3D *pos);	// 0x0030AA80
	void kill(int damageType, int deathType);	// 0x002984D4
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;		// +0x74
	char m_pad078[0x274 - 0x78];
	Object *m_274;		// +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_438;	// +0x438 (bit 0: effectively dead)
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

struct AttachUpdateModuleData
{
	char m_pad00[0x08];
	char m_objectFilter[4];		// +0x08 ObjectFilter
	_STL::_Base_bitset<4> m_parentStatus;	// +0x0C ParentStatus
	float m_scanRange;		// +0x1C ScanRange
	bool m_alwaysTeleport;		// +0x20 AlwaysTeleport
	bool m_anchorToTopOfGeometry;	// +0x21
	int m_parentOwnerAttachmentEvaEvent;	// +0x24
	int m_parentAllyAttachmentEvaEvent;	// +0x28
	int m_parentEnemyAttachmentEvaEvent;	// +0x2C
	const FXList *m_attachFX;	// +0x30 AttachFX
	int m_parentOwnerDiedEvaEvent;	// +0x34
	int m_parentAllyDiedEvaEvent;	// +0x38
	int m_parentEnemyDiedEvaEvent;	// +0x3C
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};

class AttachUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva00491AD0();
	void rva00491C84(Coord3D *out, const Object *parent);	// 0x00491C84
private:
	const AttachUpdateModuleData *getAttachUpdateModuleData() const
	{
		return (const AttachUpdateModuleData *)m_moduleData;
	}
	ObjectID m_parentID;	// +0x20
	int m_diedEvaEvent;	// +0x24
};

void AttachUpdate::rva00491AD0()
{
	if (m_parentID != INVALID_ID)
		return;
	const AttachUpdateModuleData *data = getAttachUpdateModuleData();
	Object *obj = m_object;
	Object *parent = ThePartitionManager->getClosestObject(obj->getPosition(), data->m_scanRange, 1,
		Rva002614DFFilter(obj).link(Rva0026119DFilter().link(
			&Rva002614ECFilter(data->m_objectFilter, obj->getControllingPlayer(), true))));
	if (!parent)
		return;
	if (parent->rva002931BA()) {
		Object *other = parent->m_274;
		if (other && (other->m_template->m_115 & 0x20))
			parent = other;
	}
	Player *player = parent->getControllingPlayer();
	if ((parent->m_template->m_11D & 0x40) && !player->rva002AA245())
		return;
	m_parentID = parent->getID();
	if (data->m_parentStatus._M_is_any())
		parent->rva0028CDEB(&data->m_parentStatus, true);
	obj->setStatus(OBJECT_STATUS_RVA00491AD0_98, true);
	FXList::doFXObj(data->m_attachFX, obj, parent);
	Player *local = ThePlayerList->getLocalPlayer();
	if (local && player) {
		const Coord3D *where = parent->getPosition();
		if (player == local) {
			TheEva->rva001DE2DA(data->m_parentOwnerAttachmentEvaEvent, where, 0);
			m_diedEvaEvent = data->m_parentOwnerDiedEvaEvent;
		} else if (local->getRelationship(player) == ALLIES) {
			TheEva->rva001DE2DA(data->m_parentAllyAttachmentEvaEvent, where, 0);
			m_diedEvaEvent = data->m_parentAllyDiedEvaEvent;
		} else {
			TheEva->rva001DE2DA(data->m_parentEnemyAttachmentEvaEvent, where, 0);
			m_diedEvaEvent = data->m_parentEnemyDiedEvaEvent;
		}
	}
}

UpdateSleepTime AttachUpdate::update()
{
	rva00491AD0();
	if (m_parentID != INVALID_ID) {
		Object *parent = TheGameLogic->findObjectByID(m_parentID);
		Object *obj = m_object;
		if (!parent || (parent->m_438 & 1)) {
			m_parentID = INVALID_ID;
			TheEva->rva001DE2DA(m_diedEvaEvent, obj->getPosition(), 0);
			obj->kill(8, 0);
			return UPDATE_SLEEP_FOREVER;
		}
		Coord3D pos;
		rva00491C84(&pos, parent);
		if (!pos.equals(*obj->getPosition())) {
			if (getAttachUpdateModuleData()->m_alwaysTeleport)
				obj->rva0029660C(&pos, 0);
			else
				obj->setPosition(&pos);
		}
	}
	return UPDATE_SLEEP_NONE;
}
