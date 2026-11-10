// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
//
// ??0HordeSiegeEngineContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047D247
// (215 bytes). Identity: the ctor called by the matched
// HordeSiegeEngineContain::friend_newModuleInstance 0x0024BC43; it installs the
// ten vtables that the matched dtor 0x0047CFB2 (HordeSiegeEngineContainDtor.cpp)
// re-installs, and its unwind map names the three STLport members: list<int> at
// +0x128 (state 1), map at +0x134 (state 2), list<int> at +0x140 (state 3).
// Layout of the HordeTransportContain base (vptrs at +0x00, +0x0C, +0x10,
// +0x20..+0x34, +0xFC; members to +0x128) from HordeTransportContainDtor.cpp.
//
// Body: the two plain members are zeroed and then the module sets a model
// condition bit on its object: word 5 of the Object's condition-flag words at
// +0x110 (so +0x124), bit 17 (index 177, mask 0x20000), and calls the
// condition-changed notifier 0x0028AE6D (pinned ?rva0028AE6D@Object@@QAEXXZ,
// a thiscall with no arguments; BFME1 carries it as
// notifyModelConditionChanged) only when the bit was clear.
//
// The accessors return the masked word rather than a bool and the update is a
// free __forceinline helper, which is what makes cl 7.1 materialise the mask
// in eax and test/or the member in memory (retail) instead of lea-ing the field
// and CSE-ing the loaded value; this is the recipe of the byte-exact BFME1
// HordeGarrisonContainCtor.cpp. Spelling the test as a bool, a member helper or a
// plain `field & mask` all produce the lea form (reverse/re_attempts.log).

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <map>
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

class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x110];
	Rva00110ConditionBits m_conditionBits; // +0x110
};

static __forceinline void rva0047D247SetCondition(Object *object, int bit)
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
struct Iface34 { virtual void f34(); unsigned char m_pad[0xFC - 0x38]; };
struct IfaceFC { virtual void fFC(); };
class TransportContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
	, public IfaceFC
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TransportContain();
private:
	unsigned char m_pad100[0x11C - 0x100];
};
class HordeTransportContain : public TransportContain
{
public:
	HordeTransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeTransportContain();
private:
	unsigned char m_pad11C[0x128 - 0x11C];
};

// map<ObjectID, int>: the tree family dtor 0x00286852 -> clear 0x00286656 ->
// erase 0x00286183 (one instantiation: the self-recursive erase is not ICF-folded;
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 keys it by object ID).
enum ObjectID { INVALID_ID = 0 };
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	HordeSiegeEngineContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeSiegeEngineContain();
	virtual void f00();
	virtual void f20();
	virtual void f30();
	virtual void f34();
private:
	_STL::list<int> m_list128;
	int m_12C;
	bool m_130;
	ObjectIDIntMap m_map134;
	_STL::list<int> m_list140;
};

HordeSiegeEngineContain::HordeSiegeEngineContain(Thing *thing, const ModuleData *moduleData)
	: HordeTransportContain(thing, moduleData)
{
	Object *object = m_object;
	m_12C = 0;
	m_130 = false;
	// Word 5 (+0x124) bit 17: mask 0x20000.
	rva0047D247SetCondition(object, 177);
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
#pragma comment(linker, "/alternatename:?f10@Iface10@@UAEXXZ=?update@Rva00477AF3UpdateReceiver@@QAEXXZ")
#pragma comment(linker, "/alternatename:?f24@Iface24@@UAEXXZ=?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z")
#pragma comment(linker, "/alternatename:?f28@Iface28@@UAEXXZ=?onDie@HordeTransportContain@@UAEXPBVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?fFC@IfaceFC@@UAEXXZ=?createPayloadMember@TransportContain@@UAEPAVObject@@PBVThingTemplate@@PAVPayloadContainView@@PAV2@PBDH@Z")
