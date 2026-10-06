// cl: /DNDEBUG /MD
//
// SlaughterHordeContain::update and its two iterate callbacks.
//
// ?update@SlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00480E72, 40 bytes.
// Slot 0 of the +0x10 UpdateModuleInterface vftable 0x00C48A90 (this at
// +0x10, as in the rowed DeletionUpdate::update): walks the owner's
// contained objects (its contain module at Object+0x250, slot 68) with the
// first callback, then returns the base update (pinned
// GarrisonContain::update 0x00479643; CitadelSlaughterHordeContain's update
// tail-calls this one).
//
// ?rva00480E28@@YAXPAVObject@@PAX@Z, retail 0x00480E28, 74 bytes.
// For a contained object of kind-of bit 77 that contains objects itself,
// walks those twice (iterate flags 1 and 0x10) with the second callback.
//
// ?rva00480DF4@@YAXPAVObject@@PAX@Z, retail 0x00480DF4, 52 bytes.
// For an object with an AI (Object+0x258) not in AI state 0x38 or 0x0F (rowed
// AIUpdateInterface::rva00260DED), issues the rowed
// AICommandInterface::rva0036EBB8 at the walking contain's owner (command
// source 2).
//
// ?update@CitadelSlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00480FE2, 107 bytes.
// Slot 0 of CitadelSlaughterHordeContain's +0x10 vftable 0x00C48CB0: when the
// ObjectID at +0x9EC (the one its rowed xfer transfers) names a live object,
// orders that object's AI with the owner and the source its slot 143
// reports (rowed AICommandInterface::rva0037379B for kind-of bit 77, the
// rowed aiExit otherwise), clears the ID, then returns
// SlaughterHordeContain::update.
//
// Callback names are address names; their identities are not established.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

class Object;

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

class ContainModuleInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void iterateContained(ContainIterateFunc func, void *userData, int flags);
};

class AICommandInterface
{
public:
	void rva0036EBB8(Object *target, CommandSourceType cmdSource);
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
	void aiExit(Object *obj, CommandSourceType cmdSource);
};

class AIUpdateInterfaceVtbl
{
public:
	SLOT08(v00,v01,v02,v03,v04,v05,v06,v07)
	SLOT08(v08,v09,v0A,v0B,v0C,v0D,v0E,v0F)
	SLOT08(v10,v11,v12,v13,v14,v15,v16,v17)
	SLOT08(v18,v19,v1A,v1B,v1C,v1D,v1E,v1F)
	SLOT08(v20,v21,v22,v23,v24,v25,v26,v27)
	SLOT08(v28,v29,v2A,v2B,v2C,v2D,v2E,v2F)
	SLOT08(v30,v31,v32,v33,v34,v35,v36,v37)
	SLOT08(v38,v39,v3A,v3B,v3C,v3D,v3E,v3F)
	SLOT08(v40,v41,v42,v43,v44,v45,v46,v47)
	SLOT08(v48,v49,v4A,v4B,v4C,v4D,v4E,v4F)
	SLOT08(v50,v51,v52,v53,v54,v55,v56,v57)
	SLOT08(v58,v59,v5A,v5B,v5C,v5D,v5E,v5F)
	SLOT08(v60,v61,v62,v63,v64,v65,v66,v67)
	SLOT08(v68,v69,v6A,v6B,v6C,v6D,v6E,v6F)
	SLOT08(v70,v71,v72,v73,v74,v75,v76,v77)
	SLOT08(v78,v79,v7A,v7B,v7C,v7D,v7E,v7F)
	SLOT08(v80,v81,v82,v83,v84,v85,v86,v87)
	virtual void v88(); virtual void v89(); virtual void v8A(); virtual void v8B();
	virtual void v8C(); virtual void v8D(); virtual void v8E();
	virtual CommandSourceType rva143();
	unsigned char m_pad04[0x20 - 0x04];
};

class AIUpdateInterface : public AIUpdateInterfaceVtbl, public AICommandInterface
{
public:
	int rva00260DED() const;
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

enum ObjectID
{
	INVALID_ID = 0
};

class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_kindOf.test(t); }
private:
	unsigned char m_pad[0x10C];
	Rva0010CBits m_kindOf; // +0x10C
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x250 - 0x08];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};

// ?rva00480DF4@@YAXPAVObject@@PAX@Z @0x00480DF4
void rva00480DF4(Object *obj, void *userData)
{
	if (obj == 0)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (ai == 0)
		return;
	int state = ai->rva00260DED();
	if (state == 0x38 || state == 0x0F)
		return;
	ai->rva0036EBB8((Object *)userData, (CommandSourceType)2);
}

// ?rva00480E28@@YAXPAVObject@@PAX@Z @0x00480E28
void rva00480E28(Object *obj, void *userData)
{
	if (obj == 0)
		return;
	if (!obj->getTemplate()->isKindOf((KindOfType)77))
		return;
	ContainModuleInterface *contain = obj->getContain();
	if (contain == 0)
		return;
	contain->iterateContained(rva00480DF4, userData, 1);
	contain->iterateContained(rva00480DF4, userData, 0x10);
}

struct Iface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual UpdateSleepTime update() = 0; unsigned char m_pad[12]; };

class GarrisonContain : public Iface00, public Iface0C, public Iface10
{
public:
	virtual UpdateSleepTime update();
};

class HordeGarrisonContain : public GarrisonContain
{
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual UpdateSleepTime update();
};

// ?update@SlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ @0x00480E72
UpdateSleepTime SlaughterHordeContain::update()
{
	Object *obj = m_object;
	if (obj)
		obj->getContain()->iterateContained(rva00480E28, obj, 1);
	return GarrisonContain::update();
}

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class CitadelSlaughterHordeContainBody : public SlaughterHordeContain
{
	unsigned char m_pad20[0x9EC - 0x20];
};

class CitadelSlaughterHordeContain : public CitadelSlaughterHordeContainBody
{
public:
	virtual UpdateSleepTime update();
private:
	ObjectID m_9EC;
};

// ?update@CitadelSlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ @0x00480FE2
UpdateSleepTime CitadelSlaughterHordeContain::update()
{
	if (m_9EC != INVALID_ID)
	{
		Object *other = TheGameLogic->findObjectByID(m_9EC);
		if (other)
		{
			Object *me = m_object;
			AIUpdateInterface *ai = other->getAI();
			if (other->getTemplate()->isKindOf((KindOfType)77))
				ai->rva0037379B(me, ai->rva143());
			else
				ai->aiExit(me, ai->rva143());
		}
		m_9EC = INVALID_ID;
	}
	return SlaughterHordeContain::update();
}
