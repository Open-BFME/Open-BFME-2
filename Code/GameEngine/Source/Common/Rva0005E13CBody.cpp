// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Dump range 1 (0x0005E13C 44B): frameless thiscall predicate over a
// two-level pointer chain. Null outer yields true, null inner yields false,
// inner +0xB0 != 2 yields true, else returns this->helper(middle). The
// helper is the pinned in-range 0x0005D425 (thiscall, this plus one ptr
// arg); keeping ecx live as this is what puts the middle load in edx.
// Honest address-derived names.

struct Rva0005E13CInner2
{
	char m_pad[0xB0];
	int m_B0; // +0xB0
};

struct Rva0005E13CInner1
{
	char m_pad[0x08];
	Rva0005E13CInner2 *m_08; // +0x08
};

struct Rva0005E13CArg
{
	char m_pad[0x04];
	Rva0005E13CInner1 *m_04; // +0x04
};

class Rva0005E13CHost
{
public:
	bool rva0005E13C(const Rva0005E13CArg *p);
	bool helper(const Rva0005E13CInner1 *a);
};

bool Rva0005E13CHost::rva0005E13C(const Rva0005E13CArg *p)
{
	Rva0005E13CInner1 *a = p->m_04;
	if (!a)
		return true;
	Rva0005E13CInner2 *d = a->m_08;
	if (!d)
		return false;
	if (d->m_B0 != 2)
		return true;
	return helper(a);
}
