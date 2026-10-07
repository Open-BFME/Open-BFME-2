// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// SymbioticStructuresBody overrides in the vtables its matched ctor 0x004C0AF1
// installs over ActiveBody: primary 0x00C5B830, +0x0C 0x00C5B770 and the body
// interface at +0x10 (0x00C5B6C0). The +0x10 slots are compiled with that
// subobject this. Names are by address.
//
// The float queries hand the same question to the host body module kept at
// +0x100 (its body interface at +0x10) when the rowed Rva004C0D4F check holds
// (after the pinned refresh 0x004C0C52 for slot 5 and primary slot 24), else
// answer 0. Primary slot 24 asks the host's body-interface slot 4.

#include "ascii_string.h"
class ModuleData;

// A status/condition bit set: 0x4C bytes cleared, then three bits (first
// argument ignored); rowed ctor 0x00265254.
class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
private:
	unsigned int m_bits[19];
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class Matrix3D;
class Player;

typedef float Real;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class ThingTemplate
{
public:
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	unsigned char m_pad000[0xA0];
	GeometryInfo m_geometryInfo; // +0xA0
	unsigned char m_padA1[0x5F7 - 0xA1];
	signed char m_5F7; // +0x5F7
};

class Drawable
{
public:
	void rva00275DCE(int mode, Real a, Real b, Real c);
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);
};

class Object : public Thing
{
public:
	unsigned char m_pad00[4];
	const ThingTemplate *m_template; // +0x04
	const ThingTemplate *getTemplate() const { return m_template; }
	unsigned char m_transform[0x74 - 8]; // +0x08
	ObjectID m_74; // +0x74 (ID)
	ObjectID getID() const { return m_74; }
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_88; // +0x88
	Object *m_8C; // +0x8C (next)
	unsigned char m_pad90[0x10C - 0x90];
	int m_10C[19]; // +0x10C (a 0x4C-byte condition bit set)
	void rva001E42F2(const Rva00265254 &bits);
	void rva001E431E(const int *bits);
	void setStatus(ObjectStatusTypes bit, bool set);
	void setEffectivelyDead(bool dead);
	void rva0028ABFC(Real height);
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
	void AddObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};

extern AI *TheAI;

struct GlobalData
{
	unsigned char m_pad000[0xAE4];
	Real m_AE4; // +0xAE4
};

extern GlobalData *TheGlobalData;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

struct SymbioticStructuresBodyModuleData
{
	unsigned char m_pad00[0x48];
	const FXList *m_48; // +0x48
	unsigned char m_pad4C[0x64 - 0x4C];
	AsciiString m_64; // +0x64 (host template name)
};

class GameLogic
{
public:
	Object *getFirstObject();
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

template <int N> class Rva004C0D13Slots : public Rva004C0D13Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C0D13Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva004C0D4F
{
public:
	bool rva004C0D4F();
};

class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *a1, int a2);
};

