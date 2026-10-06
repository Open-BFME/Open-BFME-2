// cl: /O1 /DNDEBUG /MD
//
// ?rva002DEE9A@Rva002DEE9AOwner@@QAEXXZ @0x002DEE9A 41B: triple-call clearer
// (thiscall, void). Clears the +0xE0C and +0xE10 sub-objects via landed
// list clear 0x0023DAA5, invokes pinned 0x002DE311 on this, then zeroes the
// +0xE18 byte. Honest address-derived names; sub-object identities unproven
// beyond the shared clear shape.

struct Rva002DEE9A0E0C
{
	void clear();
	char m_pad[4];
};

struct Rva002DEE9A0E10
{
	void clear();
	char m_pad[8];
};

class Rva002DEE9AOwner
{
public:
	void rva002DEE9A();
	void rva002DE311();
private:
	char m_pad00[0xE0C];
	Rva002DEE9A0E0C m_s0E0C;
	Rva002DEE9A0E10 m_s0E10;
	unsigned char m_b0E18;
};

// ?rva002DEE9A@Rva002DEE9AOwner@@QAEXXZ
void Rva002DEE9AOwner::rva002DEE9A()
{
	m_s0E0C.clear();
	m_s0E10.clear();
	rva002DE311();
	m_b0E18 = 0;
}
