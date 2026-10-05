// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?rva000AAD88@@YAPAXPAURva000AAD88Arg@@@Z @0x000AAD88 57B: optional clone.
// Null yields null. When bit 0x406 of the +0x58 word is clear, runs the
// rowed 0x000A97A9 writer on the +0x5C member and returns it. Otherwise
// allocates 0x30 bytes through the rowed operator new and returns the
// pinned 0x000AA966 initializer's result, null when allocation fails.
// Honest address-derived names; boundary verified (push esi at 0xAAD88,
// xor/pop/ret at end).

void *__cdecl operator new(unsigned int size);

class Rva000A97A9
{
public:
	void rva000A97A9(void *dst);
};

class Rva000AA966
{
public:
	void *rva000AA966(void *arg);
};

struct Rva000AAD88Arg
{
	char m_pad00[0x58];
	unsigned short m_58;
	char m_pad5A[0x5C - 0x5A];
	Rva000A97A9 *m_5C;
};

// ?rva000AAD88@@YAPAXPAURva000AAD88Arg@@@Z
void *rva000AAD88(Rva000AAD88Arg *u)
{
	if (!u)
		return 0;
	if ((u->m_58 & 0x406) == 0)
	{
		u->m_5C->rva000A97A9(u);
		return u->m_5C;
	}
	void *p = operator new(0x30);
	if (p)
		return ((Rva000AA966 *)p)->rva000AA966(u);
	return 0;
}
