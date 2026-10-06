// cl: /O1 /DNDEBUG /MD
//
// ?rva002D43A0@Rva002D43A0Owner@@QAEXXZ @0x002D43A0 38B: teardown tailcall
// (thiscall, no args, void). Deletes the heap pointer at m_10+0xec
// (nulling it) through the landed scalar operator delete, then tailcalls
// the pinned void method at 0x002D3C5F on the inline sub-object at
// m_10+0x98 (a bare jmp, per the voidcall-tail precedent). Views are
// minimal scaffolding; exact identities unproven.
class Rva002D43A0Sub
{
public:
	void rva002D3C5F();

	char m_pad[0x54];
};

struct Rva002D43A0Mid
{
	char m_pad00[0x98];
	Rva002D43A0Sub m_98;
	void *m_ec;
};

class Rva002D43A0Owner
{
public:
	void rva002D43A0();

private:
	char m_pad00[0x10];
	Rva002D43A0Mid *m_10;
};

// ?rva002D43A0@Rva002D43A0Owner@@QAEXXZ
void Rva002D43A0Owner::rva002D43A0()
{
	void *p = m_10->m_ec;
	m_10->m_ec = 0;
	delete p;
	return m_10->m_98.rva002D3C5F();
}
