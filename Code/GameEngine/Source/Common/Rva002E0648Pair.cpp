// cl: /O1 /DNDEBUG /MD
//
// ?rva002E0648@Rva002E0648Owner@@QAEXPAX@Z @0x002E0648 32B and
// ?rva002E07CC@Rva002E0648Owner@@QAEXXZ @0x002E07CC 34B: +0x48/+0x4C member
// dispatchers (thiscall). 0x002E0648 forwards (this, arg1) to the pinned
// 0x004FB222 on the +0x4C member, then arg1 to the pinned 0x000366F0 on the
// +0x48 member. 0x002E07CC resolves the +0x48 member through the landed
// ?find@Rva002E18C3Lookup@@QAEPAVAsciiString@@ABV2@@Z row on the g_00A03140
// lookup object and, when found, forwards (this, found) to 0x004FB222 on
// +0x4C. Honest address-derived names.

class AsciiString;

class Rva002E18C3Lookup
{
public:
	AsciiString *find(AsciiString const &x);
};

struct Rva002E0648M48
{
	void rva000366F0(void *a);
	char m_pad[4]; // +0x48..+0x4C opaque
};

struct Rva002E0648M4C
{
	void rva004FB222(void *a, void *b);
};

extern class Rva002E18C3Lookup *Va00E03140Lookup;

class Rva002E0648Owner
{
public:
	void rva002E0648(void *a);
	void rva002E07CC();
private:
	char m_pad00[0x48]; // +0x00..+0x48 unclaimed
	Rva002E0648M48 m_m48; // +0x48
	Rva002E0648M4C m_m4C; // +0x4C
};

// ?rva002E0648@Rva002E0648Owner@@QAEXPAX@Z
void Rva002E0648Owner::rva002E0648(void *a)
{
	m_m4C.rva004FB222(this, a);
	m_m48.rva000366F0(a);
}

// ?rva002E07CC@Rva002E0648Owner@@QAEXXZ
void Rva002E0648Owner::rva002E07CC()
{
	AsciiString *s = Va00E03140Lookup->find(*(AsciiString *)&m_m48);
	if (s == 0)
		return;
	m_m4C.rva004FB222(this, s);
}
