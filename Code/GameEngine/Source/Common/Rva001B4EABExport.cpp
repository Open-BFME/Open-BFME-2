// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva001B4EAB@Rva001B4EAB@@QAEXXZ @0x001B4EAB 166B. Per-entry exporter over
// the same 8-byte-entry array as 0x001B4F8B ([this+0]=begin, [this+4]=end):
// copies the entry object's AsciiString at +8 into a temp, formats
// "%s_%02d.csv" with that text and the entry index into a second temp,
// then calls the entry object's vtable slot 11 with the formatted text.
// Evidence: caller at 0x002304BB; rowed callees StringBase::set,
// AsciiString::format "%s_%02d.csv", releaseBuffer x2 and empty fallback
// g_Rva0107301CEmptyString; virtual slot 0x2c.
#include "ascii_string.h"


__forceinline const char *GetStr001B4EAB(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

struct Rva001B4EABEntry
{
	void *m_obj; // +0
	int m_pad; // +4 keeps the 8-byte stride retail steps
};

class Rva001B4EABTarget
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
	virtual void vf9();
	virtual void vf10();
	virtual void vf11(const char *s);

public:
	char m_pad4[4]; // +4
	AsciiString m_name; // +8 compared via set
};

class Rva001B4EAB
{
public:
	void rva001B4EAB();

private:
	Rva001B4EABEntry *m_begin; // +0
	Rva001B4EABEntry *m_end; // +4
};

void Rva001B4EAB::rva001B4EAB()
{
	int index = 0;
	for (Rva001B4EABEntry *p = m_begin; p != m_end; ++p) {
		AsciiString name;
		AsciiString base;
		((StringBase<char> *)&base)->set(*(const StringBase<char> *)((char *)p->m_obj + 8));
		name.format("%s_%02d.csv", GetStr001B4EAB(base), index);
		++index;
		((Rva001B4EABTarget *)p->m_obj)->vf11(GetStr001B4EAB(name));
	}
}
