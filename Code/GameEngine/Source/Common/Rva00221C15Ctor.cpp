// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva00221C15@@QAE@ABVAsciiString@@ABVRva00221A58@@PAVINI@@@Z @0x00221C15 71B
// Outer ctor forwarding same 3 args to member Rva00221B42 at +8. Explicit
// vtable slot: base g_00BC6F20 via volatile (kept early) then derived
// g_00BE6C38 with refcount at +4 zeroed. Caller 0x002222C0 passes token
// string plus esi+0xC plus INI. Evidence: retail bytes and callers.
#include "ascii_string.h"

#include "../../Include/Common/Rva0022185A.h"

#include "../../Include/Common/Rva00221A58.h"

struct FieldParse;

#include "../../Include/Common/INI/INI.h"

class Rva00221B42
{
public:
	Rva00221B42(const AsciiString &a, const Rva00221A58 &b, INI *ini);
private:
	Rva00221A58 m_00;
	AsciiString m_1C;
};

extern "C" const unsigned char __identifier("??_7Secondary005E7ED7@@6B@")[];
// The retail table at RVA 0x007E6C38: 1 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00221C15@@QAEPAXI@Z")();
}
extern const void *const g_00BE6C38[1] = {
	(const void *)&__identifier("??_GRva00221C15@@QAEPAXI@Z"), // slot 0 0x00221C5C
};

class Rva00221C15Empty
{
public:
	Rva00221C15Empty() {}
	~Rva00221C15Empty() {}
};

class Rva00221C15Base : public Rva00221C15Empty
{
public:
	Rva00221C15Base() : m_04(0) { *(volatile const void **)&m_vtable = __identifier("??_7Secondary005E7ED7@@6B@"); }
	// As in Rva00221C15Dtor.cpp: retail's teardown 0x00221C78 restores the vptr inline.
	~Rva00221C15Base() { *(const void **)&m_vtable = __identifier("??_7Secondary005E7ED7@@6B@"); }
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

Rva00221C15::Rva00221C15(const AsciiString &asciiString, const Rva00221A58 &b, INI *ini)
	: Rva00221C15Base()
	, m_08(asciiString, b, ini)
{
	*(const void **)&m_vtable = g_00BE6C38;
}
