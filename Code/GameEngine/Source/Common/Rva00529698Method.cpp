// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?OnButtonFrameLoaded@Rva0052936C@@QAEXPBD@Z @0x00529698 264B.
// Chain from 0x00529628: parse index and name params, find empty slot,
// allocate Rva005D2462 via rowed new and level/name helpers, store via rowed Set.
// Evidence: callers none; callees all rowed; prev/next share Rva0052936C family.
#include "ascii_string.h"

class Object
{
public:
	virtual void *deleteInstance(int flags);
};

class Rva00575674
{
public:
	void rva00575674(Object *p);
	Object *m_ptr;
};

struct Rva00529698Elem
{
	Rva00575674 m_holder;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

class Rva0052936C
{
public:
	void OnButtonFrameLoaded(const char *section);
private:
	char m_pad00[0x64];
	Rva00529698Elem m_elems[6];
};

bool __cdecl ParseButtonSlotIndex(const char *section, int *out);
bool __cdecl ParseClipName(const char *section, AsciiString &out);
namespace AptUtils { const char *__cdecl SkipLevelN(const char *s); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *s); }

__forceinline const char *GetStr00529698(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

class Rva005C31FB
{
public:
	virtual ~Rva005C31FB();
	Rva005C31FB(int level, const AsciiString &name);
private:
	int m_level;
	AsciiString m_name;
	bool m_flag0C;
};

class Rva00528B06 : public Rva005C31FB
{
public:
	Rva00528B06(int level, const AsciiString &name);
	virtual ~Rva00528B06();
};

class Rva005D2462 : public Rva00528B06
{
public:
	Rva005D2462(int level, const AsciiString &name, int a, int b);
private:
	int m_10;
	int m_14;
};

void Rva0052936C::OnButtonFrameLoaded(const char *section)
{
	AsciiString val;
	Rva00529698Elem *slot;
	{
		int idx;
		if (!ParseButtonSlotIndex(section, &idx) || !ParseClipName(section, val))
			return;
		slot = &m_elems[idx];
		if (slot->m_holder.m_ptr != 0)
			return;
	}
	slot->m_holder.rva00575674((Object *)new Rva005D2462(AptUtils::LevelIndexFromTarget(GetStr00529698(val)), AsciiString(AptUtils::SkipLevelN(GetStr00529698(val))), (int)&slot->m_04, (int)&slot->m_08));
}
