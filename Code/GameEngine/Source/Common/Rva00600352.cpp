// cl: /O1 /DNDEBUG /MD
// ?rva00600352Init@@YIPAVRva00600352@@PAV1@HHHHH@Z @0x00600352 39B evidence:
// fastcall init (this, fwd-dead-forwarded, a, b, c, d-dead): chains to
// pinned fastcall ?rva00600305@@YIXPAVRva00600305Obj@@HHHH@Z @0x00600305
// with (this, fwd, a, b, c) pushed c,b,a; m_08 = a; installs vtable 0x00C7A620 by
// literal store; returns this; ret 0x10. Same fastcall family as 0x005F8E37.
// TU-local view only.
class Rva00600305Obj;
void __fastcall rva00600305(Rva00600305Obj *o, int fwd, int s1, int s2, int s3);

class Rva00600352
{
public:
	char m_pad[8];
	int m_08;
};

Rva00600352 *__fastcall rva00600352Init(Rva00600352 *o, int fwd, int volatile a, int b, int c, int d)
{
	rva00600305((Rva00600305Obj *)o, fwd, b, c, d);
	o->m_08 = a;
	((int *)o)[0] = 0x00C7A620;
	return o;
}
