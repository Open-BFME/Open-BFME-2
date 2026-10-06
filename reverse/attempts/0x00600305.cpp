// ?rva00600305Init@@YIPAVRva00600305@@PAV1@HHHH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /EHsc /DNDEBUG /MD
// ?rva00600305Init@@YIPAVRva00600305@@PAV1@HHHH@Z @0x00600305 77B evidence:
// fastcall init (this, fwd-dead-forwarded, a, b, c): explicit new(0x50) via
// rowed ??2@YAPAXI@Z @0x002FDA0 homed for the try funclet; installs vtable
// 0x00C7A5CC on this; null-checked new-obj feeds pinned fastcall
// ?rva006000AE@@YIHPAVRva006000AENew@@HPAVRva00600305@@HHH@Z @0x006000AE
// (newobj, fwd, this, a, b, c) inside try/catch (late state-init, EH prolog
// plus restore); m_04 = return; returns this; ret 0xC. TU-local views only.
class Rva006000AENew
{
public:
	Rva006000AENew() {}
	~Rva006000AENew();
	char m_pad[0x50];
};

class Rva00600305;
int __fastcall rva006000AE(Rva006000AENew *n, int fwd, Rva00600305 *o, int a, int b, int c);

class Rva00600305
{
public:
	char m_pad[4];
	int m_04;
};

// ?rva00600305Init@@YIPAVRva00600305@@PAV1@HHHH@Z present-unmatched
Rva00600305 *__fastcall rva00600305Init(Rva00600305 *o, int fwd, int a, int b, int c)
{
	Rva006000AENew *tmp = new Rva006000AENew;
	((int *)o)[0] = 0x00C7A5CC;
	int r = 0;
	if (tmp)
		r = rva006000AE(tmp, fwd, o, a, b, c);
	o->m_04 = r;
	return o;
}