class BodyModuleInterface : public Rva004C0D13Slots<4>
{
public:
	virtual float rva004C0D9CSlot4() = 0;
	virtual float rva004C0D13() = 0;
	virtual float rva004C105A() = 0;
	virtual float rva004C108B() = 0;
	virtual BodyDamageType getDamageState() const = 0; virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0;
	virtual void gap12() = 0; virtual void gap13() = 0; virtual void gap14() = 0; virtual void gap15() = 0;
	virtual void gap16() = 0; virtual void gap17() = 0; virtual void gap18() = 0; virtual void gap19() = 0;
	virtual void gap20() = 0; virtual void gap21() = 0; virtual void gap22() = 0; virtual void gap23() = 0;
	virtual void gap24() = 0; virtual void gap25() = 0; virtual void gap26() = 0;
	virtual float rva004C0DF3() = 0;
	virtual AsciiString rva004C0ECE() = 0; virtual void gap29() = 0; virtual void gap30() = 0; virtual void gap31() = 0;
	virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0; virtual void gap35() = 0;
	virtual void gap36() = 0; virtual void gap37() = 0; virtual void gap38() = 0;
	virtual void rva004C121B(void *a1) = 0;
	virtual void rva004C123C(void *a1, bool doFX) = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

struct Rva004C0B60Arg
{
	int m_words[32];
};

class BehaviorModuleHead : public Rva004C0D13Slots<1>
{
protected:
	virtual void loadPostProcess();
};
template <int N> class Rva004C1170Gaps : public Rva004C1170Gaps<N - 1>
{
public:
	virtual void gap2(char (*)[N]) = 0;
};
template <> class Rva004C1170Gaps<2> : public BehaviorModuleHead
{
};
class BehaviorModule : public Rva004C1170Gaps<23>
{
public:
	virtual void rva004C0B60(Rva004C0B60Arg arg) = 0;
	virtual float rva004C0D9C() = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

// The host's body module: the same module shape with its body interface at
// +0x10.
class HostBodyModule : public BehaviorModule, public BehaviorModuleInterface, public BodyModuleInterface
{
};

class ActiveBody : public BehaviorModule, public BehaviorModuleInterface, public BodyModuleInterface
{
protected:
	unsigned char m_pad014[0x100 - 0x14];
};

class SymbioticStructuresBody : public ActiveBody
{
public:
	virtual void rva004C0B60(Rva004C0B60Arg arg);
	virtual float rva004C0D9C();
	virtual float rva004C0D13();
	virtual float rva004C105A();
	virtual float rva004C108B();
	virtual float rva004C0DF3();
	virtual AsciiString rva004C0ECE();
	virtual void rva004C121B(void *a1);
	virtual void rva004C123C(void *a1, bool doFX);
	void rva004C0B63();
	void rva004C0C52();
protected:
	virtual void loadPostProcess();
private:
	Rva004C0D4F *checker() { return (Rva004C0D4F *)(BehaviorModule *)this; }
	HostBodyModule *m_host; // +0x100
	ObjectID m_104; // +0x104 (the host's ID)
};

// ?rva004C0B60@SymbioticStructuresBody@@UAEXURva004C0B60Arg@@@Z, retail 0x004C0B60,
// 3 bytes: primary slot 23, a no-op taking a 0x80-byte argument by value.
void SymbioticStructuresBody::rva004C0B60(Rva004C0B60Arg)
{
}

// ?rva004C0C52@SymbioticStructuresBody@@QAEXXZ, retail 0x004C0C52, 193 bytes:
// with the host and an owning Object both controlled, the pinned Drawable
// member 0x00275DCE runs (0.2, 0.7, 2.0) on both drawables, mode 5 for the
// host's when the Object belongs to the local player (else the Object's) and
// mode 0 for the other.
void SymbioticStructuresBody::rva004C0C52()
{
	Object *host = TheGameLogic->findObjectByID(m_104);
	if (!host)
		return;
	Object *obj = m_object;
	if (!obj)
		return;
	Player *local = ThePlayerList->getLocalPlayer();
	Player *owner = obj->getControllingPlayer();
	if (!local || !owner)
		return;
	Drawable *first;
	Drawable *second;
	if (local == owner)
	{
		first = host->getDrawable();
		second = obj->getDrawable();
	}
	else
	{
		first = obj->getDrawable();
		second = host->getDrawable();
	}
	if (first)
		first->rva00275DCE(5, 0.2f, 0.7f, 2.0f);
	if (second)
		second->rva00275DCE(0, 0.2f, 0.7f, 2.0f);
}

// ?rva004C0D9C@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0D9C, 53 bytes:
// primary slot 24.
float SymbioticStructuresBody::rva004C0D9C()
{
	rva004C0C52();
	return checker()->rva004C0D4F() ? m_host->rva004C0D9CSlot4() : 0.0f;
}

// ?rva004C0D13@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0D13, 60 bytes: body
// interface slot 5.
float SymbioticStructuresBody::rva004C0D13()
{
	rva004C0C52();
	return checker()->rva004C0D4F() ? m_host->rva004C0D13() : 0.0f;
}

// ?rva004C105A@SymbioticStructuresBody@@UAEMXZ, retail 0x004C105A, 49 bytes: body
// interface slot 6.
float SymbioticStructuresBody::rva004C105A()
{
	return checker()->rva004C0D4F() ? m_host->rva004C105A() : 0.0f;
}

// ?rva004C108B@SymbioticStructuresBody@@UAEMXZ, retail 0x004C108B, 49 bytes: body
// interface slot 7.
float SymbioticStructuresBody::rva004C108B()
{
	return checker()->rva004C0D4F() ? m_host->rva004C108B() : 0.0f;
}

// ?rva004C0DF3@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0DF3, 49 bytes: body
// interface slot 27.
float SymbioticStructuresBody::rva004C0DF3()
{
	return checker()->rva004C0D4F() ? m_host->rva004C0DF3() : 0.0f;
}

// ?rva004C121B@SymbioticStructuresBody@@UAEXPAX@Z, retail 0x004C121B, 33 bytes:
// body interface slot 39; with an owning Object, the pinned
// BfmeSubFCB::bfmeCallFCB(argument, 0) on it, then the pinned refresh.
void SymbioticStructuresBody::rva004C121B(void *a1)
{
	Object *obj = m_object;
	if (obj)
	{
		((BfmeSubFCB *)obj)->bfmeCallFCB(a1, 0);
		rva004C0C52();
	}
}

// ?rva004C0ECE@SymbioticStructuresBody@@UAE?AVAsciiString@@XZ, retail
// 0x004C0ECE, 161 bytes: body interface slot 28; the host's slot-28 string
// when the rowed Rva004C0D4F check holds, else an empty string.
AsciiString SymbioticStructuresBody::rva004C0ECE()
{
	return checker()->rva004C0D4F() ? m_host->rva004C0ECE() : AsciiString("");
}

// ?rva004C123C@SymbioticStructuresBody@@UAEXPAX_N@Z, retail 0x004C123C, 143
// bytes: body interface slot 40 (the first argument unread). After the pinned
// refresh 0x004C0C52 and the primary member 0x004C0B63, when the primary slot
// 24 figure equals the body slot 6 figure, the Object drops condition bits
// 0x43..0x45 (0x001E42F2 with an Rva00265254 set) and statuses 2 and 0x15;
// then, asked to, plays the module data's +0x48 FX on the Object.
void SymbioticStructuresBody::rva004C123C(void *a1, bool doFX)
{
	rva004C0C52();
	rva004C0B63();
	float before = rva004C0D9C();
	if (before == rva004C105A())
	{
		Object *obj = m_object;
		obj->rva001E42F2(Rva00265254(0, 0x43, 0x44, 0x45));
		m_object->setStatus((ObjectStatusTypes)2, false);
		m_object->setStatus((ObjectStatusTypes)0x15, false);
	}
	if (doFX)
	{
		const FXList *fx = ((const SymbioticStructuresBodyModuleData *)m_moduleData)->m_48;
		if (fx)
			FXList::doFXObj(fx, m_object, 0);
	}
}

// ?loadPostProcess@SymbioticStructuresBody@@MAEXXZ, retail 0x004C1170, 171
// bytes: primary slot 1 (vtable 0x00C5B830), the loadPostProcess slot. Finds
// the first Object in TheGameLogic's list (next at +0x8C) whose +0x88 name
// equals the module data's +0x64 name, takes on its transform (Thing
// setTransformMatrix with its +8 matrix), records its ID at +0x104 and
// refreshes; then the primary member 0x004C0B63 and the refresh again.
void SymbioticStructuresBody::loadPostProcess()
{
	Object *obj = m_object;
	if (obj == 0)
		return;
	const SymbioticStructuresBodyModuleData *d = (const SymbioticStructuresBodyModuleData *)m_moduleData;
	Object *o = TheGameLogic->getFirstObject();
	AsciiString name;
	for (; o; o = o->m_8C)
	{
		name = o->m_88;
		if (name.compare(d->m_64) == 0)
		{
			obj->setTransformMatrix((const Matrix3D *)o->m_transform);
			m_104 = o->getID();
			rva004C0C52();
			break;
		}
	}
	rva004C0B63();
	rva004C0C52();
}
