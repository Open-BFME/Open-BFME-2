// cl: /O1 /MD /EHs-c-
// Target evidence: retail 0x005CE2A1 allocates 0x10 bytes, calls the
// 0x005CE259 constructor, stores the result in out->m_00, increments the
// object's refcount when non-null, and returns out. The address-derived names
// preserve uncertainty about the surrounding subsystem.
// Retail clears its compiler temp with `and dword ptr [ebp-4], 0`. MSVC emits
// a seven-byte immediate store for ordinary C++ zero initialization, so this
// one equivalent store uses inline assembly; the function body remains C++.

#include <new>

class Rva005CE259
{
public:
	struct Payload { int v[2]; };
	Rva005CE259(const Payload *src);
	virtual ~Rva005CE259();
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CE2A1
{
public:
	Rva005CE259 *m_00;
};

Rva005CE2A1 *__cdecl Rva005CE2A1Create(
	Rva005CE2A1 *out,
	const Rva005CE259::Payload *src)
{
	volatile int state;
	__asm { and state, 0 }
	Rva005CE259 *p = new Rva005CE259(src);
	out->m_00 = p;
	if (p != 0)
		p->m_ref++;
	return out;
}
