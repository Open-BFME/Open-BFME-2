// ?rva005F90F6Init@@YIPAVRva005F90F6@@PAV1@HPAURva005F90F6Arg@@HHH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /EHsc /DNDEBUG /MD
// ?rva005F90F6Init@@YIPAVRva005F90F6@@PAV1@HPAURva005F90F6Arg@@HHH@Z @0x005F90F6 75B evidence:
// fastcall init (this, fwd-passthrough-in-edx, a, b, c, d): m_00 = a->m_ptr
// with intrusive ref bump at +4 when non-null; m_04 = b; m_08 = c; then
// sub-object at +12 takes pinned ?rva00437050@@YIXPAVRva005F90F6Sub@@H@Z
// @0x00437050(d); returns this; ret 0x10. SEH frame via __EH_prolog.
// Same fastcall family as 0x005F8E37. TU-local view only.
struct Rva005F90F6Pointee
{
	int m_00;
	int m_ref;
};

struct Rva005F90F6Arg
{
	Rva005F90F6Pointee *m_ptr;
};

class Rva005F90F6Sub
{
	// size unknown; offset +12 is what matters
	char m_pad[4];
};
void __fastcall rva00437050(Rva005F90F6Sub *sub, int d);

class Rva005F90F6
{
public:
	Rva005F90F6Pointee *m_00;
	int m_04;
	int m_08;
	Rva005F90F6Sub m_sub0C;
};

// ?rva005F90F6Init@@YIPAVRva005F90F6@@PAV1@HPAURva005F90F6Arg@@HHH@Z present-unmatched
Rva005F90F6 *__fastcall rva005F90F6Init(Rva005F90F6 *o, int fwd, Rva005F90F6Arg *a, int b, int c, int d) throw()
{
	Rva005F90F6Pointee *p = a->m_ptr;
	o->m_00 = p;
	if (p)
		p->m_ref++;
	try
	{
		o->m_04 = b;
		o->m_08 = c;
		rva00437050(&o->m_sub0C, d);
	}
	catch (...)
	{
	}
	return o;
}
