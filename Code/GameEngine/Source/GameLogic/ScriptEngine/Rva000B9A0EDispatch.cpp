// cl: /DNDEBUG /MD /EHsc
// ?rva000B9A0E@Rva000B9A0E@@QAEXPAXHH@Z retail 0x000B9A0E 144B
// Loop over 0xC entries from +0x90 to +0x94; filter [esi+8]==arg2 and (arg2!=0 or [esi]==arg3); build BfmeDelayedLuaEventList and dispatch index 15 via global dispatch.
// Evidence: callees rowed ctor 0x000B6D8B and set 0x000B28A5 and dispatch 0x003360D2 plus dtor pin 0x000B6DD2; same list+dispatch pattern as sibling rva00335FE1; callers 0x000BD6C2 0x000BF9FC 0x000BEE25.
class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva001BDA20
{
public:
	void set(const Rva0036CA00Str &s);
private:
	char m_00[0x10];
	Rva0036CA00Str m_10;
	int m_14;
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	Rva001BDA20 m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

struct Rva000B9A0EEntry
{
	int m_a;
	Rva0036CA00Str m_b;
	int m_c;
};

class Rva000B9A0E
{
public:
	void rva000B9A0E(void *obj, int b, int c);
private:
	char m_pad[0x90];
	struct Vec
	{
		Rva000B9A0EEntry *m_first;
		Rva000B9A0EEntry *m_last;
	} m_vec;
};

void Rva000B9A0E::rva000B9A0E(void *obj, int b, int c)
{
	Vec &v = m_vec;
	if (v.m_first == v.m_last)
		return;
	for (Rva000B9A0EEntry *p = m_vec.m_first; p != m_vec.m_last; ++p) {
		if (p->m_c != b)
			continue;
		if (b == 0 && p->m_a != c)
			continue;
		BfmeDelayedLuaEventList list;
		list.m_events[0].set(p->m_b);
		reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(15, obj, &list);
	}
}
