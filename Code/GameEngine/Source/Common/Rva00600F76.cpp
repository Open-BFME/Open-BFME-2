// cl: /O1 /DNDEBUG /MD
// ?rva00600F76Init@@YIPAVRva00600F76@@PAV1@HPAH@Z @0x00600F76 29B evidence:
// fastcall init (this, fwd-dead-forwarded, a): m_00 = *a; sub-object at +4
// takes pinned fastcall ?rva00200A40@@YIXPAURva00200A40Sub@@HH@Z
// @0x00200A40(sub, fwd, a+1 as address); returns this; ret 4. Sibling of
// 0x00600BFB (different arg plumbing). TU-local view only.
struct Rva00200A40Sub
{
	char m_pad[4];
};

void __fastcall rva00200A40(Rva00200A40Sub *sub, int fwd, int x);

class Rva00600F76
{
public:
	int m_00;
};

Rva00600F76 *__fastcall rva00600F76Init(Rva00600F76 *o, int fwd, int *a)
{
	o->m_00 = *a;
	rva00200A40((Rva00200A40Sub *)((char *)o + 4), fwd, (int)(a + 1));
	return o;
}
