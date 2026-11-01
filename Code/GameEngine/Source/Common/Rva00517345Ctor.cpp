// cl: /O1 /MD
// ??0Rva00517345@@QAE@ABURva0051732A@@@Z @0x00517345 31B
// Ctor: vtable at +0, zero +4, copy TargetRef pointer from holder arg (+0)
// into +8 with AddRef at +4. Holder arg matches prev Rva0051732A layout.
// Caller 0x005173CB news 12B then passes its arg through; sole AddRef,
// no other callees. Vtable immediate filled by gate.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

struct Rva0051732A
{
	TargetRef00217D4C *m_ptr;
};

struct Rva00517345
{
	virtual void rva00517345slot();
	int m_04;
	TargetRef00217D4C *m_08;
	Rva00517345(const Rva0051732A &other);
};

// ?rva00517345slot@Rva00517345@@UAEXXZ present-unmatched
void Rva00517345::rva00517345slot()
{
}

Rva00517345::Rva00517345(const Rva0051732A &other) : m_04(0)
{
	m_08 = other.m_ptr;
	if (m_08)
		++m_08->references;
}

// One more constructor of this shape, each installing its own vtable (the only
// differing operand): 0x0044BDA2 (VA 0xc3edf4). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

struct Rva0044BDA2
{
	virtual void slot() {}
	int m_04;
	TargetRef00217D4C *m_08;
	Rva0044BDA2(const Rva0051732A &other);
};

Rva0044BDA2::Rva0044BDA2(const Rva0051732A &other) : m_04(0)
{
	m_08 = other.m_ptr;
	if (m_08)
		++m_08->references;
}
