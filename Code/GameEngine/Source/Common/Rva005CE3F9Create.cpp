// ?Rva005CE3F9Create@@YAPAVRva005CE3F9@@PAV1@PBUPayload@Rva005CE327@@@Z
// cl: /O1 /MD /EHs-c-
// retail 0x005CE3F9, 50 bytes. Free __cdecl creator: `new Rva005CE327(src)`
// stored to out+0 with an AddRef inc, returning out.
// Target evidence: prolog `push ebp / mov ebp,esp / push ecx / and [ebp-4],0`
// then `push 0x10 / call 0x2fda0` (operator new), null test routed to
// `xor eax,eax`, ctor 0x005CE327, `mov [ecx],eax`, `inc [eax+4]`, leave/ret.
// Twin of 0x005CE2A1 (3-dword payload; retail allocates 0x14 here).
//
// The retail state-zero is `and dword ptr [ebp-4],0`. With /EHs-c- MSVC 7.1
// emits `mov dword ptr [ebp-4],0` instead (7 bytes rather than 4); /EHsc
// also adds a non-retail SEH registration. Keep the allocation, constructor,
// null branch and refcount logic in C++; this one inline instruction preserves
// the target compiler state operation. The same failure was measured on twin
// 0x005CE2A1 and across the toolchain variants recorded in reverse/re_attempts.log.
#include <new>

class Rva005CE327
{
public:
	struct Payload { int v[3]; };
	Rva005CE327(const Payload *src);
	virtual ~Rva005CE327();
public:
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CE3F9
{
public:
	Rva005CE327 *m_00;
};

Rva005CE3F9 * __cdecl Rva005CE3F9Create(Rva005CE3F9 *out, const Rva005CE327::Payload *src)
{
	volatile int state;
	__asm and dword ptr state, 0
	Rva005CE327 *p = new Rva005CE327(src);
	out->m_00 = p;
	if (p != 0)
		p->m_ref++;
	return out;
}
