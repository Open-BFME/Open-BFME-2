// cl: /O1 /DNDEBUG /MD
//
// ?rva002E713F@Rva002E713FOwner@@QAEXXZ @0x002E713F 57B: guarded pair-call
// (thiscall, void). Returns when +0x10 is null; invokes pinned 0x0052F294
// on this when either flag byte (+0x1BEB4/+0x1BEB5) is set; then invokes
// pinned 0x00533BEC on this+0x460 with (&+0x14, &+0x60, +0x10). Honest
// address-derived names; member/callee identities unproven.

struct Rva002E713F460
{
	void rva00533BEC(void *a, void *b, void *c);
	char m_pad[4];
};

class Rva002E713FOwner
{
public:
	void rva002E713F();
	void rva0052F294();
private:
	char m_pad00[0x10];
	void *m_p10;
	int m_14;
	char m_pad18[0x60 - 0x18];
	int m_60;
	char m_pad64[0x460 - 0x64];
	Rva002E713F460 m_s460;
	char m_pad464[0x1BEB4 - 0x460 - 4];
	unsigned char m_b1BEB4;
	unsigned char m_b1BEB5;
};

// ?rva002E713F@Rva002E713FOwner@@QAEXXZ
void Rva002E713FOwner::rva002E713F()
{
	if (m_p10 == 0)
		return;
	if (m_b1BEB4 != 0 || m_b1BEB5 != 0)
		rva0052F294();
	m_s460.rva00533BEC(m_p10, &m_60, &m_14);
}
