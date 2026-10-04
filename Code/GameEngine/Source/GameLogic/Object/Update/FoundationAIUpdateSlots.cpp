// cl: /O1 /DNDEBUG /MD
//
// FoundationAIUpdate overrides. Two sit on vtables only its matched ctor 0x004551B3
// and dtor ??1Rva00455050 install: the primary 0x00C40608 and the
// BehaviorModuleInterface vtable 0x00C40548 at +0x0C. The ctor also puts the
// interface 0x00C1A690 at +0x20 (slot 3 there is the bool getter 0x00354EB0)
// and the ObjectID at +0x28 the matched xfer saves. Names are by address.
//
// ?rva00455B67@FoundationAIUpdate@@UAEXPAVPlayer@@0@Z, retail 0x00455B67,
// 118 bytes: primary slot 9, two owner arguments (the ZH onCapture shape):
// when the +0x20 interface's slot 3 holds and the +0x28 object exists, tells
// the skirmish AI records of the old and the new owner (the pinned
// TheSkirmishAIManager lookup 0x002A8AB1 on [0x00DFEEF8]) through the pinned
// record members 0x002C6A4E and 0x002C6A3D, then moves the object to the new
// owner's +0x2EC team through the pinned 0x00298AE4.
// ?rva00455B42@FoundationAIUpdate@@UAEXH@Z, retail 0x00455B42, 37 bytes:
// +0x0C slot 46 (compiled with that subobject this); unless the +0x28 ID is
// the owner's own, passes the argument to the pinned 0x0028BAAE (stores
// Object +0x45C) of the object it names.
//
// Three more sit on the +0x20 interface vtable 0x00C1A690, which the
// CastleBehavior family installs as well (its slots fold onto the same
// bodies); these three are FoundationAIUpdate's by their place in its unit
// (0x004550F8..0x00456134) and by what they touch (+0x28 through the pinned
// setter 0x0045527A, the full object at this-0x20):
// ?rva00456134@FoundationAIUpdate@@UAEPAVObject@@PAXPBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@H@Z,
// retail 0x00456134, 110 bytes: slot 4; with a template, a position and an
// owner, runs the pinned 0x00455BDD, then slot 7, then the pinned 0x00455C98,
// returning slot 7's result (else null).
// ?rva00455374@FoundationAIUpdate@@UAEXXZ, retail 0x00455374, 11 bytes:
// slot 5; clears the +0x28 ID through the setter.
// ?rva00455B33@FoundationAIUpdate@@UAEPAVObject@@XZ, retail 0x00455B33, 15
// bytes: slot 6; the object the +0x28 ID names.
//
// ?rva0045527A@FoundationAIUpdate@@AAEXW4ObjectID@@@Z, retail 0x0045527A, 250
// bytes: the +0x28 setter slot 5 calls. A new ID hides the owner (status 3,
// unselectable, fade out over 10 frames) unless its template has KindOf bit
// 54; with that bit, and the owner the local player's, it posts message
// 0x3ED with the owner's ID and passes the drawable to TheInGameUI slot 67.
// Clearing the ID reverses the hiding (fade in over 30 frames).

class ModuleData;
class Team;
class ThingTemplate;
struct Coord3D;

enum ObjectID
{
	INVALID_ID = 0
};

class Drawable
{
public:
	void setSelectable(bool selectable);
	void fadeOut(unsigned int frames);
	void fadeIn(unsigned int frames);
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x114];
	unsigned int m_kindOf[4]; // +0x114
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Player;

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	void setStatus(ObjectStatusTypes status, bool set);
	Player *getControllingPlayer() const;
	void rva0028BAAE(int value);
	void rva00298AE4(Team *team);
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x74 - 0x08];
	ObjectID m_id; // +0x74
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

