// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva00221C15@@QAE@ABVAsciiString@@ABVRva00221A58@@PAVINI@@@Z @0x00221C15 71B
// Outer ctor forwarding same 3 args to member Rva00221B42 at +8. Explicit
// vtable slot: base g_00BC6F20 via volatile (kept early) then derived
// g_00BE6C38 with refcount at +4 zeroed. Caller 0x002222C0 passes token
// string plus esi+0xC plus INI. Evidence: retail bytes and callers.
#include "ascii_string.h"

class Rva0022185A
{
public:
	Rva0022185A(const Rva0022185A &other);
private:
	AsciiString m_str;
	int m_04;
	unsigned char m_08;
};

class Rva00221A58
{
public:
	Rva00221A58(const Rva00221A58 &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	Rva0022185A m_0C;
	int m_18;
};

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva00221B42
{
public:
	Rva00221B42(const AsciiString &a, const Rva00221A58 &b, INI *ini);
private:
	Rva00221A58 m_00;
	AsciiString m_1C;
};

extern const void *const g_00BC6F20[];
extern const void *const g_00BE6C38[];

class Rva00221C15Empty
{
public:
	Rva00221C15Empty() {}
	~Rva00221C15Empty();
};

class Rva00221C15Base : public Rva00221C15Empty
{
public:
	Rva00221C15Base() : m_04(0) { *(volatile const void **)&m_vtable = g_00BC6F20; }
protected:
	const void *m_vtable;
	int m_04;
};

class Rva00221C15 : public Rva00221C15Base
{
public:
	Rva00221C15(const AsciiString &a, const Rva00221A58 &b, INI *ini);
private:
	Rva00221B42 m_08;
};

Rva00221C15::Rva00221C15(const AsciiString &a, const Rva00221A58 &b, INI *ini)
	: Rva00221C15Base()
	, m_08(a, b, ini)
{
	*(const void **)&m_vtable = g_00BE6C38;
}
