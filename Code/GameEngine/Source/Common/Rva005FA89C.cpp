// cl: /O1 /DNDEBUG /MD
// ?rva005FA89CInit@@YIPAVRva005FA89C@@PAV1@HHHPAURva005FA89CC@@@Z @0x005FA89C
// 41B evidence: fastcall init (this, fwd-passthrough-in-edx, a, b, c)
// chaining to pinned ?rva005FF0F6@@YIXPAVRva005FF0F6Obj@@HHHH@Z @0x005FF0F6
// with (this, fwd, a, b, c); installs vtable 0x00C79E30 by literal store;
// m_28 = c->m_04 (c kept in edi across the call); returns this; ret 0xC.
// Same fastcall family as 0x005FA0C9. TU-local view only.
struct Rva005FA89CC
{
	int m_00;
	int m_04;
};

class Rva005FA89C
{
public:
	char m_pad[0x28];
	int m_28;
};

class Rva005FF0F6Obj;
void __fastcall rva005FF0F6(Rva005FF0F6Obj *o, int fwd, int s1, int s2, int s3);

Rva005FA89C *__fastcall rva005FA89CInit(Rva005FA89C *o, int fwd, int a, int b, Rva005FA89CC *c)
{
	rva005FF0F6((Rva005FF0F6Obj *)o, fwd, a, b, (int)c);
	((int *)o)[0] = 0x00C79E30;
	o->m_28 = c->m_04;
	return o;
}
