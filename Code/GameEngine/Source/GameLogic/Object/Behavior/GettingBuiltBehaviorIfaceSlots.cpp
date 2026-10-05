// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Overrides in the vtables the matched GettingBuiltBehavior ctor 0x004542FA
// installs at +0x20 (0x00C403C8, over the all-purecall 27-slot base
// 0x00C40020 rowed as GettingBuiltBehaviorInterface) and at +0x0C (0x00C40440,
// the BehaviorModuleInterface). Each is compiled with its subobject this.
// Layout from the ctor: +0x24 int (1), +0x28 float, +0x2C int, bytes
// +0x30..+0x36, +0x38 int, bytes +0x3C..+0x3E, the BfmePod20 list at +0x40.
// Method identities are not established; names are by address.

#include <math.h>

class Object;
class ModuleData;
class Player;
class Rva0039B795;
class Rva0039B7AD;
class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

struct Iface20Slots
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual float v12(Player *p);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

template <int N> class Rva00454430Slots : public Rva00454430Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00454430Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
	int rva0033A69A(Object *obj, int a2, int a3) const;
};

// Object +0x254: slot 5 a fraction, slot 8 a state.
class Rva0045342FBody : public Rva00454430Slots<5>
{
public:
	virtual float rva004533B2Slot5() = 0;
	virtual void gap6() = 0;
	virtual void gap7() = 0;
	virtual int rva0045342FSlot8() = 0;
};

class GlobalData
{
public:
	unsigned char m_pad000[0xA88];
	int m_A88; // +0xA88
};

extern GlobalData *TheGlobalData;

// What Object::rva0028BCF4 hands back: slot 5 runs on it.
class Rva00454501Peer : public Rva00454430Slots<5>
{
public:
	virtual void rva00454501Slot5() = 0;
};

class Object
{
public:
	bool rva0028C264(int *out, int value);
	void *rva0028BCF4() const;
	void rva0028AE6D();
	void *rva0028BD17() const;
	void setStatus(ObjectStatusTypes bit, bool set);
	Player *getControllingPlayer() const;

	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x74 - 0x08];
	int m_74; // +0x74 (ID)
	int m_78; // +0x78 (an Object ID)
	unsigned char m_pad07C[0x94 - 0x7C];
	unsigned int m_94; // +0x94
	unsigned char m_pad098[0x10C - 0x98];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	Rva0045342FBody *m_254; // +0x254
	unsigned char m_pad258[0x438 - 0x258];
	unsigned char m_438; // +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class AudioManager : public Rva00454430Slots<27>
{
public:
	virtual void rva004535B7Slot27(unsigned int handle) = 0;
};

extern AudioManager *TheAudio;

extern const int g_009BA4E4;

template <class T> class StringBase
{
public:
	bool isEmpty() const;
private:
	T *m_data;
};

struct GettingBuiltBehaviorModuleData
{
	unsigned char m_pad00[0x14];
	StringBase<char> m_14; // +0x14
	unsigned char m_pad18[0x20 - 0x18];
	float m_20; // +0x20
	float m_24; // +0x24
	unsigned char m_pad28[0x30 - 0x28];
	float m_30[1]; // +0x30, indexed by the Object +0x254 state
};

struct BfmePod20Node
{
	BfmePod20Node *m_next;
	BfmePod20Node *m_prev;
	int m_a[5];
};

template <class T> inline const T &rva00454430Max(const T &a, const T &b)
{
	return a < b ? b : a;
}

