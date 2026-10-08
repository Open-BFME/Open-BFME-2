// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00529698@Rva0052936C@@QAEXPBD@Z @0x00529698 264B.
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

struct CameraMarker;
class Rva00528FE6
{
public:
	void rva00528FE6(CameraMarker *marker);
	void *m_ptr;
};

struct Rva00529698Elem
{
	Rva00575674 m_holder;
	int m_04;
	Rva00528FE6 m_08;
	int m_0C;
	int m_10;
};

class Rva0052936C
{
public:
	void rva00529698(const char *section);
	void rva0052991E(const char *section);
private:
	char m_pad00[0x64];
	Rva00529698Elem m_elems[6];
};

bool __cdecl Rva00529628Get(const char *section, int *out);
bool __cdecl Rva00528C30Get(const char *section, AsciiString &out);
const char *__cdecl Rva00412845AfterLevel(const char *s);
int __cdecl Rva004128BBGetLevel(const char *s);

__forceinline const char *GetStr00529698(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
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

void Rva0052936C::rva00529698(const char *section)
{
	AsciiString val;
	Rva00529698Elem *e;
	{
		int idx;
		if (!Rva00529628Get(section, &idx) || !Rva00528C30Get(section, val))
			return;
		e = &m_elems[idx];
		if (e->m_holder.m_ptr != 0)
			return;
	}
	e->m_holder.rva00575674((Object *)new Rva005D2462(Rva004128BBGetLevel(GetStr00529698(val)), AsciiString(Rva00412845AfterLevel(GetStr00529698(val))), (int)&e->m_04, (int)&e->m_08));
}

class Rva005C3932
{
public:
	Rva005C3932(int level, const AsciiString &name);
private:
	char m_data[8];
};

// Native 0052991E..00529A21 (259B), thiscall / ret 4. Independent target
// accesses establish the +0x64 array base, 20-byte stride and +8 owning
// holder. Existing family methods establish the address-derived owner.
// StrategicHUD::CommandUIImpl::OnToggleFlashLoaded is the matched algorithm
// lead; that donor name is not claimed for this separate native callback.
void Rva0052936C::rva0052991E(const char *section)
{
	AsciiString name;
	Rva00529698Elem *button;
	{
		int slot;
		if (!Rva00529628Get(section, &slot))
			return;
		if (!Rva00528C30Get(section, name))
			return;
		button = &m_elems[slot];
	}
	if (button->m_08.m_ptr)
		return;
	button->m_08.rva00528FE6((CameraMarker *)new Rva005C3932(Rva004128BBGetLevel(GetStr00529698(name)), AsciiString(Rva00412845AfterLevel(GetStr00529698(name)))));
}
