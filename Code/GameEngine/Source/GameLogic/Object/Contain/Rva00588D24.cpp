// cl: /DNDEBUG /MD
// ?rva00588D24@Rva0047A040Base9E0@@QAE_NPAXPAVObject@@@Z @0x00588D24 117B
// Evidence: unlock lane, caller 0x00479ADA lea ecx [esi+0x9E0] (HordeGarrisonContain second base),
// pin rva00588BF3 member of Rva0047A040Base9E0, slots 0x20/0xF4/0x100,
// globals TheGameLogic and g_bfmeWorldRV, callers 0x00477315 and 0x00479AE8.
class Object;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class ContainEntry
{
public:
	SLOT08(e00,e01,e02,e03,e04,e05,e06,e07)
	virtual void slot20(Object *obj);
	SLOT08(e09,e10,e11,e12,e13,e14,e15,e16)
	SLOT08(e17,e18,e19,e20,e21,e22,e23,e24)
	SLOT08(e25,e26,e27,e28,e29,e30,e31,e32)
	SLOT08(e33,e34,e35,e36,e37,e38,e39,e40)
	SLOT08(e41,e42,e43,e44,e45,e46,e47,e48)
	SLOT08(e49,e50,e51,e52,e53,e54,e55,e56)
	virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60();
	virtual bool slotF4();
	virtual void e62(); virtual void e63();
	virtual void slot100(void *a);
};

class GameLogic
{
public:
	char _00[0x40];
	void *m_40;
};
extern GameLogic *TheGameLogic;

struct BfmeWorldRV
{
	char _00[0x28];
	unsigned char m_28;
};
extern class ControlBar *TheControlBar;

class Rva0047A040Base9E0
{
public:
	void *rva00588BF3(void *a, Object *b);
	bool rva00588D24(void *a, Object *b);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *obj);
};

bool Rva0047A040Base9E0::rva00588D24(void *a, Object *b)
{
	ContainEntry *e = (ContainEntry *)rva00588BF3(a, b);
	if (e == 0)
		return false;
	if (!e->slotF4()) {
		e->slot20(b);
		e->slot100(TheGameLogic->m_40);
		if (e->slotF4()) {
			(*(BfmeWorldRV **)&TheControlBar)->m_28 = 1;
			e->slot100(0);
		}
		return true;
	}
	e->slot100(0);
	return false;
}

// ?rva00588D99@Rva0047A040Base9E0@@QAEXPAVObject@@@Z @0x00588D99 135B
// Leaf lane, pin gives name. Callers HordeTransportContain 0x004770A6 and
// HordeGarrisonContain 0x00479B7F forward Object* to helper at +0x11D/+0x9E0.
// Drawable gate at +0x43c, local-player gate via ThePlayerList+0x10 and
// getControllingPlayer, message 0x3ED with ObjectID at +0x74 via
// MessageStreamSubsystem slot 0x48 and TheInGameUI slot 0x10c, then
// setStatus(3,true); second arm checks +0x454 then testStatus(0x5E) then
// pinned rva0028BAC0. Layouts follow DrawableRva00276B95, radius-cursor
// PlayerList, Rva0042F9DAEmit MessageStream/InGameUI and Rva0042FB8F ObjectID.
enum ObjectID
{
	OBJECTID_NONE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_DUMMY = 0
};
class Drawable
{
public:
	char m_pad00[0x43c];
	bool m_43c;
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Player;
class PlayerList
{
public:
	unsigned char m_pad[0x10];
	Player *m_localPlayer;
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
	SLOT08(v00,v01,v02,v03,v04,v05,v06,v07)
	SLOT08(v08,v09,v10,v11,v12,v13,v14,v15)
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
extern class MessageStream *TheMessageStream;
class InGameUI
{
public:
	SLOT08(w00,w01,w02,w03,w04,w05,w06,w07)
	SLOT08(w08,w09,w10,w11,w12,w13,w14,w15)
	SLOT08(w16,w17,w18,w19,w20,w21,w22,w23)
	SLOT08(w24,w25,w26,w27,w28,w29,w30,w31)
	SLOT08(w32,w33,w34,w35,w36,w37,w38,w39)
	SLOT08(w40,w41,w42,w43,w44,w45,w46,w47)
	SLOT08(w48,w49,w50,w51,w52,w53,w54,w55)
	SLOT08(w56,w57,w58,w59,w60,w61,w62,w63)
	virtual void w64();
	virtual void w65();
	virtual void w66();
	virtual void slot10C(Drawable *d);
};
extern InGameUI *TheInGameUI;
class Object
{
public:
	Player *getControllingPlayer() const;
	void setStatus(ObjectStatusTypes bit, bool flag);
	bool testStatus(ObjectStatusTypes bit) const;
	void rva0028DCC4();
};
class Rva0028BAC0
{
public:
	void rva0028BAC0();
};
struct ObjectLayout
{
	char _00[0x74];
	ObjectID m_id;
	char _78[0x454 - 0x78];
	unsigned char m_454;
};
void Rva0047A040Base9E0::rva00588D99(Object *obj)
{
	Drawable *d = ((Thing *)obj)->getDrawable();
	if (d != 0 && d->m_43c) {
		Player *local = ThePlayerList->m_localPlayer;
		Player *ctrl = obj->getControllingPlayer();
		if (ctrl == local) {
			GameMessage *msg = TheMessageStream->appendType(0x3ED);
			ObjectLayout *o = (ObjectLayout *)obj;
			msg->appendObjectIDArgument(o->m_id);
			TheInGameUI->slot10C(d);
		}
		obj->setStatus((ObjectStatusTypes)3, true);
	}
	ObjectLayout *o2 = (ObjectLayout *)obj;
	if (o2->m_454 != 0) {
		if (!obj->testStatus((ObjectStatusTypes)0x5E))
			((Rva0028BAC0 *)obj)->rva0028BAC0();
	}
}

// ?rva00588E20@Rva0047A040Base9E0@@QAEXPAVObject@@@Z @0x00588E20 36B
// Unlock lane, abuts 0x00588D99 in same TU. +0x454 gate to pinned
// rva0028DCC4 then setStatus(3,false). Callers 0x00477101 and 0x00479BBC.
void Rva0047A040Base9E0::rva00588E20(Object *obj)
{
	ObjectLayout *o = (ObjectLayout *)obj;
	if (o->m_454 == 0)
		obj->rva0028DCC4();
	obj->setStatus((ObjectStatusTypes)3, false);
}