__forceinline float fast_float_ceil(float f)
{
	return (float)ceil((double)f);
}

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void gap1(); virtual void gap2(); virtual void gap3(); virtual void gap4();
	virtual void gap5(); virtual void gap6(); virtual void gap7();
	virtual void rva00454501();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface : public Rva00454430Slots<45>
{
public:
	virtual void rva004543CA(int a1) = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class GettingBuiltBehaviorInterface : public Rva00454430Slots<2>
{
public:
	virtual void rva00454430() = 0;
	virtual void gap3() = 0;
	virtual void rva00453652(int a1) = 0;
	virtual void rva004535B7() = 0;
	virtual bool rva004535B7Slot6() = 0;
	virtual bool rva0045314E(Object *obj) = 0;
	virtual bool rva004533B2() = 0;
	virtual bool rva004533A7() = 0;
	virtual void rva004543D5(bool value) = 0;
	virtual void gap11() = 0;
	virtual float rva0045342F(Object *obj) = 0;
	virtual void gap13() = 0; virtual void gap14() = 0; virtual void gap15() = 0;
	virtual void gap16() = 0; virtual void gap17() = 0; virtual void gap18() = 0;
	virtual bool rva004540F5() = 0;
	virtual float rva00453FE7(Object *obj) = 0;
	virtual void rva00453F31(int a1) = 0;
	virtual bool rva004531E4(Object *obj) = 0;
	virtual bool rva0045362B(int id) = 0;
};

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva004543CA(int a1);
	virtual void rva00454430();
	virtual void rva004535B7();
	virtual bool rva0045314E(Object *obj);
	virtual bool rva004533A7();
	virtual void rva004543D5(bool value);
	virtual bool rva004531E4(Object *obj);
	virtual bool rva0045362B(int id);
	virtual void rva00453F31(int a1);
	virtual float rva0045342F(Object *obj);
	virtual void rva00454501();
	virtual bool rva004533B2();
	void rva0045318B();
private:
	void rva004541AB();
	bool rva00453124();
	static GettingBuiltBehaviorInterface *interfaceOf(Object *obj)
	{
		return (GettingBuiltBehaviorInterface *)obj->rva0028BD17();
	}
	const GettingBuiltBehaviorModuleData *data() const { return (const GettingBuiltBehaviorModuleData *)m_moduleData; }
	unsigned int m_24; // +0x24 (an audio handle)
	float m_28; // +0x28
	unsigned int m_2C; // +0x2C
	bool m_30; // +0x30
	bool m_31; // +0x31
	bool m_32; // +0x32
	bool m_33; // +0x33
	bool m_34; // +0x34
	bool m_35; // +0x35
	bool m_36; // +0x36
	int m_38; // +0x38
	bool m_3C; // +0x3C
	bool m_3D; // +0x3D
	bool m_3E; // +0x3E
	BfmePod20Node *m_40; // +0x40 (list head)
};

// Object +0x438 bit 0, the flag the neighbour walks below require.
static inline bool rva00453F31Flag(const Object *obj)
{
	return (obj->m_438 & 1) != 0;
}

static const int GETTING_BUILT_CONDITION_A = 2 * 32 + 4;
static const int GETTING_BUILT_CONDITION_B = 2 * 32 + 5;

// ?rva004543CA@GettingBuiltBehavior@@UAEXH@Z, retail 0x004543CA, 11 bytes:
// slot 45 of the +0x0C vtable 0x00C40440; runs slot 2 of the +0x20 interface,
// the argument unread.
void GettingBuiltBehavior::rva004543CA(int)
{
	rva00454430();
}

// ?rva00454430@GettingBuiltBehavior@@UAEXXZ, retail 0x00454430, 66 bytes: slot 2
// of the +0x20 vtable; +0x2C becomes the module data's +0x24 float times
// g_009BA4E4 (logic frames), at least 1.
void GettingBuiltBehavior::rva00454430()
{
	float frames = (float)g_009BA4E4 * data()->m_24;
	m_2C = (unsigned int)rva00454430Max(frames, 1.0f);
}

// ?rva004535B7@GettingBuiltBehavior@@UAEXXZ, retail 0x004535B7, 116 bytes: slot 5
// of the +0x20 vtable; when slot 6 answers, drops +0x32, clears condition bits
// 2*32+4 and 2*32+5 (notifying per bit), clears statuses 0x14 and 2 and hands
// the +0x24 handle to TheAudio slot 27, resetting it to 1.
void GettingBuiltBehavior::rva004535B7()
{
	if (!rva004535B7Slot6())
		return;
	Object *obj = m_object;
	m_32 = false;
	if (obj->m_conditionBits.test(GETTING_BUILT_CONDITION_A))
	{
		obj->m_conditionBits.clear(GETTING_BUILT_CONDITION_A);
		obj->rva0028AE6D();
	}
	if (obj->m_conditionBits.test(GETTING_BUILT_CONDITION_B))
	{
		obj->m_conditionBits.clear(GETTING_BUILT_CONDITION_B);
		obj->rva0028AE6D();
	}
	obj->setStatus((ObjectStatusTypes)0x14, false);
	obj->setStatus((ObjectStatusTypes)2, false);
	if (TheAudio)
	{
		TheAudio->rva004535B7Slot27(m_24);
		m_24 = 1;
	}
}

