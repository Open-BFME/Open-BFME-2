// ??0Sas@@QAE@XZ
// partial score=0.85 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: Sas composer ctor.
//
// ?rva001510C2@Sas@@QAE@XZ, retail 0x001510C2 (154 bytes).
// Default ctor: five vtable-slot stores, four pinned member constructions
// (the 87B family) with EH states 2-5, a +0xB8 member via the rowed
// Rva0014F40C ctor, then the rowed Register("Sas", this) call.
// The "Sas" name is retail-proven (string at 0xBD3A30, prior-seat Register note).

#include <new>

#include "ascii_string.h"

class Rva00150D8A
{
public:
	Rva00150D8A(int n);
private:
	AsciiString m_str;
	char m_pad[0x14];
};

class Rva00150DFD
{
public:
	Rva00150DFD(int n);
private:
	AsciiString m_str;
	char m_pad[0x14];
};

class Rva00150F19
{
public:
	Rva00150F19(int n);
private:
	AsciiString m_str;
	char m_pad[0x14];
};

class Rva00150F70
{
public:
	Rva00150F70(int n);
private:
	AsciiString m_str;
	char m_pad[0x14];
};

class Rva0014F40C
{
public:
	Rva0014F40C();
	virtual void dummy();
private:
	char m_pad04[0x1C];
};

void __cdecl Rva00153565Register(const char *name, void *obj);

// Two vtable slots double as EH-tracked construction witnesses: the
// retail state sequence (2,3,4,5,7) counts exactly two silent pre-tracked
// constructions before the member calls. Each slot stores its immediate but
// carries a nontrivial dtor (explicit AsciiString teardown of the overlapped
// word) so the construction is counted. Never runs outside unwind.
class RvaSlotV
{
public:
	RvaSlotV(int v) : m_v(v) {}
	~RvaSlotV() { m_s.~AsciiString(); }
private:
	union {
		int m_v;
		AsciiString m_s;
	};
};

class Sas
{
public:
	Sas();
private:
	void *m_v00;
	RvaSlotV m_v04;
	RvaSlotV m_v08;
	void *m_v0C;
	void *m_v10;
	Rva00150D8A m_m14;
	Rva00150DFD m_m2C;
	Rva00150F19 m_m44;
	Rva00150F70 m_m5C;
	char m_pad74[0xB8 - 0x74];
	Rva0014F40C m_mB8;
};

// ?rva001510C2@Sas@@QAE@XZ
Sas::Sas()
	: m_v00((void *)0xBD3A34)
	, m_v04(0xBD3898)
	, m_v08(0xBD383C)
	, m_v0C((void *)0xBD3848)
	, m_v10((void *)0xBD3834)
	, m_m14(1)
	, m_m2C(4)
	, m_m44(4)
	, m_m5C(1)
	, m_mB8()
{
	Rva00153565Register("Sas", this);
}
