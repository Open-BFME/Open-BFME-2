// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?Run@Rva005B5787Box@@QAEXXZ @0x005B5787 63B.
// Zeroes the dword slot at +0x27C of the owner at +4, re-selects the current entry
// when the two cursor words at +0x414/+0x418 agree (0x005B54ED, thiscall with
// three zero arguments), then tail-calls the condition-bit clearer 0x00407C17 on
// the same slot. Owner layout views are neutral.
#include "../../Include/Common/Rva005B034ADwordSlot.h"

#include "../../Include/Common/Rva004076EE.h"

class Rva005B566B
{
public:
	void rva005B54ED(unsigned int, unsigned int, bool);	// row 0x005B54ED (on Rva005B566B)
};

class Rva005B5787Owner
{
public:
	Rva005B034ADwordSlot *slot() { return reinterpret_cast<Rva005B034ADwordSlot *>(m_pad + 0x27C); }
	Rva004076EE *bits() { return reinterpret_cast<Rva004076EE *>(m_pad + 0x27C); }
	int cursor() const { return m_cursor; }
	int limit() const { return m_limit; }
private:
	char m_pad[0x414];
	int m_cursor;
	int m_limit;
};

class Rva005B5787Box
{
public:
	void Run();
private:
	void *m_00;
	Rva005B5787Owner *m_owner;
};

void Rva005B5787Box::Run()
{
	m_owner->slot()->set(0);
	if (m_owner->cursor() == m_owner->limit())
		reinterpret_cast<Rva005B566B *>(this)->rva005B54ED(0, 0, false);
	m_owner->bits()->rva00407C17();
}
