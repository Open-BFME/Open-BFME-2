// cl: /MD
//
// ?rva0006ED29@Rva0006ED29@@QAEXPAX@Z, retail 0x0006ED29, 13 bytes.
// Frameless __thiscall delete wrapper: pushes the single stack arg and
// tail-calls the rowed global operator delete at 0x0002FD60, cleaning the
// pushed arg with pop ecx (retail /O1 small-code idiom) and returning via
// ret 4. This (ecx) is never read: callers pass varying this (edi at
// 0x0006B609, global 0x00DE1B34 elsewhere) and one pointer arg. Evidence:
// four callers, callee rowed, no vtable. Address-derived name stays honest.
// Plain declaration lets the gate resolve the callee by full mangled name.

void __cdecl operator delete(void *p);

class Rva0006ED29
{
public:
	void rva0006ED29(void *p);
};

void Rva0006ED29::rva0006ED29(void *p)
{
	::operator delete(p);
}
