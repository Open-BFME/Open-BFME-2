// ??0CastleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0CastleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003983D4,
// 329 bytes. CastleBehavior ctor directly over the rowed FoundationAIUpdate
// base 0x004551B3 (retail calls the rowed base itself; there is no separate
// CastleMid body inside this constructor). Member layout is proven by the
// sibling dtor 0x0039857D, which walks the same members in reverse:
// vector<ScienceType> at +0x50/+0x5C/+0x68/+0x74/+0x80, set<AsciiString>
// at +0x8C, AsciiString at +0x98, int at +0x9C, map<int,void*> at +0xA0.
//
// Ordering evidence: retail's base call lands at 0x3983ED, every +0x30..+0x4C
// store precedes the first vector base ctor at 0x39844A, and the two
// post-member calls (0x3984E6 and 0x398505) close the body. So the vector /
// erase / spell members are built by the member-init list (which necessarily
// runs after the base ctor returns) while the +0x30..+0x4C stores are body
// statements, which the /O1 scheduler hoisted ahead of the inlined base
// member ctors.
//
// Still short at exactly 0x398403, one instruction past the 47 matching
// bytes: retail stores `mov DWORD PTR [ebp-0x4],0` (its EH state going to
// zero) between `xor eax,eax` and the +0x34 store. That is the compiler's own
// state variable, not a requestable local - a homed int lands on [ebp+0xc]
// instead. Measured dead ends, all at this same offset with size still 329:
// a declared-only dtor on CastleMid, an inline-empty one, and one on
// CastleBehavior (which also adds 4 bytes by inserting a field). Do not retry
// those.
#include "ascii_string.h"
#include <vector>
#include <set>
#include <map>

class Thing;
class Object;

class ModuleData
{
public:
	char m_pad00[0x10];
	char m_str10[4];
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
public:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class FoundationAIUpdate : public UpdateModule
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);
public:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned char m_2C;
};

extern const void *const g_00C1A780[];
extern const void *const g_00C1A6C0[];
extern const void *const g_00C1A6B0[];
extern const void *const g_00C1A690[];
extern const void *const g_00C1A680[];

class Rva002EE9B7
{
public:
	void rva002EE9B7();
};

class Rva00397E50
{
public:
	void rva00397E50();
};

class CastleMid : public FoundationAIUpdate
{
public:
	__forceinline CastleMid(Thing *thing, const ModuleData *moduleData)
		: FoundationAIUpdate(thing, moduleData)
	{
		int *slot30 = (int *)&m_30;
		*slot30 = (int)0x00C4EF80;
		m_48 = -1;
		m_34 = 0;
		m_38 = 0;
		m_3c = false;
		m_44 = false;
		m_vtable = (const void *)g_00C1A780;
		m_secondary0C = (const void *)g_00C1A6C0;
		m_secondary10 = (const void *)g_00C1A6B0;
		m_20 = (const void *)g_00C1A690;
		m_30 = (const void *)g_00C1A680;
		m_3d = true;
		m_40 = 0.0f;
		m_4c = 0.0f;
	}
	const void *m_30;
	int m_34;
	int m_38;
	bool m_3c;
	bool m_3d;
	char m_pad3E[2];
	float m_40;
	bool m_44;
	char m_pad45[3];
	int m_48;
	float m_4c;
};

class CastleBehavior : public CastleMid
{
public:
	CastleBehavior(Thing *thing, const ModuleData *moduleData);
private:
	_STL::vector<ScienceType> m_v50;
	_STL::vector<ScienceType> m_v5c;
	_STL::vector<ScienceType> m_v68;
	_STL::vector<ScienceType> m_v74;
	_STL::vector<ScienceType> m_v80;
	_STL::set<AsciiString> m_s8c;
	AsciiString m_98;
	int m_9c;
	_STL::map<int, void *> m_mA0;
};

// ??0CastleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
CastleBehavior::CastleBehavior(Thing *thing, const ModuleData *moduleData)
	: CastleMid(thing, moduleData)
	, m_v50(_STL::allocator<ScienceType>())
	, m_v5c(_STL::allocator<ScienceType>())
	, m_v68(_STL::allocator<ScienceType>())
	, m_v74(_STL::allocator<ScienceType>())
	, m_v80(_STL::allocator<ScienceType>())
	, m_s8c()
	, m_98()
	, m_9c(0)
	, m_mA0()
{
	_STL::vector<ScienceType> &v0 = m_v50;
	_STL::vector<ScienceType> &v1 = m_v5c;
	_STL::vector<ScienceType> &v2 = m_v68;
	v0.erase(v0.begin(), v0.end());
	v1.erase(v1.begin(), v1.end());
	v2.erase(v2.begin(), v2.end());
	((Rva002EE9B7 *)&m_s8c)->rva002EE9B7();
	((Rva00397E50 *)this)->rva00397E50();
	if (!((StringBase<char> *)((char *)m_moduleData + 0x10))->isEmpty())
		m_3c = true;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}