class GameMessage
{
public:
	void appendObjectIDArgument(ObjectID id);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *MessageStreamSubsystem;

template <int N> class Rva0045527AUISlots : public Rva0045527AUISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0045527AUISlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
class InGameUI : public Rva0045527AUISlots<67>
{
public:
	virtual void slot67(Drawable *draw) = 0;
};
extern InGameUI *TheInGameUI;

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct Rva002A8AB1Record
{
	void rva002C6A4E(Object *obj);
	void rva002C6A3D(Object *obj);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

template <int N> class Rva00455B42Slots : public Rva00455B42Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00455B42Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void gap1();
	virtual void gap2();
	virtual void gap3();
	virtual void gap4();
	virtual void gap5();
	virtual void gap6();
	virtual void gap7();
	virtual void gap8();
	virtual void rva00455B67(Player *oldOwner, Player *newOwner) = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface : public Rva00455B42Slots<46>
{
public:
	virtual void rva00455B42(int value) = 0;
};

struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva00C1A690Iface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual bool slot3() const = 0;
	virtual Object *rva00456134(void *unused, const ThingTemplate *tmpl, const Coord3D *pos, float angle,
		Player *owner, int a6) = 0;
	virtual void rva00455374() = 0;
	virtual Object *rva00455B33() = 0;
	virtual Object *slot7(const ThingTemplate *tmpl, const Coord3D *pos, float angle, Player *owner,
		int a5, int a6) = 0;
};

class FoundationAIUpdate : public UpdateModule, public Rva00C1A690Iface
{
public:
	virtual void rva00455B67(Player *oldOwner, Player *newOwner);
	virtual void rva00455B42(int value);
	virtual Object *rva00456134(void *unused, const ThingTemplate *tmpl, const Coord3D *pos, float angle,
		Player *owner, int a6);
	virtual void rva00455374();
	virtual Object *rva00455B33();
private:
	void rva0045527A(ObjectID id);
	void rva00455BDD(const ThingTemplate *tmpl, const Coord3D *pos, float angle);
	void rva00455C98(const ThingTemplate *tmpl, const Coord3D *pos, float angle, Player *owner);
	int m_24;
	ObjectID m_28; // +0x28
	bool m_2C;
};

// ?rva00455B67@FoundationAIUpdate@@UAEXPAVPlayer@@0@Z @0x00455B67
void FoundationAIUpdate::rva00455B67(Player *oldOwner, Player *newOwner)
{
	if (!slot3())
		return;
	Object *obj = TheGameLogic->findObjectByID(m_28);
	if (!obj)
		return;
	Rva002A8AB1Record *oldRecord = g_00DFEEF8->rva002A8AB1(oldOwner);
	Rva002A8AB1Record *newRecord = g_00DFEEF8->rva002A8AB1(newOwner);
	if (oldRecord)
		oldRecord->rva002C6A4E(obj);
	if (newRecord)
		newRecord->rva002C6A3D(obj);
	obj->rva00298AE4(newOwner->getDefaultTeam());
}

// ?rva00455B42@FoundationAIUpdate@@UAEXH@Z @0x00455B42
void FoundationAIUpdate::rva00455B42(int value)
{
	if (m_28 != m_object->getID())
	{
		Object *obj = TheGameLogic->findObjectByID(m_28);
		if (obj)
			obj->rva0028BAAE(value);
	}
}

// ?rva00456134@FoundationAIUpdate@@UAEPAVObject@@PAXPBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@H@Z @0x00456134
Object *FoundationAIUpdate::rva00456134(void *, const ThingTemplate *tmpl, const Coord3D *pos, float angle,
	Player *owner, int a6)
{
	if (!tmpl || !pos || !owner)
		return 0;
	rva00455BDD(tmpl, pos, angle);
	Object *obj = slot7(tmpl, pos, angle, owner, 0, a6);
	rva00455C98(tmpl, pos, angle, owner);
	return obj;
}

// ?rva00455374@FoundationAIUpdate@@UAEXXZ @0x00455374
void FoundationAIUpdate::rva00455374()
{
	rva0045527A(INVALID_ID);
}

// ?rva00455B33@FoundationAIUpdate@@UAEPAVObject@@XZ @0x00455B33
Object *FoundationAIUpdate::rva00455B33()
{
	return TheGameLogic->findObjectByID(m_28);
}

// ?rva0045527A@FoundationAIUpdate@@AAEXW4ObjectID@@@Z @0x0045527A
void FoundationAIUpdate::rva0045527A(ObjectID id)
{
	if (m_28 == id)
		return;
	m_28 = id;
	if (id != INVALID_ID)
	{
		Drawable *draw = m_object->getDrawable();
		if (m_object->isKindOf(54) == 0)
		{
			m_object->setStatus(OBJECT_STATUS_3, true);
			if (draw)
			{
				draw->setSelectable(false);
				draw->fadeOut(10);
			}
		}
		else if (draw && m_object)
		{
			if (m_object->getControllingPlayer() == ThePlayerList->getLocalPlayer())
			{
				GameMessage *msg = MessageStreamSubsystem->appendMessage(0x3ED);
				msg->appendObjectIDArgument(m_object->getID());
				TheInGameUI->slot67(draw);
			}
		}
	}
	else if (m_object->isKindOf(54) == 0)
	{
		m_object->setStatus(OBJECT_STATUS_3, false);
		Drawable *draw = m_object->getDrawable();
		if (draw && m_object->isKindOf(54) == 0)
		{
			draw->setSelectable(true);
			draw->fadeIn(30);
		}
	}
}
