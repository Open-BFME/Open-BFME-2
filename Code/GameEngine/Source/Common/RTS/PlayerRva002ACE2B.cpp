// cl: /MD /GX-
// stlport
// ?rva002ACE2B@Player@@QAEHPAX@Z @0x002ACE2B 161B: Player method iterating
// list at +0x6f4 of Rva002AC3BE entries (vector<float> at +4, ObjectID at
// +0x10, void* at +0). For each entry resolves Object via TheGameLogic
// findObjectByID, skips null and KindOf 0x44, matches *(int*)m_00 vs arg,
// picks float at list-index when in range, returns (int)floor(g-f*k).
// Evidence: prev PlayerRva002ACD09 list at +0x6f4, callers 0x00528CDD,
// callees rowed findObjectByID 0x00049DC5 and isKindOf, IAT floor.
#include <vector>
#include <list>

extern float g_Va007C26F0;
extern "C" __declspec(dllimport) double __cdecl floor(double);

// BaseType.h verbatim: C cast emits out-of-line __ftol2 plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing (shape-levers
// row 18, same __ftol2-vs-fistp symptom as ScriptEngineExecuteActions).
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum KindOfType
{
	KINDOF_44 = 0x44
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Rva002ACE2BEntry
{
	void *m_00;
	_STL::vector<float> m_04;
	int m_10;
	bool m_14;
};

class Player
{
public:
	int rva002ACE2B(void *arg);
private:
	char m_pad[0x6f4];
	_STL::list<int> m_list6f4;
};

int Player::rva002ACE2B(void *arg)
{
	int i = 0;
	float f = 0.0f;
	_STL::list<int>::iterator end = m_list6f4.end();
	for (_STL::list<int>::iterator it = m_list6f4.begin(); it != end; ++it) {
		Rva002ACE2BEntry *e = (Rva002ACE2BEntry *)(*it);
		Object *obj = TheGameLogic->findObjectByID((ObjectID)e->m_10);
		if (obj == 0)
			continue;
		if (obj->isKindOf((KindOfType)0x44))
			continue;
		if (*(void **)e->m_00 != arg)
			continue;
		if ((unsigned int)i < e->m_04.size())
			f = e->m_04[i];
		++i;
	}
	float prod = f * 100.0f;
	float diff = g_Va007C26F0 - prod;
	double d = floor((double)diff);
	float t = (float)d;
	return fast_float2long_round(t);
}
