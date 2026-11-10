// cl: /DNDEBUG /MD /EHs
//
// ??0HordeGarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047A040
// (160 bytes). Identity: the ctor called by the matched
// HordeGarrisonContain::friend_newModuleInstance 0x0024BA96 (news 0x9E4) and
// the base call of the matched ProductionQueueHordeContain ctor 0x00481343; it
// installs the nine HordeGarrisonContain vtables (primary 0x00C46570, the one
// the deleting dtor 0x0047A12B re-installs) and forwards both args to the pinned
// GarrisonContain ctor 0x00477F06 (base size 0x9E0; EH state 0 after it).
//
// Retail calls the ICF-folded empty default ctor 0x0047A6A9 (mov eax,ecx; ret;
// rowed as the Coord/Region/Matrix4D empty ctors) with ecx = this+0x9E0 BEFORE
// the vtable stores, which only a base-class subobject constructed in the base
// phase can produce (a member ctor is called after the vptr stores: tried, 34
// diffs). The class therefore has an empty second base with a user-declared
// out-of-line ctor, modelled as the placeholder Rva0047A040Base9E0 whose ctor is
// pinned to the folded address, and one derived int at +0x9E0 (BFME1's
// HordeGarrisonContainCtor.cpp has the same zeroed int at its +0x9B8 and no
// second base). Body: zero the int, then if the object exists set condition
// word 1 (+0x114) bit 10 (index 42, mask 0x400) and call the pinned
// condition-changed notifier 0x0028AE6D when it was clear, through the same
// masked-word accessors and free __forceinline helper as
// HordeSiegeEngineContainCtor.cpp (the BFME1 recipe that keeps the mask in eax
// and the test/or on the member).

class Thing;
class ModuleData;

class Rva00110ConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[8];
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RETAIL_5D = 0x5D,
	OBJECT_STATUS_26 = 0x26
};
class Player;
class Drawable;
class Rva0047A14CBody;
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	void rva0028DCC4();
	Drawable *getDrawable() const;
	void rva0028AE6D();
	char m_pad00[0x110];
	Rva00110ConditionBits m_conditionBits; // +0x110
	char m_pad130[0x120];
	Rva0047A14CBody *m_body250; // +0x250
	char m_pad254[0x200];
	unsigned char m_454; // +0x454
	char m_pad455[0x3];
};

static __forceinline void rva0047A040SetCondition(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

struct Iface00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 { virtual void f20(); };
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); };
class GarrisonContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public:
	GarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~GarrisonContain();
private:
	unsigned char m_pad38[0x9E0 - 0x38];
};

// Empty second base with an out-of-line empty ctor (retail 0x0047A6A9, ICF).
class Rva0047A040Base9E0
{
public:
	Rva0047A040Base9E0();
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	HordeGarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeGarrisonContain();
private:
	int m_9E0;
};

HordeGarrisonContain::HordeGarrisonContain(Thing *thing, const ModuleData *moduleData)
	: GarrisonContain(thing, moduleData)
{
	Object *object = m_object;
	m_9E0 = 0;
	// Word 1 (+0x114) bit 10: mask 0x400.
	if (object != 0)
		rva0047A040SetCondition(object, 42);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f00@Iface00@@UAEXXZ=??_GHordeGarrisonContain@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?f10@Iface10@@UAEXXZ=?update@GarrisonContain@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f20@Iface20@@UAEXXZ=?rva0046261B@SlaughterHordeContain@@UAEX_N@Z")
#pragma comment(linker, "/alternatename:?f28@Iface28@@UAEXXZ=?rva00479CF6@Rva00479CF6@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?f30@Iface30@@UAEXXZ=?isExitBusy@HordeGarrisonContain@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?f34@Iface34@@UAEXXZ=??1Region2D@@QAE@XZ")
