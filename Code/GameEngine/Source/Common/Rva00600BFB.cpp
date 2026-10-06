// cl: /O1 /DNDEBUG /MD
// ?rva00600BFBInit@@YIPAVRva00600BFB@@PAV1@HPAHH@Z @0x00600BFB 29B evidence:
// fastcall init (this, fwd-dead-forwarded, a, b): m_00 = *a; sub-object at
// +4 takes pinned fastcall ?rva00200A40@@YIXPAURva00200A40Sub@@HH@Z
// @0x00200A40(sub, fwd, b); returns this; ret 8. TU-local view only.
struct Rva00200A40Sub
{
	char m_pad[4];
};

void __fastcall rva00200A40(Rva00200A40Sub *sub, int fwd, int x);

class Rva00600BFB
{
public:
	int m_00;
};

Rva00600BFB *__fastcall rva00600BFBInit(Rva00600BFB *o, int fwd, int *a, int b)
{
	o->m_00 = *a;
	rva00200A40((Rva00200A40Sub *)((char *)o + 4), fwd, b);
	return o;
}
