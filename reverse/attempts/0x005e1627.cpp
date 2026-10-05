// ??0Rva005E1627@@QAE@PAX0@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva005E1627@@QAE@PAX0@Z @0x005E1627 (89B): small EH ctor allocating
// 0x44 via real nothrow-new (TU-local static forward inlines to the pinned
// plain operator new, as in the banked 0x005E5C95 factory) and constructing
// a helper on it with (this, a1, a2) through the pinned helper ctor at
// 0x005E136C; the vtable 0xC77998 has no provider so it is imprinted as the
// measured immediate (linking will want the real table). 81/89: everything
// except the EH registration (mov eax scope plus call 0x629188, which also
// establishes ebp) plus 2 reserved slots plus state 0-to-1. Refuted: explicit
// operator-new plus placement (needs inline funclets), throw variants (throw
// kills state, throwing needs funclets), NULL-init (optimized away),
// volatile int (mov overshoot), explicit try-catch-empty (adds 26B inline).
// State without inline handler means out-of-line funclet/scope table.
#include <new>

static inline void *operator new(unsigned int s, const std::nothrow_t &)
{
	return operator new(s);
}

// Declared so a throwing helper ctor gets EH allocation cleanup (out of
// line); without it MSVC emits no scope table at all.
void operator delete(void *p, const std::nothrow_t &) throw();

void *__cdecl operator new(unsigned int size);

class Rva005E136C
{
public:
	Rva005E136C(void *outer, void *a1, void *a2);
};

class Rva005E1627
{
public:
	Rva005E1627(void *a1, void *a2);

private:
	void *m_vtbl; // +0 (imprinted, no provider)
	int m_04; // +4
	Rva005E136C *m_08; // +8
};

// ??0Rva005E1627@@QAE@PAX0@Z
Rva005E1627::Rva005E1627(void *a1, void *a2)
{
	*(void **)this = (void *)0xC77998;
	m_04 = 0;
	Rva005E136C *h = new (std::nothrow) Rva005E136C(this, a1, a2);
	m_08 = h;
}
