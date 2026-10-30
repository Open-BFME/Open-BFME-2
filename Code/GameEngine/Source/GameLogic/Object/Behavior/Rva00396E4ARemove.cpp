// cl: -O1 -arch:SSE -G7 -EHsc -MD -D_STLP_USE_STATIC_LIB -D_STLP_USE_MALLOC -D_CRTIMP= -D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00396E4A@Rva00396E4A@@QAEXPAVObject@@@Z @0x00396E4A 72B
// Map remove: find key from Object+0x74 in map at +0x8c via rowed _M_find
// 0x00388F63 (int-int spelling: _M_find only reads key at node+0x10 so value
// type does not change bytes; erase proves void* value), clear status 0x55,
// erase via rowed 0x005530A8 (int-void*).
// Evidence: ret 4 thiscall, test ebx null, [ebx+0x74] key, [ecx+0x8c] map,
// callers unclaimed, callees all rowed. Scoped settings keep EBP; local
// key copy reproduces retail mov/mov/lea.
#include <stdio.h>
#include <map>
#include <set>
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

// Tree erase has a complete verified retail provider at5530A8.
// Keep inline iterator access visible without emitting a competing erase.
typedef _STL::pair<const int,void *> TriggerPtrValue;
typedef _STL::_Rb_tree<int,TriggerPtrValue,_STL::_Select1st<TriggerPtrValue>,_STL::less<int>,_STL::allocator<TriggerPtrValue> > TriggerPtrTree;
typedef _STL::_Rb_tree<int,int,_STL::_Identity<int>,_STL::less<int>,_STL::allocator<int> > TriggerSetTree;
namespace _STL {
// Native set-node creation4ABCC9 uses the rowed byte allocator.
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
template <> __declspec(dllimport) __forceinline
void _Construct<int,int>(int *place, const int &value)
{ new (static_cast<void *>(place)) int(value); }
template <> TriggerSetTree::_Link_type TriggerSetTree::_M_create_node(const int &value)
{
    _Link_type node = (_Link_type)allocator<char>::allocate(sizeof(_Rb_tree_node<int>), 0);
    _Construct(&node->_M_value_field, value);
    return node;
}
template <> void TriggerPtrTree::erase(TriggerPtrTree::iterator);
}

enum ObjectStatusTypes
{
	DUMMY_00 = 0x00,
	DUMMY_55 = 0x55
};
typedef bool Bool;

struct Rva00396C43NameData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

struct Rva00396C43Name
{
	const char *str() const { return m_data ? m_data->m_text : ""; }
	Rva00396C43NameData *m_data;
};

class ThingTemplate
{
public:
	const Rva00396C43Name &getName() const { return m_name; }
	// KindOf bit 0x2F of the BitFlags at +0x108.
	bool testKindOf2F() const { return (m_kindOf[0x2F >> 3] & (1 << (0x2F & 7))) != 0; }

private:
	char m_pad00[0x64];
	Rva00396C43Name m_name;	// +0x64
	char m_pad68[0x108 - 0x68];
	unsigned char m_kindOf[0x20];	// +0x108
};

// Slot 0 of the interface AI slot 96 returns: false is logged "not scared".
class Rva00396C43Critter
{
public:
	virtual bool slot0();
};

class AIUpdateInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual Rva00396C43Critter *slot96();	// +0x180
	void requestPath(Coord3D *destination, bool isFinalGoal);
};

class Object
{
public:
	void setStatus(ObjectStatusTypes bit, Bool flag);
	void rva0028AD32();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() { return m_ai; }

	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;						// +0x38
	char m_pad44[0x74 - 0x44];
	int m_key74;						// +0x74, the ObjectID
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai;			// +0x258
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *pos) { c.x = pos->x; c.y = pos->y; c.z = pos->z; }
static __forceinline void subCoord(Coord3D &c, const Coord3D *pos) { c.x -= pos->x; c.y -= pos->y; c.z -= pos->z; }
static __forceinline void addCoord(Coord3D &c, const Coord3D *pos) { c.x += pos->x; c.y += pos->y; c.z += pos->z; }
static __forceinline void scaleCoord(Coord3D &c, float factor) { c.x *= factor; c.y *= factor; c.z *= factor; }

extern bool g_bfmeCritterDesyncLog;
extern "C" FILE *theLogicRandomLogFile;
extern GameLogic *TheGameLogic;

class Rva00396E4A
{
public:
	void onTriggerEntered(Object *obj);
	void rva00396E4A(Object *obj);
private:
	char m_pad00[0x38];
	ObjectID m_fleeFromObjectID;	// +0x38, the object the trigger flees from
	char m_pad3C[0x8c - 0x3C];
	_STL::map<int, void *> m_map8c;
};

// Native trigger bodies retain EBP; inline library helpers use normal omission.
#pragma optimize("y", off)
void Rva00396E4A::rva00396E4A(Object *obj)
{
	if (obj == 0)
		return;
	int key = obj->m_key74;
	_STL::map<int, int>::iterator it_int = ((_STL::map<int, int> *)&m_map8c)->find(key);
	_STL::map<int, void *>::iterator it = *(_STL::map<int, void *>::iterator *)&it_int;
	if (it == m_map8c.end())
		return;
	obj->setStatus((ObjectStatusTypes)0x55, false);
	m_map8c.erase(it);
}

// ?onTriggerEntered@Rva00396E4A@@QAEXPAVObject@@@Z @0x00396C43 519B: the enter
// twin of rva00396E4A, reached through the same dispatcher 0x00397CEB. An
// object without kindof bit 0x2F gets status 0x55 and its ID inserted into
// the +0x8C set (rowed set<int>::insert 0x000BC15D). Otherwise, when the
// +0x38 object exists and the entrant's AI slot 96 interface reports true
// in slot 0, it paths the entrant 150 units directly away from that object.
// The three CritterDesync lines are the WB twin's (0x00EB94B0, which names
// the routine CastleBehavior::onTriggerEntered in its first line).
void Rva00396E4A::onTriggerEntered(Object *obj)
{
	if (obj == 0)
		return;
	if (obj->getTemplate()->testKindOf2F())
	{
		Object *source = TheGameLogic->findObjectByID(m_fleeFromObjectID);
		if (source == 0)
			return;
		AIUpdateInterface *ai = obj->getAI();
		if (ai == 0)
			return;
		Rva00396C43Critter *critter = ai->slot96();
		if (critter == 0)
			return;
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile, "CritterDesync:  CastleBehavior::onTriggerEntered called with animal %s",
				obj->getTemplate()->getName().str());
		if (!critter->slot0())
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "CritterDesync:  animal %s not scared, returning.",
					obj->getTemplate()->getName().str());
			return;
		}
		Coord3D dest;
		copyCoord(dest, obj->getPosition());
		subCoord(dest, source->getPosition());
		dest.Normalize();
		scaleCoord(dest, 150.0f);
		addCoord(dest, obj->getPosition());
		obj->rva0028AD32();
		ai->requestPath(&dest, true);
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile, "CritterDesync:  animal %s is scared, requesting new path to pos %g,%g,%g.",
				obj->getTemplate()->getName().str(), (double)dest.x, (double)dest.y, (double)dest.z);
		return;
	}
	obj->setStatus((ObjectStatusTypes)0x55, true);
	int id = obj->m_key74;
	((_STL::set<int> *)&m_map8c)->insert(id);
}

// MSVC uses the final state when emitting delayed template instances.
#pragma optimize("", on)