// ?rva0045314E@GettingBuiltBehavior@@UAE_NPAVObject@@@Z, retail 0x0045314E, 61
// bytes: slot 7 of the +0x20 vtable; whether the Object's +0x94 count reaches
// slot 12's figure for it rounded up (ZH REAL_TO_INT_CEIL shape: ceil import,
// then fld/fistp).
bool GettingBuiltBehavior::rva0045314E(Object *obj)
{
	if (!obj)
		return false;
	unsigned int count = obj->m_94;
	return count >= (unsigned int)REAL_TO_INT_CEIL(rva0045342F(obj));
}

// ?rva004533A7@GettingBuiltBehavior@@UAE_NXZ, retail 0x004533A7, 11 bytes: slot 9
// of the +0x20 vtable; whether the module data's +0x14 string is empty.
bool GettingBuiltBehavior::rva004533A7()
{
	return ((const GettingBuiltBehaviorModuleData *)m_moduleData)->m_14.isEmpty();
}

// ?rva004543D5@GettingBuiltBehavior@@UAEX_N@Z, retail 0x004543D5, 10 bytes: slot
// 10 of the +0x20 vtable; stores +0x36.
void GettingBuiltBehavior::rva004543D5(bool value)
{
	m_36 = value;
}

// ?rva004531E4@GettingBuiltBehavior@@UAE_NPAVObject@@@Z, retail 0x004531E4, 61
// bytes: slot 22 of the +0x20 vtable; slot 7's test against slot 20's figure.
bool GettingBuiltBehavior::rva004531E4(Object *obj)
{
	if (!obj)
		return false;
	unsigned int count = obj->m_94;
	return count >= (unsigned int)REAL_TO_INT_CEIL(rva00453FE7(obj));
}

// ?rva0045362B@GettingBuiltBehavior@@UAE_NH@Z, retail 0x0045362B, 39 bytes: slot
// 23 of the +0x20 vtable; false for the owner's own ID, else whether an entry
// of the +0x40 list starts with the ID.
bool GettingBuiltBehavior::rva0045362B(int id)
{
	if (id == m_object->m_74)
		return false;
	for (BfmePod20Node *node = m_40->m_next; node != m_40; node = node->m_next)
	{
		if (id == node->m_a[0])
			return true;
	}
	return false;
}

// The three slots below walk the Objects whose IDs run on from the owner's in
// both directions while they share its template (rowed
// ThingTemplate::isEquivalentTo) and carry the +0x438 flag, through each one's
// interface (rowed Object::rva0028BD17).

// ?rva00453F31@GettingBuiltBehavior@@UAEXH@Z, retail 0x00453F31, 182 bytes: slot
// 21 of the +0x20 vtable; with the flag, slot 4 with the argument on the owner
// and on every such neighbour.
void GettingBuiltBehavior::rva00453F31(int a1)
{
	Object *me = m_object;
	const ThingTemplate *tmpl = me->m_template;
	int id = me->m_74;
	if (!rva00453F31Flag(me))
		return;
	rva00453652(a1);

	Object *other;
	int upId = id + 1;
	while ((other = TheGameLogic->findObjectByID(upId)) != 0)
	{
		if (!other->m_template->isEquivalentTo(tmpl) || !rva00453F31Flag(other))
			break;
		GettingBuiltBehaviorInterface *gbi = interfaceOf(other);
		if (gbi)
			gbi->rva00453652(a1);
		++upId;
	}
	while ((other = TheGameLogic->findObjectByID(--id)) != 0)
	{
		if (!other->m_template->isEquivalentTo(tmpl) || !rva00453F31Flag(other))
			break;
		GettingBuiltBehaviorInterface *gbi = interfaceOf(other);
		if (gbi)
			gbi->rva00453652(a1);
	}
}

// ?rva0045342F@GettingBuiltBehavior@@UAEMPAVObject@@@Z, retail 0x0045342F, 62
// bytes: slot 12 of the +0x20 vtable; the owner template's 0x0033A69A figure
// for the Object (0, -1) scaled by the module-data +0x30 entry for the owner's
// +0x254 slot 8 state.
float GettingBuiltBehavior::rva0045342F(Object *obj)
{
	float value = (float)m_object->m_template->rva0033A69A(obj, 0, -1);
	Rva0045342FBody *body = m_object->m_254;
	return value * data()->m_30[body->rva0045342FSlot8()];
}

// ?rva00454501@GettingBuiltBehavior@@UAEXXZ, retail 0x00454501, 86 bytes: slot
// 8 of the primary vtable 0x00C404FC. When the Object named by the owner's
// +0x78 exists and Object::rva0028BCF4 finds its peer, the peer's slot 5 runs,
// +0x30 is raised and the pinned member 0x004541AB follows; then a +0x24 audio
// handle of 5 or more goes to TheAudio slot 27 and resets to 1.
void GettingBuiltBehavior::rva00454501()
{
	Object *other = TheGameLogic->findObjectByID(m_object->m_78);
	if (other)
	{
		Rva00454501Peer *peer = (Rva00454501Peer *)other->rva0028BCF4();
		if (peer)
		{
			peer->rva00454501Slot5();
			m_30 = true;
			rva004541AB();
		}
	}
	if (TheAudio && m_24 >= 5)
	{
		TheAudio->rva004535B7Slot27(m_24);
		m_24 = 1;
	}
}

// ?rva004533B2@GettingBuiltBehavior@@UAE_NXZ, retail 0x004533B2, 125 bytes:
// slot 8 of the +0x20 vtable; false while slot 6 answers. Otherwise, with a
// negative module-data +0x20, the owner's rowed 0x0028C264 test against
// TheGlobalData +0xA88 must fail and the +0x254 slot 5 fraction be under 1;
// else the +0x254 slot 8 state must be 3. Then true unless the owner's
// 0x00453124 test (rowed under the address name BfmeThingE63::isValid)
// passes. Retail returns the verdict as one boolean expression (eax 0/1).
bool GettingBuiltBehavior::rva004533B2()
{
	if (!rva004535B7Slot6())
	{
		Rva0045342FBody *body = m_object->m_254;
		bool ready;
		if (data()->m_20 < 0.0f)
		{
			int out = 0;
			ready = !m_object->rva0028C264(&out, TheGlobalData->m_A88) && body->rva004533B2Slot5() < 1.0f;
		}
		else
			ready = body->rva0045342FSlot8() == 3;
		return ready && !rva00453124();
	}
	return false;
}

// ?rva0045318B@GettingBuiltBehavior@@QAEXXZ @0x0045318B 89B
// __thiscall ceil-and-credit: if m_object and its controlling player exist,
// REAL_TO_INT_CEIL slot 12 (+0x30) of the +0x20 subobject for the player into
// Money at Player+0x90 via rowed rva003B0CB3 and store to m_38. Gap between
// slot 7 0x0045314E and slot 22 0x004531E4; mirrors their ceil shape.
// Evidence: neighbours prove GettingBuiltBehavior owner (+0x08/+0x38/+0x20);
// callee rows getControllingPlayer 0x0028AFA9 plus rva003B0CB3 0x003B0CB3
// plus ceil import; caller 0x004536B5.
void GettingBuiltBehavior::rva0045318B()
{
	Object *obj = m_object;
	if (!obj)
		return;
	Player *player = obj->getControllingPlayer();
	if (!player)
		return;
	Iface20Slots *iface = (Iface20Slots *)((char *)this + 0x20);
	int count = REAL_TO_INT_CEIL(iface->v12(player));
	m_38 = count;
	Rva003B0D7C *money = (Rva003B0D7C *)((char *)player + 0x90);
	money->rva003B0CB3((unsigned int)count, (Rva0039B795 *)((char *)player + 0x3BC), true);
}
